CC=gcc
GCC_FLAGS=-Wall -g

all: ChainMain

Chaine.o: Chaine.c Chaine.h
	$(CC) $(GCC_FLAGS) -c $< -o $@

ChainMain: Chaine.h ChainMain.c Chaine.o
	$(CC) $(GCC_FLAGS) -o $@ $^


clean:
	rm -f *.o
