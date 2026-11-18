/*
 * probleme.c — Termes source, conditions aux limites, solutions exactes. Spécifications : probleme.h.
 *
 * π : M_PI (math.h, disponible avec -std=gnu11). NAN : math.h.
 * Coordonnées : x_i = i * sd->dx, y_j = j * sd->dy (indices globaux) ;
 * bords : x = 0, x = Lx, y = 0, y = Ly.
 */
#include <math.h>

#include "probleme.h"

double probleme_f(const Params *p, double x, double y, double t)
{
    /* TODO : switch (p->cas) */
    return 0.0;
}

double probleme_g(const Params *p, double x, double y, double t)
{
    /* TODO */
    return 0.0;
}

double probleme_h(const Params *p, double x, double y, double t)
{
    /* TODO */
    return 0.0;
}

double probleme_u_exacte(const Params *p, double x, double y)
{
    /* TODO : cas 1 et 2 ; NAN pour le cas 3 */
    return 0.0;
}

int probleme_est_stationnaire(const Params *p)
{
    /* TODO */
    return 0;
}

void probleme_condition_initiale(const Params *p, const SousDomaine *sd, double *u)
{
    /* TODO : boucle sur j = j_debut..j_fin, puis i = 1..Nx */
}

void probleme_bords_physiques(const Params *p, const SousDomaine *sd, double t,
                              double *bord_bas, double *bord_haut)
{
    /* TODO : seulement les côtés sans voisin (MPI_PROC_NULL) */
}
