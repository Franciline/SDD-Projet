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
        if (numero_methode == 1) {
            printf("Vous ouvrez le fichier %s avec la méthode Liste\n", argv[1]);
            FILE * fichier = fopen(argv[1], "r");
            Chaines* test = lectureChaines(fichier);
            printf("nb chaines %d\n", test->nbChaines);
            /*
            int ttmp = 0;
            CellChaine* cptc = test->chaines;
            while (cptc){
                CellPoint* cptp = cptc->points;
                while(cptp){
                    ttmp ++;
                    printf("point %lf %lf\n ", cptp->x, cptp->y);
                    cptp = cptp->suiv;
                }
                cptc = cptc->suiv;
            }
            printf("fini tot de %d \n", ttmp);
            */
            Reseau* test_reseau = reconstitueReseauListe(test);
            int nb_cell_noeud = 0;
            CellNoeud* tmp = test_reseau-> noeuds;
            while(tmp){
                nb_cell_noeud ++;
                tmp = tmp->suiv;
            }
            printf("nb de noeud %d et vrai %d", test_reseau->nbNoeuds, nb_cell_noeud);
            printf("nombre liaisons et comodites %d %d \n", nbLiaisons(test_reseau), nbCommodites(test_reseau));
            afficheReseauSVG(test_reseau, "affichage_depuis_reseau");
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
