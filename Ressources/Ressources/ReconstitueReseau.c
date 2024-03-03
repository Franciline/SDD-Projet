#include "Chaine.h"
#include "Reseau.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    if (argc < 2){
        printf("Il faut 1 arguments!: %s  <nom_du_fichier.cha>\n", argv[0]);
        return -1;
    } 
    //récupération de la méthode à utiliser
    int choix;
    char reponse[512];

    printf("Quelles méthode souhaitez vous utiliser? \n");
    printf("0-liste\n1-table de hachage\n2-arbre\n");

    fgets(reponse, 512, stdin);
    sscanf(reponse, "%d", &choix);
        
    return 0;
}