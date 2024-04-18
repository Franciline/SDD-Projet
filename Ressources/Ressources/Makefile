CC=gcc
GCC_FLAGS=-Wall -g

all: test_Chaine ReconstitueReseau comparaison_structure comparaison_structure_graphe test_ABQ test_File test_graphe test_Hachage

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

comparaison_structure: comparaison_structure.c Reseau.o Chaine.o SVGwriter.o Hachage.o ArbreQuat.o
	$(CC) $(GCC_FLAGS) -o $@ $^ -lm

comparaison_structure_graphe: comparaison_structure_graphe.c Reseau.o Chaine.o SVGwriter.o Hachage.o ArbreQuat.o
	$(CC) $(GCC_FLAGS) -o $@ $^ -lm

test_Chaine: Chaine.h test_Chaine.c Chaine.o SVGwriter.o Reseau.o
	$(CC) $(GCC_FLAGS) -o $@ $^ -lm

test_Hachage: test_Hachage.c Reseau.o Chaine.o SVGwriter.o Hachage.o
	$(CC) $(GCC_FLAGS) -o $@ $^ -lm

test_ABQ: test_ABQ.c Reseau.o Chaine.o SVGwriter.o ArbreQuat.o
	$(CC) $(GCC_FLAGS) -o $@ $^ -lm

test_file: test_file.c File.o graphe.o Reseau.o SVGwriter.o
	$(CC) $(GCC_FLAGS) -o $@ $^ 

test_File: test_File.c File.o graphe.o Reseau.o SVGwriter.o
	$(CC) $(GCC_FLAGS) -o $@ $^ 

test_graphe: test_graphe.c File.o graphe.o Reseau.o SVGwriter.o ArbreQuat.o Chaine.o
	$(CC) $(GCC_FLAGS) -o $@ $^ -lm


clean:
	rm -f *.o
	rm -f ReconstitueReseau
	rm -f comparaison_structure
	rm -f test_Chaine
	rm -f test_ABQ
	rm -f comparaison_structure_graphe
	rm -f test_File
	rm -f test_Hachage
	rm -f test_graphe
	rm -f cpu_lc.txt
	rm -f cpu_hash_abr.txt
	rm -f comparaison.txt
	rm -f ecriture_reseau_Liste.txt
	rm -f ecriture_reseau_Hachage.txt
	rm -f ecriture_reseau_Arbre.txt
	rm -f test_ecriture_chaine.txt
	rm -f *.html
	rm -f vgcore.*

