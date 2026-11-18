/*
 * decomposition.c — Découpage en bandes et topologie MPI. Spécifications : decomposition.h.
 *
 * Résultat attendu pour Ny = 10, Np = 3, r = 2 :
 *   rang 0 : propres [1,4]    locales [1,5]    (+1 ligne en haut)
 *   rang 1 : propres [5,7]    locales [4,8]    (+1 en bas, +1 en haut)
 *   rang 2 : propres [8,10]   locales [7,10]   (+1 en bas)
 *   -> les rangs 0 et 1 partagent les lignes 4 et 5, les rangs 1 et 2 les lignes 7 et 8.
 *
 * Le motif MPI_Cart_create / MPI_Cart_shift est celui de TP1/exo1.cpp, en dimension 1.
 */
#include <stdio.h>
#include <mpi.h>

#include "decomposition.h"

void charge(int me, int n, int np, int *debut, int *fin)
{
    /* TODO */
}

int decomposition_construire(const Params *p, MPI_Comm comm_monde, SousDomaine *sd)
{
    /* TODO, dans l'ordre :
     *   1. MPI_Comm_size, MPI_Cart_create (1D, non périodique), MPI_Comm_rank dans sd->comm
     *   2. MPI_Cart_shift(sd->comm, 0, 1, &sd->voisin_bas, &sd->voisin_haut)
     *   3. charge() -> j_debut_propre, j_fin_propre
     *   4. extension : floor(r/2) en bas si voisin_bas existe, ceil(r/2) en haut si voisin_haut existe
     *   5. nx, ny_loc, n_loc, dx, dy, puis contrôles (ny_loc >= 3, r < lignes propres minimales) */
    return 0;
}

int indice_local(const SousDomaine *sd, int i, int j)
{
    /* TODO */
    return 0;
}

void decomposition_afficher(const SousDomaine *sd)
{
    /* TODO : pour q = 0..nb_procs-1 : si rang == q, afficher ; MPI_Barrier(sd->comm) */
}

void decomposition_liberer(SousDomaine *sd)
{
    /* TODO */
}
