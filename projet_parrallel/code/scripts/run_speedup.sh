#!/usr/bin/env bash
# =============================================================================
#  run_speedup.sh — Campagne de mesures pour le speed-up (à écrire).
#
#  Variables, surchargeables à l'appel (ex. NP_LIST="1 2 4 8" ./scripts/run_speedup.sh) :
#    NP_LIST="1 2 4"                nombres de processus
#    N_LIST="200 400 800"           tailles Nx = Ny (scalabilité forte)
#    NREP=3                         répétitions par configuration (garder le min ou la médiane)
#    MPIRUN_OPTS="--bind-to core"   portable : --oversubscribe au-delà des cœurs physiques
#    EXTRA="cas=3 dt=0.01 Tf=1 recouvrement=2"   paramètres communs à tous les runs
#
#  Pour chaque N, chaque np et chaque répétition :
#    mpirun $MPIRUN_OPTS -np $np ./chaleur params.dat Nx=$N Ny=$N $EXTRA \
#           fichier_perf=resultats/perf_<machine>.csv dossier_sortie=resultats/tmp freq_sortie=0
#
#  Scalabilité faible : Ny = np * Ny_par_proc, Nx fixe.
#  Études demandées (énoncé 4a-e) : taille, machine, recouvrement, nombre de sous-domaines,
#  paramètres numériques (solveur, tolérances, alpha/beta, dt...) -> autant de boucles.
#
#  Relevé de l'environnement (exigé par l'énoncé) dans resultats/env_<machine>.txt :
#    hostname, lscpu, gcc --version, mpicc --showme, mpirun --version, module list (PlaFRIM).
# =============================================================================
set -euo pipefail
cd "$(dirname "$0")/.."

# TODO
echo "scripts/run_speedup.sh : à écrire (voir l'en-tête)."
