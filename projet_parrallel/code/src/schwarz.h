/*
 * schwarz.h — Communications de la méthode de Schwarz additif.
 *
 * À chaque itération de Schwarz k, chaque processus :
 *   1) envoie à ses voisins les données d'interface calculées avec SON itéré u^k ;
 *   2) reçoit celles des voisins dans bord_bas / bord_haut ;
 *   3) résout son problème local (hors de ce module, voir solveurs.h) ;
 *   4) participe au critère d'arrêt global (ecart_max_global).
 * Tous les processus travaillent en même temps (Schwarz ADDITIF). Dans le TP alterné
 * (multiplicatif), le domaine 2 attendait au contraire la solution du domaine 1.
 *
 * Lignes échangées (indices LOCAUX de lignes 0..ny_loc−1, r = recouvrement, u[l][i] = valeur
 * de la ligne locale l et de la colonne i) :
 *
 *   Dirichlet (alpha = 0) : envoi direct depuis u (nx doubles contigus, pas de copie)
 *     vers le BAS  : ma ligne r            (&u[r * nx])            -> bord_haut du voisin du bas
 *     vers le HAUT : ma ligne ny_loc−1−r   (&u[(ny_loc-1-r) * nx]) -> bord_bas  du voisin du haut
 *
 *   Robin (alpha != 0, r >= 2) : on envoie R déjà multiplié par 2 dy / alpha (une seule ligne).
 *   Voir le TP Schwarz Robin, éq. 2 et 7.
 *     vers le BAS  (normale +y du voisin) :
 *         R_i = alpha (u[r][i] − u[r-2][i]) / (2 dy) + beta u[r-1][i]
 *     vers le HAUT (normale −y du voisin), avec m = ny_loc − r :
 *         R_i = alpha (u[m-1][i] − u[m+1][i]) / (2 dy) + beta u[m][i]
 *
 * Exemple (Ny = 10, Np = 3, r = 2) : le rang 0 a les lignes globales 1..5, le rang 1 les lignes 4..8.
 * En Dirichlet, le rang 1 envoie sa ligne locale 2 (globale 6) au rang 0, qui l'utilise comme
 * fantôme au-dessus de sa ligne 5. Le rang 0 envoie sa ligne locale 2 (globale 3) au rang 1,
 * qui l'utilise comme fantôme sous sa ligne 4.
 *
 * MPI_PROC_NULL rend sans effet les envois et réceptions vers un bord physique : une réception
 * depuis MPI_PROC_NULL ne modifie pas le tampon, donc les valeurs g de probleme_bords_physiques()
 * sont conservées sans cas particulier à coder.
 *
 * Deux variantes à comparer dans le rapport (aspects bloquants / non bloquants) :
 *   - bloquante     : 2 x MPI_Sendrecv (vers le bas, puis vers le haut), sans interblocage ;
 *   - non bloquante : 2 MPI_Irecv + 2 MPI_Isend + MPI_Waitall.
 * Utiliser deux étiquettes (tags) différentes pour les deux sens.
 *
 * Fonctions internes conseillées (static dans schwarz.c) :
 *   preparer_robin(...), echanger_bloquant(...), echanger_non_bloquant(...).
 */
#ifndef SCHWARZ_H
#define SCHWARZ_H

#include "parametres.h"
#include "decomposition.h"
#include "chrono.h"

/* Tampons d'envoi (taille nx) pour les données Robin. En Dirichlet, on envoie directement depuis u. */
typedef struct {
    double *envoi_bas, *envoi_haut;
} TamponsSchwarz;

/* Alloue les tampons (taille sd->nx). Retour : 0 si tout va bien. */
int schwarz_allouer(TamponsSchwarz *t, const SousDomaine *sd);

/* Libère les tampons. */
void schwarz_liberer(TamponsSchwarz *t);

/*
 * Met à jour bord_bas / bord_haut sur les côtés qui ont un voisin (lignes échangées : voir
 * l'en-tête), à partir de l'itéré courant u de chaque processus. Les côtés physiques ne sont
 * pas modifiés. La variante dépend de p->comm_non_bloquante.
 * Ajoute le temps passé à c->comm.
 */
void schwarz_echanger(const Params *p, const SousDomaine *sd, const double *u,
                      TamponsSchwarz *t, double *bord_bas, double *bord_haut, Chronos *c);

/*
 * Écart global : max de |a[k] − b[k]| sur toutes les inconnues de tous les processus
 * (max local, puis MPI_Allreduce MPI_MAX sur sd->comm).
 * Sert au critère de Schwarz (a = u^{k+1}, b = u^k) et au critère stationnaire (a = u^{n+1}, b = u^n).
 * Ajoute le temps passé à c->reduction.
 */
double ecart_max_global(const SousDomaine *sd, const double *a, const double *b, Chronos *c);

#endif /* SCHWARZ_H */
