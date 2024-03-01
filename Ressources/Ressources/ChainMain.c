#include "Chaine.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    if (argc < 2){
        printf("Il faut 1 arguments!: %s  <nom_du_fichier>\n", argv[0]);
        return -1;
    }   

    FILE * fichier = fopen(argv[1], "r");
    FILE * fichier2 = fopen("test_ecriture.txt", "w");

    //Test de la fonction lecture
    Chaines* test = lectureChaines(fichier);
    
    //Test de la fonction écriture
    ecrireChaines(test, fichier2);

    fclose(fichier);
    fclose(fichier2);
    

    //TEST SVGwriter
    afficheChainesSVG(test, "affichage_test");

    return 0;
    
}