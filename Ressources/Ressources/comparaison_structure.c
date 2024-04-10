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
    //Chaines* test = generationAleatoire(100, 100, 500, 500);
    int taille_tab = 20;
    Reseau* test_reseau = NULL;

    //Arbre quaternaire
    temps_initial = clock();
    test_reseau = reconstitueReseauArbre(test);
    temps_final = clock();
    //printf("%ld %ld \n", temps_final, temps_initial);
    temps_cpu_arbre = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
    fprintf(fichier2, "Temps de calcul pour arbre\n%lf\n",temps_cpu_arbre);

    //Liste chainée
    temps_initial = clock();
    test_reseau = reconstitueReseauListe(test);
    temps_final = clock();
    //printf("%ld %ld \n", temps_final, temps_initial);
    temps_cpu_liste = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
    fprintf(fichier2, "Temps de calcul pour liste chainee\n%lf\n",temps_cpu_liste);

    //Table de hachage
    for (taille_tab = 10; taille_tab <= 500; taille_tab+=50){
        temps_initial = clock();
        test_reseau = reconstitueReseauHachage(test, taille_tab);
        temps_final = clock();
        //printf("%ld %ld \n", temps_final, temps_initial);
        temps_cpu_hachage = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
        fprintf(fichier2, "Temps de calcul pour table de hachage de taille %d\n%lf\n",taille_tab, temps_cpu_hachage);
    }

    //printf("liste : %lf hachage : %lf arbre : %lf \n", temps_cpu_liste, temps_cpu_hachage, temps_cpu_arbre);

    liberer_chaine(test);
    liberer_reseau(test_reseau);

}