#include "ArbreQuat.h"
#include "Reseau.h"

//EXO 5 
//Question 1
/*Fonction qui détermine les coordonnées min et max de la chaine*/
void chaineCoordMinMax(Chaines* C, double* xmin, double* ymin, double* xmax, double* ymax){
    if ((C == NULL) || (C->chaines == NULL)) return; 
    CellChaine * cellchaine = C->chaines;

    //On assigne les premieres valeurs
    double xmi = cellchaine->points->x, ymi = cellchaine->points->y, xma = cellchaine->points->x, yma = cellchaine->points->y;
    cellchaine = cellchaine->suiv;

    //on parcours les cellules chaines de la chaine
    while (cellchaine){
        CellPoint * points = cellchaine->points;
        //on parcours les points de la chaine
        while(points){
            if (points->x < xmi){
                xmi = points->x;
            }
            if (points->x > xma){
                xma = points->x;
            }
            if (points->y < ymi){
                ymi = points->y;
            }
            if (points->y > yma){
                yma = points->y;
            }

            points = points->suiv;
        }
        cellchaine = cellchaine->suiv;
    }

    //on enregistre ces valeurs
    *xmin = xmi; *ymin = ymi; *xmax = xma; *ymax = yma;
}

//Question 3
/*INsere un NOeud du réseau dans un arbre*/
void insererNoeudArbre(Noeud* n, ArbreQuat** a, ArbreQuat* parent){
    //
}