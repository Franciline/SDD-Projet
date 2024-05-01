#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Chaine.h"
#include "Reseau.h"

/*Test de la structure Reseau*/
int main(){

    Chaines* chaines = generationAleatoire(50, 10, 100, 100);
    Reseau* reseau = creer_reseau(2);
    FILE* destination = fopen("test_w_reseau.txt", "w");

    //assert(chaines->nbChaines == nb_commodite(reseau));
    printf("%d %d\n",chaines->nbChaines, nb_commodite(reseau));
    ecrireReseau(reseau, destination);

    liberer_chaine(chaines);
    liberer_reseau(reseau);
    fclose(destination);

}