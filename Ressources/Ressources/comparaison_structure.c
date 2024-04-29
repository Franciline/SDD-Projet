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
    FILE * source = fopen("10000_USA-road-d-NY.cha", "r");
    FILE * destination = fopen("instance_comparaison.txt", "a");
    Chaines* chaines = lectureChaines(source);
    int taille_tab = 20;
    Reseau* test_reseau;

    //fprintf(destination, "nbChaine ABQ LC H50 H100 H150 H200 H250 H300 H350 H400 H450 H500 \n\n");
    fprintf(destination, "%d ",chaines->nbChaines);

    //Arbre quaternaire
    temps_initial = clock();
    test_reseau = reconstitueReseauArbre(chaines);
    temps_final = clock();
    temps_cpu_arbre = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
    fprintf(destination, "%lf ",temps_cpu_arbre);
    //liberer_reseau(test_reseau);
    printf("arbre fait\n");
    //Liste chainée
    temps_initial = clock();
    test_reseau = reconstitueReseauListe(chaines);
    temps_final = clock();
    temps_cpu_liste = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
    fprintf(destination, "%lf ",temps_cpu_liste);
    //liberer_reseau(test_reseau);
    printf("LC fait\n");
    //Table de hachage
    for (taille_tab = 50; taille_tab <= 501; taille_tab+=50){
        temps_initial = clock();
        test_reseau = reconstitueReseauHachage(chaines, taille_tab);
        temps_final = clock();
        temps_cpu_hachage = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
        fprintf(destination, "%lf ", temps_cpu_hachage);
        //liberer_reseau(test_reseau);
        printf("table %d fait\n", taille_tab);
    }
    fprintf(destination,"\n");
    //liberer_chaine(chaines);
    fclose(source);
    fclose(destination);

}