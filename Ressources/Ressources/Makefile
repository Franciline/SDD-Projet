all: ChainMain

Chaine.o: Chaine.h Chaine.c
	gcc -c Chaine.c

ChainMain: Chaine.h ChainMain.c Chaine.o
	gcc -o ChainMain ChainMain.c Chaine.o


clean:
	rm *.o