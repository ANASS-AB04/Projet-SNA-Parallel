/*
 * schwarz.c — Échanges d'interface et critère d'arrêt global. Spécifications : schwarz.h.
 *
 * Fonctions internes conseillées (static, à écrire dans ce fichier) :
 *
 *   static void preparer_robin(const Params *p, const SousDomaine *sd, const double *u,
 *                              TamponsSchwarz *t);
 *       Remplit t->envoi_bas et t->envoi_haut avec (2 dy / alpha) R (formules dans schwarz.h).
 *
 *   static void echanger_bloquant(const SousDomaine *sd,
 *                                 const double *envoi_bas, const double *envoi_haut,
 *                                 double *bord_bas, double *bord_haut);
 *       MPI_Sendrecv : envoi_bas vers voisin_bas, réception depuis voisin_haut dans bord_haut ;
 *       MPI_Sendrecv : envoi_haut vers voisin_haut, réception depuis voisin_bas dans bord_bas.
 *
 *   static void echanger_non_bloquant(... mêmes arguments ...);
 *       2 MPI_Irecv, 2 MPI_Isend, puis MPI_Waitall(4, ...).
 *
 * Dirichlet : envoi_bas = &u[r * nx] et envoi_haut = &u[(ny_loc - 1 - r) * nx] (pas de copie).
 * Robin     : envoi_bas = t->envoi_bas et envoi_haut = t->envoi_haut, après preparer_robin().
 */
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#include "schwarz.h"

int schwarz_allouer(TamponsSchwarz *t, const SousDomaine *sd)
{
    /* TODO */
    return 0;
}

void schwarz_liberer(TamponsSchwarz *t)
{
    /* TODO */
}

void schwarz_echanger(const Params *p, const SousDomaine *sd, const double *u,
                      TamponsSchwarz *t, double *bord_bas, double *bord_haut, Chronos *c)
{
    /* TODO : préparer (Robin), échanger (bloquant ou non), chronométrer dans c->comm */
}

double ecart_max_global(const SousDomaine *sd, const double *a, const double *b, Chronos *c)
{
    /* TODO : max local, puis MPI_Allreduce(..., MPI_MAX, sd->comm), chronométré dans c->reduction */
    return 0.0;
}
