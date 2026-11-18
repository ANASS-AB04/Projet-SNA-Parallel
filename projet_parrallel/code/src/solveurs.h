/*
 * solveurs.h — Solveurs itératifs LOCAUX (aucune communication MPI).
 *
 * Avec Schwarz, chaque sous-domaine résout SON problème A_loc x = b indépendamment : les
 * produits scalaires et les normes sont locaux. À opposer au GC global de FemPar.c (TP éléments
 * finis), où chaque produit scalaire demande un MPI_Allreduce.
 *
 * Contrat commun aux deux solveurs :
 *   - x contient l'initialisation en entrée (départ à chaud : itéré de Schwarz précédent)
 *     et la solution en sortie ;
 *   - arrêt si ||b − A x||_2 <= tol * ||b||_2, ou après itmax itérations ;
 *   - si ||b||_2 = 0 : x = 0 et retour 0 ;
 *   - retour : nombre d'itérations effectuées, ou −1 si non convergé (afficher un avertissement).
 */
#ifndef SOLVEURS_H
#define SOLVEURS_H

#include "parametres.h"
#include "operateur.h"

/*
 * Vecteurs de travail, alloués UNE seule fois (aucun malloc dans la boucle en temps).
 *   GC       : r, p, v (= A p)
 *   BiCGStab : r, r0 (résidu « ombre »), p, v, s, t
 */
typedef struct {
    int     n;
    double *r, *r0, *p, *v, *s, *t;
} Travail;

/* Alloue les 6 vecteurs de taille n. Retour : 0 si tout va bien. */
int travail_allouer(Travail *w, int n);

/* Libère les vecteurs. */
void travail_liberer(Travail *w);

/* Produit scalaire LOCAL : somme des a[k] * b[k], k = 0..n-1. */
double produit_scalaire(const double *a, const double *b, int n);

/* Gradient conjugué (A_loc symétrique définie positive : transmission Dirichlet). */
int gradient_conjugue(const Operateur *op, const double *b, double *x,
                      double tol, int itmax, Travail *w);

/*
 * BiCGStab (A_loc non symétrique : transmission Robin). Même contrat que gradient_conjugue.
 * Gérer les « breakdowns » : |rho| ou |omega| quasi nuls -> arrêt avec avertissement.
 * Algorithme : voir TP_SCHWARZ_ALTERNE_ROBIN/code/mod_bicgstab.f90.
 */
int bicgstab(const Operateur *op, const double *b, double *x,
             double tol, int itmax, Travail *w);

/* Appelle gradient_conjugue ou bicgstab selon p->solveur, avec p->tol_solveur et p->itmax_solveur. */
int solveur_resoudre(const Params *p, const Operateur *op, const double *b, double *x, Travail *w);

#endif /* SOLVEURS_H */
