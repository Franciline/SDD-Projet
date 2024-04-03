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
//Question 2

Chaines* generationAleatoire(int nbChaines, int nbPointsChaine, int xmax, int ymax) {
    Chaines* chaines = creer_chaine();
    CellChaine* suiv = chaines->chaines;

    for (int i = 0; i < nbChaines, i++) {
        CellChaine* cellC = (CellChaine*) malloc(sizeof(CellChaine));
        cellC->points = NULL;
        cellC->numero = i;

        for (int j = 0; j < nbPointsChaine; j++) {
            CellPoint* cellP = (CellPoint*) malloc(sizeof(CellPoint));
            cellP->x = rand() % xmax;
            cellP->y = rand() % ymax;
            cellP->suiv = cellC->points;
            cellC->points = cellP;
        }

        cellC->suiv = chaines->chaines;
        chaines->chaines = cellC;
        chaines->nbChaines++;
    }

    return chaines;
}