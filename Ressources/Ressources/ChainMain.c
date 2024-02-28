#include "Chaine.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    if (argc < 2){
        printf("Il faut 1 arguments!: %s  <nom_du_fichier>\n", argv[0]);
        return -1;
    }   

    Chaines* test = lectureChaines(argv[1]);

    //Test de la fonction écriture
    
}