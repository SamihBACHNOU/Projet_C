all: generation_aleatoire sortie_dimacs affichage_solution


generation_aleatoire: generation_aleatoire.c  grille_du_jeux.o
	$(CC) $^ -o $@

sortie_dimacs: sortie_dimacs.c grille_du_jeux.o manipulation_fnc.o dimacs.o lecture.o
	$(CC) $^ -lm -o $@

affichage_solution: affichage_solution.c grille_du_jeux.o lecture.o
	$(CC) $^ -o $@

%.o: %.c %.h
	$(CC) -c $< -o $@

.PHONY: clean

clean:
	rm -f *.o
