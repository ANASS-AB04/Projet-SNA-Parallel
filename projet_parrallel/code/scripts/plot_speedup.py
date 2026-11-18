#!/usr/bin/env python3
"""plot_speedup.py — Courbes de speed-up et d'efficacité à partir du CSV de performance (à écrire).

Colonnes du CSV (écrites par sorties_bilan_perf, voir src/sorties.h) :
    np,Nx,Ny,recouvrement,alpha,beta,solveur,comm_non_bloquante,dt,nb_pas,
    it_schwarz,it_solveur,t_total,t_solveur,t_comm,t_reduction

Définitions (T = t_total, minimum sur les répétitions) :
    S(p)   = T(1) / T(p)            speed-up
    E(p)   = S(p) / p               efficacité
    E_f(p) = T(1, N) / T(p, p N)    efficacité en scalabilité faible

Usage prévu :
    python3 scripts/plot_speedup.py resultats/perf.csv --mode forte  --sortie resultats/figures
    python3 scripts/plot_speedup.py resultats/perf.csv --mode faible --sortie resultats/figures

Bibliothèques : csv (ou numpy), argparse, matplotlib.
"""


def lire_csv(chemin):
    """Lit le CSV et retourne une liste de dictionnaires (une entrée par exécution)."""
    raise NotImplementedError


def grouper(runs, cles):
    """Regroupe les exécutions par configuration.

    Exemple : cles = ("Nx", "Ny", "recouvrement", "alpha", "beta", "solveur").
    Retourne un dictionnaire {tuple des valeurs des cles: liste des runs}.
    """
    raise NotImplementedError


def speedup_fort(runs):
    """Pour une configuration : liste triée de (p, T(p), S(p), E(p)), T(p) = min des répétitions."""
    raise NotImplementedError


def efficacite_faible(runs, lignes_par_proc):
    """Efficacité en scalabilité faible : liste de (p, T(1, N) / T(p, p N))."""
    raise NotImplementedError


def tracer(resultats, mode, dossier_sortie):
    """Trace S(p) avec la droite idéale S = p, E(p), et le nombre d'itérations de Schwarz en
    fonction de p. Enregistre les figures (PDF ou PNG) dans dossier_sortie."""
    raise NotImplementedError


def main():
    """Arguments : chemin du CSV, --mode forte|faible, --sortie <dossier>.
    Enchaîne lire_csv -> grouper -> speedup_fort ou efficacite_faible -> tracer."""
    raise NotImplementedError


if __name__ == "__main__":
    main()
