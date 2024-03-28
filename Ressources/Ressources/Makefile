CC=gcc
GCC_FLAGS=-Wall -g

all: ChainMain ReconstitueReseau comparaison_structure

Chaine.o: Chaine.c Chaine.h SVGwriter.c SVGwriter.h
	$(CC) $(GCC_FLAGS) -c $< -o $@ -lm 


SVGwriter.o: SVGwriter.c SVGwriter.h
	$(CC) $(GCC_FLAGS) -c $< -o $@

Reseau.o: Reseau.c Reseau.h SVGwriter.h Hachage.h Chaine.h
	$(CC) $(GCC_FLAGS) -c $< -o $@

ChainMain: Chaine.h ChainMain.c Chaine.o SVGwriter.o Reseau.o
	$(CC) $(GCC_FLAGS) -o $@ $^ -lm

Hachage.o: Hachage.c Hachage.h Reseau.h
	$(CC) $(GCC_FLAGS) -c $< -o $@ -lm

ArbreQuat.o: ArbreQuat.c ArbreQuat.h Reseau.h
	$(CC) $(GCC_FLAGS) -c $< -o $@ 

ReconstitueReseau: ReconstitueReseau.c Reseau.o Chaine.o SVGwriter.o Hachage.o ArbreQuat.o
	$(CC) $(GCC_FLAGS) -o $@ $^ -lm

main_test_ABQ: main_test_ABQ.c Reseau.o Chaine.o SVGwriter.o ArbreQuat.o
	$(CC) $(GCC_FLAGS) -o $@ $^ -lm

comparaison_structure: comparaison_structure.c Reseau.o Chaine.o SVGwriter.o Hachage.o ArbreQuat.o
	$(CC) $(GCC_FLAGS) -o $@ $^ -lm


clean:
	rm -f *.o
	rm -f ReconstitueReseau
	rm -f comparaison_structure
	rm -f ChainMain
	rm -f main_test_ABQ
	rm -f ecriture_reseau_Liste.txt
	rm -f ecriture_reseau_Hachage.txt
	rm -f ecriture_reseau_Arbre.txt
	rm -f comparaison.txt
	rm -f *.html
	rm -f vgcore.*

