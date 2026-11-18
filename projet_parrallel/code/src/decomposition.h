/*
 * decomposition.h — Découpage du domaine en bandes horizontales avec recouvrement.
 *
 *      y = Ly +-------------------------------+
 *             |  proc Np-1                    |
 *             |...............................|  <- r lignes communes (recouvrement)
 *             |  proc 1                       |
 *             |...............................|  <- r lignes communes
 *             |  proc 0                       |
 *      y = 0  +-------------------------------+ --> x
 *
 * Indices GLOBAUX : i = 1..Nx (colonnes), j = 1..Ny (lignes) ; x_i = i*dx, y_j = j*dy.
 * Les lignes 0 et Ny+1 et les colonnes 0 et Nx+1 sont les bords physiques (pas des inconnues).
 *
 * 1) charge() : partition SANS recouvrement des lignes 1..Ny -> [j_debut_propre, j_fin_propre].
 * 2) Recouvrement r : on étend la bande de floor(r/2) lignes vers le bas (s'il y a un voisin
 *    en bas) et de ceil(r/2) lignes vers le haut (s'il y a un voisin en haut) -> [j_debut, j_fin].
 *    Deux voisins ont alors exactement r lignes d'inconnues en commun.
 * 3) Stockage local, une ligne j étant contiguë en mémoire :
 *        k = (j - j_debut) * nx + (i - 1),   0 <= k < n_loc = nx * ny_loc.
 * 4) Lignes fantômes : j_debut - 1 et j_fin + 1. Elles ne sont pas stockées dans u : leurs
 *    valeurs (Dirichlet) ou les données de Robin sont dans bord_bas / bord_haut (operateur.h).
 */
#ifndef DECOMPOSITION_H
#define DECOMPOSITION_H

#include <mpi.h>

#include "parametres.h"

typedef struct {
    MPI_Comm comm;                    /* communicateur cartésien 1D, non périodique (MPI_Cart_create) */
    int rang, nb_procs;               /* rang dans comm, nombre de sous-domaines                      */
    int voisin_bas, voisin_haut;      /* rangs voisins (MPI_Cart_shift), MPI_PROC_NULL au bord physique */

    int j_debut, j_fin;               /* lignes globales des inconnues locales, recouvrement compris  */
    int j_debut_propre, j_fin_propre; /* lignes « possédées » (partition sans recouvrement) : sorties */
                                      /* et normes, pour compter chaque point une seule fois          */
    int nx;                           /* = Nx                                                         */
    int ny_loc;                       /* = j_fin - j_debut + 1                                        */
    int n_loc;                        /* = nx * ny_loc : taille des vecteurs locaux                   */
    double dx, dy;                    /* = Lx / (Nx + 1), Ly / (Ny + 1)                               */
} SousDomaine;

/*
 * Répartition équilibrée de n lignes (numérotées 1..n) sur np processus : le processus me
 * reçoit [*debut, *fin]. Les (n mod np) premiers processus ont une ligne de plus.
 * Exemple : n = 10, np = 3 -> [1,4], [5,7], [8,10].
 */
void charge(int me, int n, int np, int *debut, int *fin);

/*
 * Construit le sous-domaine du processus appelant :
 *   1. MPI_Cart_create(comm_monde, 1, {nb_procs}, {0}, 0, &sd->comm), rang dans sd->comm ;
 *   2. MPI_Cart_shift(sd->comm, 0, 1, &sd->voisin_bas, &sd->voisin_haut) ;
 *   3. charge() -> lignes propres ;
 *   4. extension de r = p->recouvrement lignes (voir l'en-tête) -> j_debut, j_fin ;
 *   5. nx, ny_loc, n_loc, dx, dy.
 * Contrôles : ny_loc >= 3, et r < nombre de lignes propres du plus petit sous-domaine.
 * Avec Np = 1 : un seul sous-domaine = tout le domaine, aucun voisin (à faire marcher en premier).
 * Retour : 0 si tout va bien, non nul sinon.
 */
int decomposition_construire(const Params *p, MPI_Comm comm_monde, SousDomaine *sd);

/*
 * Indice local k du point de coordonnées GLOBALES (i, j), avec i = 1..Nx et j = j_debut..j_fin.
 * Dans les boucles critiques (produit matrice-vecteur), calculer k directement.
 */
int indice_local(const SousDomaine *sd, int i, int j);

/*
 * Affiche, pour chaque rang (dans l'ordre des rangs : boucle + MPI_Barrier) :
 * rang, voisins, [j_debut, j_fin], [j_debut_propre, j_fin_propre], ny_loc.
 * Sert à tester le découpage.
 */
void decomposition_afficher(const SousDomaine *sd);

/* Libère le communicateur cartésien (MPI_Comm_free). */
void decomposition_liberer(SousDomaine *sd);

#endif /* DECOMPOSITION_H */
