# Chaleur 2D : Schwarz additif en C + MPI

Projet de Programmation CHP, Partie II (ENSEIRB-MATMECA).

Le code résout ∂t u − D Δu = f sur [0,Lx]×[0,Ly], avec u = g sur Γ0 (bords bas et haut) et u = h sur Γ1 (bords gauche et droit). La discrétisation utilise des différences finies centrées à 5 points et Euler implicite.

Le domaine est découpé en bandes horizontales avec recouvrement :
- chaque processus résout son sous-domaine avec le GC ou BiCGStab (matrice non stockée) ;
- les sous-domaines échangent leurs données d'interface (Dirichlet ou Robin) à chaque itération de Schwarz.

> État : **squelette**. Structures et prototypes sont définis et documentés dans `src/*.h`. Les corps de fonctions sont à écrire (`TODO`).

## Arborescence

| Fichier | Rôle |
|---|---|
| `src/main.c` | boucle en temps et boucle de Schwarz (algorithme détaillé en tête du fichier) |
| `src/parametres.[ch]` | lecture de `params.dat` et des surcharges `cle=valeur` |
| `src/probleme.[ch]` | f, g, h, solutions exactes des cas 1 à 3, condition initiale, bords physiques |
| `src/decomposition.[ch]` | bandes, recouvrement, topologie cartésienne 1D, voisins |
| `src/operateur.[ch]` | produit matrice-vecteur sans matrice, second membre, lignes Robin |
| `src/solveurs.[ch]` | gradient conjugué et BiCGStab locaux |
| `src/schwarz.[ch]` | échanges d'interface (bloquants ou non bloquants), critère d'arrêt global |
| `src/sorties.[ch]` | fichiers solution, erreurs, bilan de performance (CSV) |
| `src/chrono.h` | temps et compteurs cumulés |
| `scripts/` | validation, campagne de speed-up, tracés, comparaison de solutions, job PlaFRIM |

## Compilation

```bash
make            # version optimisée -> ./chaleur
make debug      # -O0 -g + AddressSanitizer / UBSan
make prof       # instrumentation gprof (-pg)
make clean
```

Après `make debug` ou `make prof`, refaire `make clean && make` avant toute mesure de performance.

Environnements utilisés (à compléter) :

| Machine | Processeur / cœurs | Compilateur | MPI | Modules |
|---|---|---|---|---|
| Portable (WSL2) | i7-1165G7, 4 cœurs / 8 threads | gcc 13.3.0 | Open MPI 4.1.6 | — |
| CREMI ou PlaFRIM | … | … | … | … |

## Exécution

```bash
mpirun -np 4 ./chaleur params.dat
mpirun -np 4 ./chaleur params.dat cas=1 dt=1 Tf=1000 Nx=200 Ny=200    # surcharges cle=valeur
```

Sur le portable (4 cœurs physiques), au-delà de 4 processus il faut `mpirun --oversubscribe ...`. Les mesures de speed-up ne sont alors plus représentatives : à signaler dans le rapport.

## Paramètres

Tous sont dans `params.dat`, commentés. Les principaux :

| Clé | Rôle |
|---|---|
| `Nx`, `Ny` | nombre d'inconnues intérieures en x et en y |
| `dt`, `Tf` | pas de temps et temps final |
| `cas` | 1, 2 (stationnaires, solution exacte) ou 3 (périodique) |
| `solveur` | `gc` ou `bicgstab` |
| `recouvrement` | r = nombre de lignes communes à deux sous-domaines voisins |
| `alpha`, `beta` | transmission α ∂u/∂n + β u (α = 0 : Dirichlet) |
| `tol_solveur`, `tol_schwarz`, `tol_stationnaire` | critères d'arrêt |
| `comm_non_bloquante` | 0 : `MPI_Sendrecv` ; 1 : `MPI_Isend` / `MPI_Irecv` |

## Sorties

- `resultats/sol_<rang>.dat` : solution finale, au format `x y u u_exacte`, sur les lignes propres du processus.
- `resultats/instant_<n>_<rang>.dat` : instantanés, si `freq_sortie > 0`.
- Tracé :
  `gnuplot -p -e 'set pm3d map; splot for [f in system("ls resultats/sol_*.dat")] f u 1:2:3 w pm3d notitle'`
- Cas 1 et 2 : une ligne `ERREUR cas=… Nx=… Ny=… np=… einf=… el2=…` est affichée sur la sortie standard.
- `resultats/perf.csv` : une ligne par exécution (colonnes décrites dans `src/sorties.h`).

## Profilage (gprof)

```bash
make prof
GMON_OUT_PREFIX=gmon mpirun -np 4 ./chaleur params.dat   # un fichier gmon.<pid> par processus
gprof ./chaleur gmon.<pid> > profil.txt
```

## Scripts

| Script | Rôle |
|---|---|
| `scripts/valider.sh` | cas 1 (erreur ≈ 0), cas 2 (ordre 2), GC contre BiCGStab, Np > 1 contre Np = 1 |
| `scripts/run_speedup.sh` | campagne Np × tailles → CSV, plus relevé de l'environnement |
| `scripts/plot_speedup.py` | speed-up, efficacité (scalabilité forte et faible), itérations de Schwarz |
| `scripts/comparer_solutions.py` | écart max entre deux exécutions (validation du cas 3) |
| `scripts/job_plafrim.sh` | gabarit de job SLURM |

## Avancement

- [ ] `parametres`, `probleme`
- [ ] `decomposition` pour Np = 1
- [ ] `operateur` + `gradient_conjugue` + `main` → validation séquentielle (cas 1, 2, 3)
- [ ] `decomposition` pour Np > 1
- [ ] `schwarz` : échanges Dirichlet + critère d'arrêt → validation Np > 1
- [ ] mesures de performance (portable + CREMI ou PlaFRIM), gprof
- [ ] Robin + `bicgstab`
- [ ] (option) grille grossière
