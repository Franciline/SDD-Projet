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

/*Main pour tester reorganiseReseau sur plusieurs instances*/
int main(){
    //Chaines* test = generationAleatoire(5, 100, 5000, 5000);
    //chaines->gamma = 3;

    FILE* inst = fopen("07397_pla.cha", "r");
    FILE* destination = fopen("instance_liste.txt", "a");
    Chaines* chaines = lectureChaines(inst);
    //chaines->gamma = 10;

    Reseau* reseau = reconstitueReseauArbre(chaines);

    temps_initial = clock();
    int t = reorganiseReseau(reseau);
    temps_final = clock();

    temps = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
    if (t) printf("Nombre de chaines: %d \ngamma : %d\ntemps: %lf \nReconstitution reussie\n", chaines->nbChaines, chaines->gamma, temps);
    else printf("Nombre de chaines: %d \ngamma : %d\ntemps: %lf\nReconstitution echouee\n", chaines->nbChaines, chaines->gamma, temps);
    
    fprintf(destination, "07397_pla.cha %d %d %lf %d\n",chaines->nbChaines, chaines->gamma, temps, t);

    //liberer_chaine(chaines);
    //liberer_reseau(reseau);
    fclose(inst);
    fclose(destination);

    return 0;
}