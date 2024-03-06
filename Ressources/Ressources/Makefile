CC=gcc
GCC_FLAGS=-Wall -g

all: ChainMain ReconstitueReseau

Chaine.o: Chaine.c Chaine.h SVGwriter.c SVGwriter.h
	$(CC) $(GCC_FLAGS) -c $< -o $@ -lm 


SVGwriter.o: SVGwriter.c SVGwriter.h
	$(CC) $(GCC_FLAGS) -c $< -o $@

Reseau.o: Reseau.c Reseau.h SVGwriter.h
	$(CC) $(GCC_FLAGS) -c $< -o $@

ChainMain: Chaine.h ChainMain.c Chaine.o SVGwriter.o Reseau.o
	$(CC) $(GCC_FLAGS) -o $@ $^ -lm

ReconstitueReseau: ReconstitueReseau.c Reseau.o Chaine.o SVGwriter.o
	$(CC) $(GCC_FLAGS) -o $@ $^ -lm


clean:
	rm -f *.o
