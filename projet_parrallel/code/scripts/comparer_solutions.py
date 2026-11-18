#!/usr/bin/env python3
"""comparer_solutions.py — Écart maximal entre deux calculs (à écrire).

Sert à valider Schwarz sur le cas 3, qui n'a pas de solution exacte : on compare un calcul
avec Np > 1 à la référence Np = 1, sur la même grille.

Usage prévu :
    python3 scripts/comparer_solutions.py resultats/np1 resultats/np4

Fichiers lus : <dossier>/sol_<rang>.dat, lignes « x y u u_exacte » (lignes vides ignorées).
Sortie : max |u_A − u_B| sur les points communs, et le nombre de points comparés.
"""


def lire_solution(dossier):
    """Concatène tous les sol_<rang>.dat du dossier et retourne un dictionnaire {(x, y): u}.

    Arrondir x et y (ex. round(x, 12)) pour que les clés de deux calculs coïncident.
    """
    raise NotImplementedError


def ecart_max(sol_a, sol_b):
    """Retourne (max |u_a − u_b| sur les points communs, nombre de points communs).

    Signaler les points présents dans une seule des deux solutions.
    """
    raise NotImplementedError


def main():
    """Lit les deux dossiers passés en arguments (sys.argv[1], sys.argv[2]) et affiche l'écart."""
    raise NotImplementedError


if __name__ == "__main__":
    main()
