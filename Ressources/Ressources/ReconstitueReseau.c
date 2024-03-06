#include "Reseau.h"
#include "Chaine.h"
#include <stdio.h>
#include <stdlib.h>

#include "Reseau.h"

// Exercice 2

// Question 3

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Il faut des arguments ! : ./%s <nom_fichier> <numero_methode>\n", argv[0]);
        printf("numero_methode :\n"
               "\t- 1 : Liste\n"
               "\t- 2 : Table de hachage\n"
               "\t- 3 : Arbre\n");
        
        return 1;
    }
    if (argc > 3) {
        printf("Trop d'arguments ! : ./%s <nom_fichier> <numero_methode>\n", argv[0]);
        printf("numero_methode :\n"
               "\t- 1 : Liste\n"
               "\t- 2 : Table de hachage\n"
               "\t- 3 : Arbre\n");
        
        return 1;
    }
    else {
       
        int numero_methode = atoi(argv[2]);
        printf("numero m %d\n", numero_methode);
        if (numero_methode == 1) {
            printf("Vous ouvrez le fichier %s avec la méthode Liste\n", argv[1]);
            FILE * fichier = fopen(argv[1], "r");
            Chaines* test = lectureChaines(fichier);
            Reseau* test_reseau = reconstitueReseauListe(test);
            afficheReseauSVG(test_reseau, "affichage_reseau_test");
        }
        else if (numero_methode == 2) {
            printf("Vous ouvrez le fichier %s avec la méthode Table de hachage\n", argv[1]);
        }
        else if (numero_methode == 3) {
            printf("Vous ouvrez le fichier %s avec la méthode Arbre\n", argv[1]);
        }
        else {
            printf("Numéro de méthode invalide !\n");
            printf("numero_methode :\n"
               "\t- 1 : Liste\n"
               "\t- 2 : Table de hachage\n"
               "\t- 3 : Arbre\n");
        }
        return 0;
    }
}
