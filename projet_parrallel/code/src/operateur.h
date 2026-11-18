/*
 * operateur.h — Opérateur discret local (la matrice n'est jamais stockée) et second membre.
 *
 * Euler implicite + différences finies centrées à 5 points, avec cx = D dt / dx², cy = D dt / dy² :
 *
 *   (1 + 2cx + 2cy) u_ij − cx (u_{i-1,j} + u_{i+1,j}) − cy (u_{i,j-1} + u_{i,j+1}) = u^n_ij + dt f^{n+1}_ij
 *
 * Les voisins situés HORS du sous-domaine (bords physiques, lignes fantômes) sont connus :
 * on les passe au second membre. L'opérateur A_loc n'agit donc que sur les inconnues locales.
 * Sans Robin, A_loc est symétrique définie positive, à diagonale strictement dominante
 * (grâce au terme 1), pentadiagonale : gradient conjugué.
 *
 * Ligne d'interface Robin (alpha != 0). Côté haut, ligne locale J = ny_loc − 1, le nœud fantôme
 * J + 1 est éliminé comme dans le TP Schwarz Robin (éq. 3 à 5) :
 *
 *   alpha (u_{J+1} − u_{J-1}) / (2 dy) + beta u_J = R            (R calculé par le voisin)
 *   =>  diag_robin u_J − cx (u_{i-1,J} + u_{i+1,J}) − 2 cy u_{J-1} = u^n + dt f + cy (2 dy / alpha) R
 *   avec diag_robin = 1 + 2cx + 2cy + 2 cy beta dy / alpha.
 *
 * Même chose côté bas (ligne locale 0, coefficient −2cy vers la ligne 1).
 * Le −2cy casse la symétrie -> BiCGStab. Variante à discuter dans le rapport : multiplier ces
 * lignes par 1/2 redonne une matrice symétrique définie positive.
 *
 * Tableaux de bord (taille nx), utilisés UNIQUEMENT dans le second membre :
 *   bord_bas[i-1]  : valeur « sous » la ligne locale 0           -> + cy * bord_bas[i-1]
 *   bord_haut[i-1] : valeur « sur » la ligne locale ny_loc − 1   -> + cy * bord_haut[i-1]
 *   Contenu : g (bord physique), valeur du voisin (Dirichlet) ou (2 dy / alpha) R (Robin).
 */
#ifndef OPERATEUR_H
#define OPERATEUR_H

#include "parametres.h"
#include "decomposition.h"

typedef struct {
    int    nx, ny_loc;            /* dimensions locales (n = nx * ny_loc)                          */
    double diag;                  /* 1 + 2cx + 2cy                                                 */
    double cx, cy;                /* D dt / dx², D dt / dy²                                        */
    int    robin_bas, robin_haut; /* 1 si la ligne locale 0 (resp. ny_loc − 1) porte une condition Robin */
    double diag_robin;            /* diag + 2 cy beta dy / alpha (lignes Robin)                    */
} Operateur;

/*
 * Calcule les coefficients. Active robin_bas (resp. robin_haut) si alpha != 0 ET s'il y a un
 * voisin en bas (resp. en haut). Un bord physique reste toujours de type Dirichlet.
 */
void operateur_init(Operateur *op, const Params *p, const SousDomaine *sd);

/*
 * y = A_loc x, avec x et y de taille nx * ny_loc et x != y.
 * Un voisin hors du sous-domaine ne contribue pas (il est dans le second membre).
 * Lignes Robin : diag_robin sur la diagonale, −2cy vers la ligne intérieure, rien vers l'extérieur.
 */
void operateur_appliquer(const Operateur *op, const double *x, double *y);

/*
 * Second membre au temps t = t^{n+1} (k = indice du point (i, j)) :
 *   b_k = u_n[k] + dt f(x_i, y_j, t)
 *         + cx h(0,  y_j, t)   si i = 1
 *         + cx h(Lx, y_j, t)   si i = Nx
 *         + cy bord_bas[i-1]   si ligne locale 0
 *         + cy bord_haut[i-1]  si ligne locale ny_loc − 1
 * La même formule sert en Dirichlet et en Robin : seul le contenu de bord_* change.
 */
void operateur_second_membre(const Operateur *op, const Params *p, const SousDomaine *sd,
                             const double *u_n, double t,
                             const double *bord_bas, const double *bord_haut, double *b);

#endif /* OPERATEUR_H */
