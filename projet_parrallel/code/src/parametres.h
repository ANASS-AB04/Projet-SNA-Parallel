/*
 * parametres.h — Paramètres du calcul.
 *
 * Ils sont lus dans un fichier texte (params.dat) au format « cle valeur », une paire par
 * ligne, « # » commençant un commentaire :
 *
 *     Nx       100
 *     solveur  gc        # gc | bicgstab
 *
 * puis surchargeables en ligne de commande par des arguments « cle=valeur » :
 *
 *     mpirun -np 4 ./chaleur params.dat Nx=400 Ny=400 recouvrement=4
 *
 * Les clés portent exactement le nom des champs de la structure Params.
 */
#ifndef PARAMETRES_H
#define PARAMETRES_H

#define LONGUEUR_CHEMIN 256

typedef enum {
    SOLVEUR_GC       = 0,   /* gradient conjugué : matrice SPD (transmission Dirichlet) */
    SOLVEUR_BICGSTAB = 1    /* BiCGStab : matrice non symétrique (transmission Robin)    */
} TypeSolveur;

typedef struct {
    /* --- Domaine [0,Lx] x [0,Ly] et maillage ------------------------------------------- */
    int    Nx, Ny;             /* nombre d'inconnues INTÉRIEURES en x et en y              */
    double Lx, Ly;             /* dimensions du domaine                                    */
    double D;                  /* coefficient de diffusion                                 */

    /* --- Temps (Euler implicite) -------------------------------------------------------- */
    double dt;                 /* pas de temps                                             */
    double Tf;                 /* temps final : nb_pas = arrondi(Tf / dt)                  */
    double tol_stationnaire;   /* cas 1-2 : arrêt si max|u^{n+1} - u^n| < tol (0 : jamais) */

    /* --- Cas test (énoncé, section 2) --------------------------------------------------- */
    int    cas;                /* 1, 2 : stationnaires (solution exacte) ; 3 : périodique  */

    /* --- Solveur linéaire local --------------------------------------------------------- */
    TypeSolveur solveur;       /* clé « solveur » : gc | bicgstab                          */
    double tol_solveur;        /* arrêt si ||b - A x|| <= tol_solveur * ||b||              */
    int    itmax_solveur;

    /* --- Décomposition de domaine et Schwarz additif ------------------------------------ */
    int    recouvrement;       /* r : nombre de lignes d'inconnues communes à deux voisins */
    double alpha, beta;        /* transmission alpha du/dn + beta u ; alpha = 0 : Dirichlet */
    double tol_schwarz;        /* arrêt si max global |u^{k+1} - u^k| < tol_schwarz        */
    int    itmax_schwarz;
    int    comm_non_bloquante; /* 0 : MPI_Sendrecv ; 1 : MPI_Isend/MPI_Irecv + MPI_Waitall */

    /* --- Sorties ------------------------------------------------------------------------ */
    int    freq_sortie;                     /* instantané tous les freq_sortie pas (0 : solution finale seulement) */
    char   dossier_sortie[LONGUEUR_CHEMIN]; /* dossier des fichiers solution                 */
    char   fichier_perf[LONGUEUR_CHEMIN];   /* CSV des mesures de performance (1 ligne / run) */
} Params;

/*
 * Remplit p avec les valeurs par défaut (les mêmes que dans params.dat), pour que toute
 * clé absente du fichier ait une valeur définie.
 */
void parametres_defaut(Params *p);

/*
 * Appelle parametres_defaut(), lit le fichier, puis applique les surcharges.
 *   fichier       : chemin du fichier de paramètres (argv[1])
 *   nb_surcharges : nombre de chaînes « cle=valeur » (argc - 2)
 *   surcharges    : ces chaînes (argv + 2)
 * Une clé inconnue est une erreur (évite les fautes de frappe silencieuses).
 * Chaque processus lit le fichier lui-même (petit fichier, pas besoin de MPI_Bcast).
 * Retour : 0 si tout va bien, non nul sinon (message sur stderr).
 */
int parametres_lire(const char *fichier, int nb_surcharges, char **surcharges, Params *p);

/*
 * Contrôle la cohérence des paramètres :
 *   - Nx, Ny >= 1 ; Lx, Ly, D, dt > 0 ; Tf >= dt ; cas dans {1, 2, 3} ;
 *   - tolérances > 0, itmax > 0, recouvrement >= 0 ;
 *   - Robin (alpha != 0) : recouvrement >= 2 (le voisin utilise les lignes J-1, J, J+1) ;
 *   - avertissement si Robin avec solveur gc (matrice non symétrique) ;
 *   - avertissement si tol_solveur n'est pas très inférieure à tol_schwarz ;
 *   - Ny suffisant pour nb_procs bandes d'au moins 3 lignes.
 * Retour : 0 si tout va bien, non nul sinon (message sur stderr).
 */
int parametres_verifier(const Params *p, int nb_procs);

/* Affiche tous les paramètres (à n'appeler que sur le rang 0). */
void parametres_afficher(const Params *p);

#endif /* PARAMETRES_H */
