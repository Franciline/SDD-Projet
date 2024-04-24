#include <stdio.h>
#include <stdlib.h>

#include "Chaine.h"
#include "Reseau.h"
#include "Hachage.h"
#include "ArbreQuat.h"

#include <time.h>
clock_t temps_initial;
clock_t temps_final;
double temps_cpu_liste, temps_cpu_hachage, temps_cpu_arbre;


/*Exécute les 3 fonctions de reconstructions*/
int main(int argc, char** argv){

    //ouverture du fichier de chaines
    FILE * fichier1 = fopen("00014_burma.cha", "r");
    FILE * fichier2 = fopen("comparaison.txt", "w");
    Chaines* test = lectureChaines(fichier1);
    int taille_tab = 20;
    Reseau* test_reseau = NULL;

    fprintf(fichier2, "Temps de calcul pour\n\n");

    //Arbre quaternaire
    temps_initial = clock();
    test_reseau = reconstitueReseauArbre(test);
    temps_final = clock();
    temps_cpu_arbre = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
    fprintf(fichier2, "Arbre Quaternaire \n%lf\n",temps_cpu_arbre);
    liberer_reseau(test_reseau);

    //Liste chainée
    temps_initial = clock();
    test_reseau = reconstitueReseauListe(test);
    temps_final = clock();
    temps_cpu_liste = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
    fprintf(fichier2, "Liste chainee\n%lf\n",temps_cpu_liste);
    liberer_reseau(test_reseau);

    //Table de hachage
    for (taille_tab = 10; taille_tab <= 500; taille_tab+=50){
        temps_initial = clock();
        test_reseau = reconstitueReseauHachage(test, taille_tab);
        temps_final = clock();
        temps_cpu_hachage = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
        fprintf(fichier2, "Table de hachage taille = %d\n%lf\n",taille_tab, temps_cpu_hachage);
        liberer_reseau(test_reseau);
    }

    liberer_chaine(test);
    fclose(fichier1);
    fclose(fichier2);

}