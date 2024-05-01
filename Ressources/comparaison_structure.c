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


//Exercice 6

//Question 1

int main(int argc, char** argv) {

    if (argc < 2) {
        printf("Il faut des arguments ! : ./%s <nom_instance> \n", argv[0]);        
        return 1;
    }

    //Ouverture du fichier de chaines
    FILE* source = fopen(argv[1], "r");
    FILE* destination = fopen("EXO6_Q1.txt", "a");
    
    Chaines* chaines = lectureChaines(source);
    Reseau* test_reseau;
    int taille_tab;

    fprintf(destination, "nom nbChaines ABQ LC H100 H200 H300 H400 H500\n");
    fprintf(destination, "%s %d ", argv[1], chaines->nbChaines);

    //Arbre quaternaire
    temps_initial = clock();
    test_reseau = reconstitueReseauArbre(chaines);
    temps_final = clock();

    temps_cpu_arbre = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;

    fprintf(destination, "%lf ", temps_cpu_arbre);
    liberer_reseau(test_reseau);
    
    //Liste chainee
    temps_initial = clock();
    test_reseau = reconstitueReseauListe(chaines);
    temps_final = clock();

    temps_cpu_liste = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;

    fprintf(destination, "%lf ", temps_cpu_liste);
    liberer_reseau(test_reseau);
    
    //Table de hachage
    for (taille_tab=100; taille_tab<=500; taille_tab+=100) {
        temps_initial = clock();
        test_reseau = reconstitueReseauHachage(chaines, taille_tab);
        temps_final = clock();

        temps_cpu_hachage = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
        fprintf(destination, "%lf ", temps_cpu_hachage);
        liberer_reseau(test_reseau);
    }
    
    fprintf(destination, "\n");

    liberer_chaine(chaines);
    fclose(source);
    fclose(destination);

    return 0;
}
