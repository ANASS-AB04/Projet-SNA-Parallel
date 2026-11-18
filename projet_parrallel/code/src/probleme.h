/*
 * probleme.h — Définition du problème :
 *
 *      ∂t u − D Δu = f   dans [0,Lx] x [0,Ly]
 *      u = g             sur Γ0
 *      u = h             sur Γ1
 *
 * HYPOTHÈSE, déduite de la figure de l'énoncé (à confirmer avec l'enseignant) :
 *      Γ0 = bords bas (y = 0) et haut (y = Ly)      -> g
 *      Γ1 = bords gauche (x = 0) et droit (x = Lx)  -> h
 * Seul le cas 3 dépend de ce choix (g = 0, h = 1).
 *
 * Cas tests (Lx = Ly = 1, D = 1) :
 *   cas 1 : f = 2 (x − x² + y − y²),    g = h = 0              -> u_ex = x (1 − x) y (1 − y)
 *   cas 2 : f = sin(x) + cos(y),        g = h = sin(x) + cos(y) -> u_ex = sin(x) + cos(y)
 *   cas 3 : f = exp(−(x − Lx/2)²) exp(−(y − Ly/2)²) cos(π t / 2),  g = 0,  h = 1
 *           (solution périodique de période 4, pas de solution exacte)
 */
#ifndef PROBLEME_H
#define PROBLEME_H

#include "parametres.h"
#include "decomposition.h"

/* Terme source f(x, y, t) du cas p->cas. */
double probleme_f(const Params *p, double x, double y, double t);

/* Condition de Dirichlet g sur Γ0 (bords bas et haut). */
double probleme_g(const Params *p, double x, double y, double t);

/* Condition de Dirichlet h sur Γ1 (bords gauche et droit). */
double probleme_h(const Params *p, double x, double y, double t);

/* Solution exacte stationnaire (cas 1 et 2, valable pour D = 1). Retourne NAN pour le cas 3. */
double probleme_u_exacte(const Params *p, double x, double y);

/* 1 si le cas a une solution stationnaire connue (cas 1 et 2), 0 sinon. */
int probleme_est_stationnaire(const Params *p);

/*
 * Condition initiale u(x, y, 0) sur les n_loc inconnues locales (recouvrement compris).
 * Par défaut u0 = 0 (la condition initiale est un paramètre à étudier, énoncé 4e).
 * Point (i, j) global : x = i * dx, y = j * dy, k = indice_local(sd, i, j).
 */
void probleme_condition_initiale(const Params *p, const SousDomaine *sd, double *u);

/*
 * Remplit les valeurs de bord des côtés PHYSIQUES à l'instant t (tableaux de taille nx) :
 *   si sd->voisin_bas  == MPI_PROC_NULL : bord_bas[i-1]  = g(x_i, 0,  t), i = 1..Nx
 *   si sd->voisin_haut == MPI_PROC_NULL : bord_haut[i-1] = g(x_i, Ly, t), i = 1..Nx
 * Ne touche pas aux côtés qui ont un voisin (remplis par schwarz_echanger).
 * Les bords gauche et droit (h) ne passent pas par ces tableaux : ils sont ajoutés
 * directement dans operateur_second_membre().
 */
void probleme_bords_physiques(const Params *p, const SousDomaine *sd, double t,
                              double *bord_bas, double *bord_haut);

#endif /* PROBLEME_H */
