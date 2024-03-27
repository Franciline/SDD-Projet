#include <stdlib.h>

#include "ArbreQuat.h"
#include "Reseau.h"

//EXO 5 
//Question 1
/*Fonction qui determine les coordonnees min et max de la chaine*/
void chaineCoordMinMax(Chaines* C, double* xmin, double* ymin, double* xmax, double* ymax){
    if ((C == NULL) || (C->chaines == NULL)) return; 
    CellChaine * cellchaine = C->chaines;

    //On assigne les premieres valeurs
    double xmi = cellchaine->points->x, ymi = cellchaine->points->y, xma = cellchaine->points->x, yma = cellchaine->points->y;
    cellchaine = cellchaine->suiv;

    //on parcourt les cellules chaines de la chaine
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
    //cas 1 arbre vide
    if (a == NULL){

        //on insere par rapport au parent en fonction de sa position
        //Les cotes correspondent a ceux du parent/2
        ArbreQuat* new = creerArbreQuat(parent->coteX/4, parent->coteY/4, parent->coteX/2, parent->coteY/2);
        new->noeud = n; 
        *a = new;
        
        if ((n->x <= parent->xc) && (n->y <= parent->yc))
        //cas no
            parent->no = *a;        
        if ((n->x >= parent->xc) && (n->y <= parent->yc))
        //cas ne
            parent->ne = *a;  
        if ((n->x <= parent->xc) && (n->y >= parent->yc))
        //cas so
            parent->so = *a;  
        if ((n->x >= parent->xc) && (n->y >= parent->yc))
        //cas se
            parent->se = *a;  
        return;
    }

    //Cas 2 feuille de l'arbre
    if ((*a)->noeud != NULL){
        //on cree un nouveau noeud ou on va insérer les deux noeuds
        ArbreQuat* new = creerArbreQuat(parent->coteX/4, parent->coteY/4, parent->coteX/2, parent->coteY/2);
        new->noeud = NULL;
        new->no = NULL;
        new->ne = NULL;
        new->so = NULL;
        new->se = NULL; 

        insererNoeudArbre((*a)->noeud, NULL, new);
        insererNoeudArbre(n, NULL, new);
        return;
    }

    //Cas 3 noeud interne
    if ((n->x <= parent->xc) && (n->y <= parent->yc))
    //cas no
        insererNoeudArbre(n, &((*a)->no), parent);
    //cas ne
    if ((n->x >= parent->xc) && (n->y <= parent->yc))
        insererNoeudArbre(n, &((*a)->ne), parent);
    //cas so
    if ((n->x <= parent->xc) && (n->y >= parent->yc))
        insererNoeudArbre(n, &((*a)->so), parent);
    //cas se
    if ((n->x >= parent->xc) && (n->y >= parent->yc))
        insererNoeudArbre(n, &((*a)->se), parent);

    return;

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
        if ((x < parent->xc) && (y < parent->yc)) {
            return rechercheCreeNoeudArbre(R, arbre, parent->so, x, y);
        }
        if ((x > parent->xc) && (y > parent->yc)) {
            return rechercheCreeNoeudArbre(R, arbre, parent->ne, x, y);
        }
        if ((x < parent->xc) && (y > parent->yc)) {
            return rechercheCreeNoeudArbre(R, arbre, parent->no, x, y);
        }
        if ((x > parent->xc) && (y < parent->yc)) {
            return rechercheCreeNoeudArbre(R, arbre, parent->se, x, y);
        }
    }
}
