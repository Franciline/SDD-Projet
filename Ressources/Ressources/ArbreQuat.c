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

//Question 2
/*Fonction qui creer une cellule de l'arbre quaternaire*/
ArbreQuat* creerArbreQuat(double xc, double yc, double coteX, double coteY) {
    ArbreQuat* new_aq = (ArbreQuat*) malloc(sizeof(ArbreQuat));

    new_aq->xc = xc;
    new_aq->yc = yc;
    new_aq->coteX = coteX;
    new_aq->coteY = coteY;
    new_aq->noeud = creer_noeud();
    new_aq->so = NULL;
    new_aq->se = NULL;
    new_aq->no = NULL;
    new_aq->ne = NULL;

    return new_aq;
}


//Question 3
/*Insere un Noeud du reseau dans un arbre*/
void insererNoeudArbre(Noeud* n, ArbreQuat** a, ArbreQuat* parent){
    //
}

//Question 4
/*Retourne le noeud de R correspondant, sinon cree le noeud et l'ajoute dans R*/
Noeud* rechercheCreeNoeudArbre(Reseau* R, ArbreQuat** a, ArbreQuat* parent, double x, double y) {
    ArbreQuat* arbre = *a;

    //Cas arbre vide
    if (arbre == NULL) {
        //on cree un nouveau noeud
        Noeud* new_noeud = creer_noeud();
        new_noeud->x = x;
        new_noeud->y = y;
        new_noeud->num = R->nbNoeuds + 1;

        //creation de la cellule pour R
        CellNoeud* new_cellnR = (CellNoeud*)(malloc(sizeof(CellNoeud)));
        new_cellnR->nd = new_noeud; //on affecte le noeud dans la cellule
        new_cellnR->suiv = R->noeuds; //on ajoute à la suite de la liste de CellNoeud dans Reseau
        
        //ajout dans R
        R->noeuds = new_cellnR;
        R->nbNoeuds = R->nbNoeuds + 1; //on incrémente le nombre de noeuds

        //ajout dans a
        insererNoeudArbre(new_noeud, a, parent);

        return new_noeud;
    }

    //Cas feuille
    if (arbre->noeud != NULL) {
        if ((x == arbre->noeud->x) && (y == arbre->noeud->y)) {
            return arbre->noeud;
        }
        else {
            //on cree un nouveau noeud
            Noeud* new_noeud = creer_noeud();
            new_noeud->x = x;
            new_noeud->y = y;
            new_noeud->num = R->nbNoeuds + 1;

            //creation de la cellule pour R
            CellNoeud* new_cellnR = (CellNoeud*)(malloc(sizeof(CellNoeud)));
            new_cellnR->nd = new_noeud; //on affecte le noeud dans la cellule
            new_cellnR->suiv = R->noeuds; //on ajoute à la suite de la liste de CellNoeud dans Reseau
            
            //ajout dans R
            R->noeuds = new_cellnR;
            R->nbNoeuds = R->nbNoeuds + 1; //on incrémente le nombre de noeuds

            //ajout dans a
            insererNoeudArbre(new_noeud, a, parent);

            return new_noeud;
        }
    }

    //Cas cellule interne
    if ((arbre != NULL) && (arbre->noeud == NULL)) {
        if (x < parent->xc) && (y < parent->yc) {
            rechercheCreeNoeudArbre(R, arbre, parent->so, x, y);
        }
        if (x > parent->xc) && (y > parent->yc) {
            rechercheCreeNoeudArbre(R, arbre, parent->ne, x, y);
        }
        if (x < parent->xc) && (y > parent->yc) {
            rechercheCreeNoeudArbre(R, arbre, parent->no, x, y);
        }
        if (x > parent->xc) && (y < parent->yc) {
            rechercheCreeNoeudArbre(R, arbre, parent->se, x, y);
        }
    }

    return new_noeud;
}
