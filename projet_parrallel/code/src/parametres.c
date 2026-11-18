/*
 * parametres.c — Lecture et contrôle des paramètres. Spécifications : parametres.h.
 *
 * Fonction interne conseillée (static, à écrire dans ce fichier) :
 *
 *     static int affecter(Params *p, const char *cle, const char *valeur);
 *
 *     Compare cle aux noms des champs (strcmp) et convertit valeur (atoi, atof, strncpy).
 *     La clé « solveur » accepte "gc" ou "bicgstab". Retour : 0 si la clé est connue, 1 sinon.
 *     Elle sert à la fois pour le fichier et pour les surcharges de la ligne de commande.
 *
 * Lecture du fichier : fgets() ligne par ligne, couper au premier '#', puis
 * sscanf(ligne, "%63s %255s", cle, valeur) ; ignorer les lignes vides.
 * Surcharge « cle=valeur » : couper au '=' (strchr), puis appeler affecter().
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parametres.h"

void parametres_defaut(Params *p)
{
    /* TODO : mêmes valeurs que dans params.dat */
}

int parametres_lire(const char *fichier, int nb_surcharges, char **surcharges, Params *p)
{
    /* TODO : parametres_defaut(p), lecture du fichier, puis surcharges */
    return 0;
}

int parametres_verifier(const Params *p, int nb_procs)
{
    /* TODO : contrôles listés dans parametres.h */
    return 0;
}

void parametres_afficher(const Params *p)
{
    /* TODO */
}
