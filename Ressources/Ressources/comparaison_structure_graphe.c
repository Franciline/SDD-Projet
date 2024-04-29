#include <stdio.h>
#include <stdlib.h>

#include "Chaine.h"
#include "Reseau.h"
#include "Hachage.h"
#include "ArbreQuat.h"

#include <time.h>
clock_t temps_initial;
clock_t temps_final;
double temps_cpu_liste, temps_cpu_hachage_50, temps_cpu_hachage_100, temps_cpu_hachage_500, temps_cpu_hachage_1000, temps_cpu_arbre;

#define XMAX 5000
#define YMAX 5000
#define NBPC 100

/*Exercice 6 question 3*/
int main(){

    FILE * res_liste = fopen("reconstitueR_lc.txt", "w");
    FILE * res_hash_abr = fopen("reconstitueR_hash_abr.txt", "w");
    Chaines* chaine;
    Reseau * reseau;

    fprintf(res_liste,"n tmp_lc\n");
    fprintf(res_hash_abr,"n h=50 h=100 h=500 h=1000 tmp_abr\n");

    for (int i = 500; i <= 5000; i+=500){
        chaine = generationAleatoire(i, NBPC, XMAX, YMAX);
        
        //liste chainee
        temps_initial = clock();
        reseau = reconstitueReseauListe(chaine);
        temps_final = clock();
        liberer_reseau(reseau);

        temps_cpu_liste = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
        fprintf(res_liste, "%d %lf\n", i, temps_cpu_liste);

        //table de hachage
        int tab_tailles[4] = {50, 100, 500, 1000};
        fprintf(res_hash_abr, "%d ", i);

        for (int j = 0; j < 4; j ++){
            temps_initial = clock();
            reseau = reconstitueReseauHachage(chaine, tab_tailles[j]);
            temps_final = clock();

            temps_cpu_hachage_50 = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
            liberer_reseau(reseau);

            fprintf(res_hash_abr, "%lf ", temps_cpu_hachage_50);
        }

        //arbre
        temps_initial = clock();
        reseau = reconstitueReseauArbre(chaine); 
        temps_final = clock();
        
        temps_cpu_arbre = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
        liberer_reseau(reseau);

        fprintf(res_hash_abr, "%lf\n", temps_cpu_arbre);
        liberer_chaine(chaine);  

    }

    fclose(res_hash_abr);
    fclose(res_liste);

    return 0;
}