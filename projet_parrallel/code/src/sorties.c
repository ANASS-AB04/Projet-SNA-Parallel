/*
 * sorties.c — Fichiers de résultats, erreurs, bilan de performance. Spécifications : sorties.h.
 *
 * Conseils :
 *   - noms de fichiers : snprintf(nom, sizeof nom, "%s/sol_%d.dat", p->dossier_sortie, sd->rang) ;
 *   - dossiers : mkdir(chemin, 0755) sur chaque préfixe du chemin (comme mkdir -p), en acceptant
 *     errno == EEXIST ; seulement sur le rang 0, puis MPI_Barrier ;
 *   - CSV : tester l'existence (fopen en "r") pour savoir s'il faut écrire l'en-tête, puis fopen en "a" ;
 *   - écrire au moins 15 chiffres significatifs (%.15e), pour pouvoir comparer des solutions.
 */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <sys/stat.h>
#include <mpi.h>

#include "sorties.h"
#include "probleme.h"

int sorties_preparer(const Params *p, const SousDomaine *sd)
{
    /* TODO */
    return 0;
}

void sorties_ecrire_solution(const Params *p, const SousDomaine *sd, const double *u, int n)
{
    /* TODO */
}

void sorties_erreurs(const Params *p, const SousDomaine *sd, const double *u,
                     double *e_inf, double *e_l2)
{
    /* TODO */
}

void sorties_bilan_perf(const Params *p, const SousDomaine *sd, const Chronos *c)
{
    /* TODO */
}
