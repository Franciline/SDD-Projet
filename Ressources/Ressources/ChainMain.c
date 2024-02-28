#include "Chaine.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    if (argc < 2){
        printf("Il faut 1 arguments!: %s  <nom_du_fichier>\n", argv[0]);
        return -1;
    }   

    FILE * fichier = fopen(argv[1], "r");
    FILE * fichier2 = fopen("test.txt", "w");
    Chaines* test = lectureChaines(fichier);
    fclose(fichier);
    ecrireChaines(test, fichier2);

    //Test de la fonction écriture
    
}