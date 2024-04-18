#include "Chaine.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*Test de la structure Chaine*/
int main(int argc, char** argv){
    if (argc < 2){
        printf("Il faut 1 argument!: %s  <nom_du_source>\n", argv[0]);
        return -1;
    }   

    FILE * source = fopen(argv[1], "r");
    FILE * destination = fopen("test_ecriture_chaine.txt", "w");

    //Test de la fonction lecture
    Chaines* chaine = lectureChaines(source);
    assert(chaine != NULL);
    
    //Test de la fonction écriture
    ecrireChaines(chaine, destination);

    //Test SVGwriter, verification en ouvrant le fichier
    afficheChainesSVG(chaine, "affichage_chaine");

    liberer_chaine(chaine);
    fclose(source);
    fclose(destination);

    return 0;
    
}