#include <stdio.h>
#include <stdlib.h>

#include "Chaine.h"
#include "Reseau.h"
#include "Hachage.h"
#include "ArbreQuat.h"
#define TAILLE 20

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
        if (numero_methode == 1) {
            printf("Vous ouvrez le fichier %s avec la méthode Liste\n", argv[1]);
            FILE * fichier = fopen(argv[1], "r");
            FILE * fichier2 = fopen("test_ecriture_reseau.txt", "w");
            Chaines* test = lectureChaines(fichier);

            //on reconstitue le réseau depuis la chaine
            Reseau* test_reseau = reconstitueReseauListe(test);
            afficheReseauSVG(test_reseau, "affichage_depuis_reseau");
            ecrireReseau(test_reseau, fichier2);

        }
        else if (numero_methode == 2) {
            printf("Vous ouvrez le fichier %s avec la méthode Table de hachage\n", argv[1]);
            FILE * fichier = fopen(argv[1], "r");
            FILE * fichier2 = fopen("test_ecriture_reseau_Hachage.txt", "w");
            Chaines* test = lectureChaines(fichier);

            //on reconstitue le réseau depuis la chaine avec la table de hachage
            Reseau* test_reseau = reconstitueReseauHachage(test, TAILLE);
            afficheReseauSVG(test_reseau, "affichage_depuis_reseau");
            ecrireReseau(test_reseau, fichier2);
        }
        else if (numero_methode == 3) {
            printf("Vous ouvrez le fichier %s avec la méthode Arbre\n", argv[1]);
            FILE * fichier = fopen(argv[1], "r");
            FILE * fichier2 = fopen("test_ecriture_reseau_Arbre.txt", "w");
            Chaines* test = lectureChaines(fichier);

            //on reconstitue le réseau depuis la chaine avec la table de hachage
            Reseau* test_reseau = reconstitueReseauArbre(test);
            afficheReseauSVG(test_reseau, "affichage_depuis_reseau");
            ecrireReseau(test_reseau, fichier2);
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
