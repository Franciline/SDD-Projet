CC=gcc
GCC_FLAGS=-Wall -g

all: ChainMain

Chaine.o: Chaine.c Chaine.h
	$(CC) $(GCC_FLAGS) -c -lm $< -o $@

ChainMain: Chaine.h ChainMain.c Chaine.o SVGwriter.o Reseau.o
	$(CC) $(GCC_FLAGS) -o $@ $^

SVGwriter.o: SVGwriter.c SVGwriter.h
	$(CC) $(GCC_FLAGS) -c $< -o $@

Reseau.o: Reseau.c Reseau.h
	$(CC) $(GCC_FLAGS) -c $< -o $@

clean:
	rm -f *.o
