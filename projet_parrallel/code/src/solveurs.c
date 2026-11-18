/*
 * solveurs.c — GC et BiCGStab locaux, sans communication. Spécifications : solveurs.h.
 *
 * Gradient conjugué (A symétrique définie positive) :
 *     r = b − A x ;  p = r ;  rr = (r, r)
 *     tant que sqrt(rr) > tol ||b|| et it < itmax :
 *         v = A p ;  alpha = rr / (p, v)
 *         x = x + alpha p ;  r = r − alpha v
 *         rr_nouveau = (r, r) ;  p = r + (rr_nouveau / rr) p ;  rr = rr_nouveau ;  it++
 *
 * BiCGStab (A inversible quelconque), comme mod_bicgstab.f90 du TP Schwarz :
 *     r = b − A x ;  r0 = r ;  rho = alpha = omega = 1 ;  v = p = 0
 *     tant que ||r|| > tol ||b|| et it < itmax :
 *         rho_prec = rho ;  rho = (r0, r)                        (breakdown si rho ~ 0)
 *         beta = (rho / rho_prec) (alpha / omega)
 *         p = r + beta (p − omega v) ;  v = A p ;  alpha = rho / (r0, v)
 *         s = r − alpha v ;  t = A s ;  omega = (t, s) / (t, t)    (breakdown si omega ~ 0)
 *         x = x + alpha p + omega s ;  r = s − omega t ;  it++
 *
 * Aucun malloc ici : tous les vecteurs viennent de Travail (alloués une fois).
 * Le produit A·p est operateur_appliquer(op, p, v).
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "solveurs.h"

int travail_allouer(Travail *w, int n)
{
    /* TODO */
    return 0;
}

void travail_liberer(Travail *w)
{
    /* TODO */
}

double produit_scalaire(const double *a, const double *b, int n)
{
    /* TODO */
    return 0.0;
}

int gradient_conjugue(const Operateur *op, const double *b, double *x,
                      double tol, int itmax, Travail *w)
{
    /* TODO */
    return 0;
}

int bicgstab(const Operateur *op, const double *b, double *x,
             double tol, int itmax, Travail *w)
{
    /* TODO */
    return 0;
}

int solveur_resoudre(const Params *p, const Operateur *op, const double *b, double *x, Travail *w)
{
    /* TODO */
    return 0;
}
