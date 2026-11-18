/*
 * main.c — Équation de la chaleur 2D instationnaire, décomposition de domaine de Schwarz
 *          additif (C + MPI).
 *
 * Usage : mpirun -np <Np> ./chaleur params.dat [cle=valeur ...]
 *
 * Algorithme (à coder, dans cet ordre) :
 *
 *  1. MPI_Init. Paramètres : parametres_lire(argv[1], argc - 2, argv + 2, &p), puis
 *     parametres_verifier(&p, nb_procs) ; le rang 0 appelle parametres_afficher().
 *     En cas d'erreur : MPI_Abort(MPI_COMM_WORLD, 1).
 *
 *  2. decomposition_construire(&p, MPI_COMM_WORLD, &sd).
 *     Ensuite, utiliser sd.comm plutôt que MPI_COMM_WORLD.
 *
 *  3. operateur_init(&op, &p, &sd) ; travail_allouer(&w, sd.n_loc) ; schwarz_allouer(&ts, &sd).
 *     Allouer u, u_n, u_prec, b (taille sd.n_loc) et bord_bas, bord_haut (taille sd.nx).
 *
 *  4. probleme_condition_initiale(&p, &sd, u) ; sorties_preparer(&p, &sd) ; Chronos c = {0}.
 *
 *  5. Boucle en temps, nb_pas = (int) round(Tf / dt), chronométrée par MPI_Wtime()
 *     après un MPI_Barrier :
 *
 *       pour n = 1 .. nb_pas :
 *         t = n * dt ; copier u dans u_n
 *         probleme_bords_physiques(&p, &sd, t, bord_bas, bord_haut)
 *
 *         pour k = 0 .. itmax_schwarz - 1 :                          (boucle de Schwarz)
 *           schwarz_echanger(&p, &sd, u, &ts, bord_bas, bord_haut, &c)
 *           operateur_second_membre(&op, &p, &sd, u_n, t, bord_bas, bord_haut, b)
 *           copier u dans u_prec
 *           it = solveur_resoudre(&p, &op, b, u, &w)       (ajouter à c.solveur et c.it_solveur)
 *           c.it_schwarz++
 *           si sd.nb_procs == 1 : sortir (un seul domaine, pas d'itérations de Schwarz)
 *           si ecart_max_global(&sd, u, u_prec, &c) < tol_schwarz : sortir
 *         (si itmax_schwarz est atteint : avertissement « Schwarz non convergé »)
 *
 *         si probleme_est_stationnaire(&p) et tol_stationnaire > 0
 *            et ecart_max_global(&sd, u, u_n, &c) < tol_stationnaire : sortir (état stationnaire)
 *         si freq_sortie > 0 et n % freq_sortie == 0 :
 *            sorties_ecrire_solution(&p, &sd, u, n)                 (ajouter à c.sorties)
 *
 *       c.total = temps de la boucle ; c.nb_pas = nombre de pas effectués
 *
 *  6. sorties_ecrire_solution(&p, &sd, u, -1) ;
 *     si probleme_est_stationnaire(&p) : sorties_erreurs(&p, &sd, u, &e_inf, &e_l2) ;
 *     sorties_bilan_perf(&p, &sd, &c).
 *
 *  7. Libérer (free, travail_liberer, schwarz_liberer, decomposition_liberer), puis MPI_Finalize.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <mpi.h>

#include "chrono.h"
#include "parametres.h"
#include "decomposition.h"
#include "probleme.h"
#include "operateur.h"
#include "solveurs.h"
#include "schwarz.h"
#include "sorties.h"

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    /* TODO : étapes 1 à 7 décrites ci-dessus */

    MPI_Finalize();
    return 0;
}
