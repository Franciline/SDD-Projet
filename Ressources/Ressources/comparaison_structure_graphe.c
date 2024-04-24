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

int main(){
    FILE * rec_liste = fopen("reconstitueR_lc2.txt", "w");
    FILE * rec_hash_abr = fopen("reconstitueR_hash_abr2.txt", "w");
    Chaines* chaine;
    Reseau * reseau;

    fprintf(rec_liste,"n tmp_lc\n");
    fprintf(rec_hash_abr,"n h=50 h=100 h=500 h=1000 tmp_abr\n");

    for (int i = 500; i <= 5000; i+=500){
        printf("boucle i = %d\n", i);
        chaine = generationAleatoire(i, NBPC, XMAX, YMAX);
        
        //liste chainee
        temps_initial = clock();
        reseau = reconstitueReseauListe(chaine);
        temps_final = clock();
        //liberer_reseau(reseau);

        temps_cpu_liste = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
        fprintf(rec_liste, "%d %lf\n", i, temps_cpu_liste);


        //table hachage taille 50 100 500 1000
        temps_initial = clock();
        reseau = reconstitueReseauHachage(chaine, 50);
        temps_final = clock();
        //liberer_reseau(reseau);

        temps_cpu_hachage_50 = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;

        temps_initial = clock();
        reseau = reconstitueReseauHachage(chaine, 100); 
        temps_final = clock();
        //liberer_reseau(reseau);
        
        temps_cpu_hachage_100 = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;

        temps_initial = clock();
        reseau = reconstitueReseauHachage(chaine, 500); 
        temps_final = clock();
        //liberer_reseau(reseau);

        temps_cpu_hachage_500 = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
        
        temps_initial = clock();
        reseau = reconstitueReseauHachage(chaine, 1000); 
        temps_final = clock();
        //liberer_reseau(reseau);
        
        temps_cpu_hachage_1000 = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
        
    
        //arbre
        temps_initial = clock();
        reseau = reconstitueReseauArbre(chaine); 
        temps_final = clock();
        //liberer_reseau(reseau);
        
        temps_cpu_arbre = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;

        fprintf(rec_hash_abr, "%d %lf %lf %lf %lf %lf\n", i, temps_cpu_hachage_50, temps_cpu_hachage_100, temps_cpu_hachage_500, temps_cpu_hachage_1000, temps_cpu_arbre);
        
        //liberer_chaine(chaine);   
    }

    fclose(rec_hash_abr);
    fclose(rec_liste);

    return 0;
}