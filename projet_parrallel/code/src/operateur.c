/*
 * operateur.c — Produit matrice-vecteur sans matrice et second membre. Spécifications : operateur.h.
 *
 * Conseils :
 *   - boucle sur les lignes locales jl = 0..ny_loc-1, puis sur les colonnes il = 0..nx-1, avec k = jl*nx + il ;
 *   - un voisin hors du sous-domaine (il-1 < 0, il+1 >= nx, jl-1 < 0, jl+1 >= ny_loc) ne contribue pas
 *     au produit : sa valeur est dans le second membre ;
 *   - coder d'abord sans Robin (robin_bas = robin_haut = 0), valider en séquentiel, puis ajouter
 *     les lignes Robin.
 */
#include "operateur.h"
#include "probleme.h"

void operateur_init(Operateur *op, const Params *p, const SousDomaine *sd)
{
    /* TODO */
}

void operateur_appliquer(const Operateur *op, const double *x, double *y)
{
    /* TODO */
}

void operateur_second_membre(const Operateur *op, const Params *p, const SousDomaine *sd,
                             const double *u_n, double t,
                             const double *bord_bas, const double *bord_haut, double *b)
{
    /* TODO : coordonnées globales x_i = i*dx (i = 1..Nx), y_j = j*dy (j = j_debut..j_fin) */
}
