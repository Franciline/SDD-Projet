CC=gcc
GCC_FLAGS=-Wall -g

all: ChainMain ReconstitueReseau comparaison_structure comparaison_structure_graphe main_test_ABQ main_test_file

Chaine.o: Chaine.c Chaine.h SVGwriter.c SVGwriter.h
	$(CC) $(GCC_FLAGS) -c $< -o $@ -lm 

SVGwriter.o: SVGwriter.c SVGwriter.h
	$(CC) $(GCC_FLAGS) -c $< -o $@

Reseau.o: Reseau.c Reseau.h SVGwriter.h Hachage.h Chaine.h
	$(CC) $(GCC_FLAGS) -c $< -o $@

Hachage.o: Hachage.c Hachage.h Reseau.h
	$(CC) $(GCC_FLAGS) -c $< -o $@ -lm

graphe.o: graphe.c graphe.h Reseau.o
	$(CC) $(GCC_FLAGS) -c $< -o $@ -lm

ArbreQuat.o: ArbreQuat.c ArbreQuat.h Reseau.h
	$(CC) $(GCC_FLAGS) -c $< -o $@ 

File.o: File.c File.h Reseau.o SVGwriter.o graphe.o
	$(CC) $(GCC_FLAGS) -c $< -o $@ 

ReconstitueReseau: ReconstitueReseau.c Reseau.o Chaine.o SVGwriter.o Hachage.o ArbreQuat.o
	$(CC) $(GCC_FLAGS) -o $@ $^ -lm

main_test_ABQ: main_test_ABQ.c Reseau.o Chaine.o SVGwriter.o ArbreQuat.o
	$(CC) $(GCC_FLAGS) -o $@ $^ -lm

comparaison_structure: comparaison_structure.c Reseau.o Chaine.o SVGwriter.o Hachage.o ArbreQuat.o
	$(CC) $(GCC_FLAGS) -o $@ $^ -lm

ChainMain: Chaine.h ChainMain.c Chaine.o SVGwriter.o Reseau.o
	$(CC) $(GCC_FLAGS) -o $@ $^ -lm

comparaison_structure_graphe: comparaison_structure_graphe.c Reseau.o Chaine.o SVGwriter.o Hachage.o ArbreQuat.o
	$(CC) $(GCC_FLAGS) -o $@ $^ -lm

main_test_file: main_test_file.c File.o graphe.o Reseau.o SVGwriter.o
	$(CC) $(GCC_FLAGS) -o $@ $^ 

clean:
	rm -f *.o
	rm -f ReconstitueReseau
	rm -f comparaison_structure
	rm -f ChainMain
	rm -f main_test_ABQ
	rm -f comparaison_structure_graphe
	rm -f cpu_lc.txt
	rm -f cpu_hash_abr.txt
	rm -f comparaison.txt
	rm -f ecriture_reseau_Liste.txt
	rm -f ecriture_reseau_Hachage.txt
	rm -f ecriture_reseau_Arbre.txt
	rm -f *.html
	rm -f vgcore.*

