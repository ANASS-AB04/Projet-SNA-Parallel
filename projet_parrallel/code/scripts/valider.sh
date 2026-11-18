#!/usr/bin/env bash
# =============================================================================
#  valider.sh — Validation du code (à écrire). Lancement : make test
#
#  1. Cas 1 (u_ex = x(1−x)y(1−y)), Np = 1 : erreur max ≲ 1e-9 QUEL QUE SOIT N, car le
#     schéma à 5 points est exact pour un polynôme de degré 2 en x et en y.
#       mpirun -np 1 ./chaleur params.dat cas=1 dt=1 Tf=1000 tol_stationnaire=1e-12 Nx=$N Ny=$N
#  2. Cas 2 (u_ex = sin x + cos y), Np = 1, N = 20 40 80 160 : le rapport de deux erreurs
#     successives doit valoir environ 4 (ordre 2 en espace).
#     Récupérer e_inf dans la ligne « ERREUR ... einf=... » (grep, sed ou awk).
#  3. Mêmes cas avec solveur=bicgstab : mêmes erreurs qu'avec gc.
#  4. Une fois Schwarz codé : cas 1 et 2 avec Np = 2 et 4 -> mêmes erreurs qu'avec Np = 1.
#     Cas 3 : comparer Np = 4 à Np = 1 avec scripts/comparer_solutions.py
#     (dossier_sortie=resultats/np1, puis dossier_sortie=resultats/np4).
#  5. Reprendre 4. en Robin (alpha=1, beta à choisir, solveur=bicgstab, recouvrement >= 2).
#
#  Sortie attendue : un tableau N | e_inf | rapport, et OK / ÉCHEC pour chaque test.
# =============================================================================
set -euo pipefail
cd "$(dirname "$0")/.."

# TODO
echo "scripts/valider.sh : à écrire (voir l'en-tête)."
