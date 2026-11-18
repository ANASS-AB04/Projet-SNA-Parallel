/*
 * sorties.h — Fichiers de résultats, erreurs et bilan de performance.
 *
 * Fichiers solution, dans p->dossier_sortie :
 *   sol_<rang>.dat              solution finale
 *   instant_<n>_<rang>.dat      instantané du pas n (n sur 6 chiffres), si freq_sortie > 0
 * Une ligne « x y u u_exacte » par point PROPRE (lignes j_debut_propre..j_fin_propre), avec
 * une ligne vide après chaque ligne j (format attendu par gnuplot pour pm3d). Pour le cas 3,
 * sans solution exacte, la 4e colonne vaut 0.
 * Tracé :
 *   gnuplot -p -e 'set pm3d map; splot for [f in system("ls resultats/sol_*.dat")] f u 1:2:3 w pm3d notitle'
 */
#ifndef SORTIES_H
#define SORTIES_H

#include "parametres.h"
#include "decomposition.h"
#include "chrono.h"

/*
 * Crée p->dossier_sortie et le dossier de p->fichier_perf s'ils n'existent pas, dossiers parents
 * compris (comme mkdir -p). C'est le rang 0 qui crée, puis MPI_Barrier.
 * Retour : 0 si tout va bien.
 */
int sorties_preparer(const Params *p, const SousDomaine *sd);

/*
 * Écrit la solution locale, sur les lignes propres uniquement.
 * n >= 0 : instantané du pas n ; n < 0 : solution finale.
 */
void sorties_ecrire_solution(const Params *p, const SousDomaine *sd, const double *u, int n);

/*
 * Erreurs GLOBALES par rapport à probleme_u_exacte(), sur les lignes propres :
 *   e_inf = max |u − u_ex|                     (MPI_Allreduce MPI_MAX)
 *   e_l2  = sqrt( dx dy somme (u − u_ex)² )    (MPI_Allreduce MPI_SUM)
 * Le rang 0 affiche une ligne facile à extraire par les scripts :
 *   ERREUR cas=<cas> Nx=<Nx> Ny=<Ny> np=<np> einf=<e_inf> el2=<e_l2>
 */
void sorties_erreurs(const Params *p, const SousDomaine *sd, const double *u,
                     double *e_inf, double *e_l2);

/*
 * Bilan de performance : MPI_Reduce (MPI_MAX) des temps et de it_solveur vers le rang 0.
 * it_schwarz est identique sur tous les processus, puisque le critère est global.
 * Le rang 0 affiche le bilan et ajoute une ligne à p->fichier_perf, en écrivant l'en-tête si
 * le fichier n'existe pas encore. Colonnes :
 *   np,Nx,Ny,recouvrement,alpha,beta,solveur,comm_non_bloquante,dt,nb_pas,
 *   it_schwarz,it_solveur,t_total,t_solveur,t_comm,t_reduction
 */
void sorties_bilan_perf(const Params *p, const SousDomaine *sd, const Chronos *c);

#endif /* SORTIES_H */
