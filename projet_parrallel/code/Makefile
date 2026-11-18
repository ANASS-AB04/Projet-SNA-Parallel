# =============================================================================
#  Makefile — Chaleur 2D, décomposition de domaine de Schwarz additif (C + MPI)
#
#  make         version optimisée                    -> ./chaleur
#  make debug   -O0 -g + AddressSanitizer / UBSan    (lancer avec ASAN_OPTIONS=detect_leaks=0)
#  make prof    instrumentation gprof (-pg)          (voir README : GMON_OUT_PREFIX)
#  make test    lance scripts/valider.sh
#  make clean   supprime build/, l'exécutable et les fichiers gmon
#
#  Après make debug ou make prof : make clean && make avant toute mesure de performance.
# =============================================================================

CC     = mpicc
# gnu11 : C11 + extensions POSIX (M_PI, mkdir, ...).
# -Wno-unused-parameter : seulement le temps de remplir le squelette (fonctions vides),
#                         à retirer une fois toutes les fonctions codées.
CFLAGS = -std=gnu11 -O3 -Wall -Wextra -Wno-unused-parameter
LDLIBS = -lm

CFLAGS_DEBUG = -std=gnu11 -O0 -g -Wall -Wextra -Wno-unused-parameter -fsanitize=address,undefined -fno-omit-frame-pointer

SRC = $(wildcard src/*.c)
HDR = $(wildcard src/*.h)
OBJ = $(SRC:src/%.c=build/%.o)
EXE = chaleur

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDLIBS)

# Chaque objet dépend de tous les en-têtes : simple et sûr pour un petit projet.
build/%.o: src/%.c $(HDR) | build
	$(CC) $(CFLAGS) -c $< -o $@

build:
	mkdir -p build

debug:
	$(MAKE) clean
	$(MAKE) CFLAGS="$(CFLAGS_DEBUG)"

prof:
	$(MAKE) clean
	$(MAKE) CFLAGS="$(CFLAGS) -pg"

test: $(EXE)
	./scripts/valider.sh

clean:
	rm -rf build $(EXE) gmon.out gmon.[0-9]*

.PHONY: all debug prof test clean
