#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "File.h"
#include "graphe.h"
#include "Reseau.h"
#include "Chaine.h"
#include "ArbreQuat.h"
#include "SVGwriter.h"

clock_t temps_initial;
clock_t temps_final;
double temps;


//Exercice 7

//Question 5

int main(int argc, char** argv) {

    if (argc < 2) {
        printf("Il faut des arguments ! : ./%s <nom_instance> \n", argv[0]);        
        return 1;
    }

    //Ouverture des fichiers
    FILE* inst = fopen(argv[1], "r");
    FILE* destination = fopen("EXO7_Q5.txt", "a");
    Chaines* chaines = lectureChaines(inst);

    Reseau* reseau = reconstitueReseauArbre(chaines);

    //Temps de calcul
    temps_initial = clock();
    int t = reorganiseReseau(reseau);
    temps_final = clock();

    temps = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;

    if (t) printf("Nombre de chaines: %d \ngamma : %d\ntemps: %lf \nReconstitution reussie\n", chaines->nbChaines, chaines->gamma, temps);
    else printf("Nombre de chaines: %d \ngamma : %d\ntemps: %lf\nReconstitution echouee\n", chaines->nbChaines, chaines->gamma, temps);
    
    fprintf(destination, "%s %d %d %lf %d\n",argv[1], chaines->nbChaines, chaines->gamma, temps, t);

    liberer_chaine(chaines);
    liberer_reseau(reseau);
    fclose(inst);
    fclose(destination);

    return 0;
}
