#!/usr/bin/env bash
# =============================================================================
#  job_plafrim.sh — Gabarit de job SLURM pour PlaFRIM (à adapter).
#  Soumission : sbatch scripts/job_plafrim.sh        Suivi : squeue -u $USER
#  À vérifier sur PlaFRIM : noms exacts des modules (module avail), type de nœud (--constraint),
#  nombre de cœurs par nœud (lscpu sur un nœud de calcul).
# =============================================================================
#SBATCH --job-name=chaleur_schwarz
#SBATCH --nodes=1
#SBATCH --ntasks=32
#SBATCH --time=00:30:00
#SBATCH --output=slurm-%j.out
##SBATCH --constraint=bora       # TODO : type de nœud, à vérifier
##SBATCH --exclusive             # nœud entier : mesures de temps plus fiables

set -euo pipefail
cd "${SLURM_SUBMIT_DIR:-.}"

# TODO : charger les modules (noms à vérifier avec « module avail »), par exemple :
# module purge
# module load compiler/gcc mpi/openmpi

# TODO : make clean && make
#        relever l'environnement (module list, lscpu, mpirun --version) dans resultats/env_plafrim.txt
#        NP_LIST="1 2 4 8 16 32" ./scripts/run_speedup.sh
echo "scripts/job_plafrim.sh : gabarit à compléter (voir l'en-tête)."
