CC=gcc
GCC_FLAGS=-Wall -g

all: ReconstitueReseau comparaison_structure comparaison_structure_graphe main_reorganiseReseau
test: test_Chaine test_Hachage test_ABQ test_File test_graphe test_Reseau

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

main_reorganiseReseau: main_reorganiseReseau.c Reseau.o Chaine.o SVGwriter.o ArbreQuat.o graphe.o File.o
	$(CC) $(GCC_FLAGS) -o $@ $^ -lm

test_Chaine: Chaine.h test_Chaine.c Chaine.o SVGwriter.o Reseau.o
	$(CC) $(GCC_FLAGS) -o $@ $^ -lm

test_Hachage: test_Hachage.c Reseau.o Chaine.o SVGwriter.o Hachage.o
	$(CC) $(GCC_FLAGS) -o $@ $^ -lm

test_ABQ: test_ABQ.c Reseau.o Chaine.o SVGwriter.o ArbreQuat.o
	$(CC) $(GCC_FLAGS) -o $@ $^ -lm

test_File: test_File.c File.o graphe.o Reseau.o SVGwriter.o
	$(CC) $(GCC_FLAGS) -o $@ $^ 

test_graphe: test_graphe.c File.o graphe.o Reseau.o SVGwriter.o ArbreQuat.o Chaine.o
	$(CC) $(GCC_FLAGS) -o $@ $^ -lm

test_Reseau: test_Reseau.c File.o graphe.o Reseau.o SVGwriter.o Chaine.o
	$(CC) $(GCC_FLAGS) -o $@ $^ -lm

clean:
	rm -f *.o
	rm -f ReconstitueReseau
	rm -f comparaison_structure
	rm -f main_reorganiseReseau
	rm -f comparaison_structure_graphe
	rm -f test_*
	rm -f *.txt
	rm -f *.html
	rm -f vgcore.*
	rm -f *.ps
