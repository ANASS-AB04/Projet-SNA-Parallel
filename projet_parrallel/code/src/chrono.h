/*
 * chrono.h — Mesures de performance : temps et compteurs cumulés d'un processus.
 *
 * Pas de fonction à écrire : tout se fait avec MPI_Wtime().
 *
 *     Chronos c = {0};                 // tous les champs à zéro
 *     double t0 = MPI_Wtime();
 *     ...                              // phase mesurée (ex. résolution locale)
 *     c.solveur += MPI_Wtime() - t0;
 *
 * Les temps sont LOCAUX à chaque processus. sorties_bilan_perf() en prend le maximum :
 * c'est le processus le plus lent qui fixe le temps parallèle.
 */
#ifndef CHRONO_H
#define CHRONO_H

typedef struct {
    /* Temps cumulés (secondes) */
    double total;       /* boucle en temps complète (hors lecture, allocations, sorties finales) */
    double solveur;     /* résolutions locales (GC ou BiCGStab)                                  */
    double comm;        /* échanges d'interface avec les voisins (schwarz_echanger)              */
    double reduction;   /* réductions globales des critères d'arrêt (ecart_max_global)           */
    double sorties;     /* écritures de fichiers pendant la boucle en temps                      */

    /* Compteurs cumulés */
    long nb_pas;        /* pas de temps effectués                                                */
    long it_schwarz;    /* itérations de Schwarz, sommées sur tous les pas de temps              */
    long it_solveur;    /* itérations du solveur local, sommées sur toutes les résolutions       */
} Chronos;

#endif /* CHRONO_H */
