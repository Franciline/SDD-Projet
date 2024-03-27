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
    new_aq->noeud = NULL;
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
        //on insère par rapport au parent en fonction de sa position
        //Les cotés correspondent à ceux du parent/2
        ArbreQuat* new = creerArbreQuat(parent->coteX/4, parent->coteY/4, parent->coteX/2, parent->coteY/2);
        new->noeud = n; 
        *a = new;
        
        if ((n->x <= parent->xc) && (n->y >= parent->yc))
        //cas no
            parent->no = *a;        
        if ((n->x >= parent->xc) && (n->y >= parent->yc))
        //cas ne
            parent->ne = *a;  
        if ((n->x <= parent->xc) && (n->y <= parent->yc))
        //cas so
            parent->so = *a;  
        if ((n->x >= parent->xc) && (n->y <= parent->yc))
        //cas se
            parent->se = *a;  
        return;
    }

    //Cas 2 feuille de l'arbre
    if ((*a)->noeud != NULL){
        //on transforme la feuille en Noeud interne
        //et on reinsere dans l'arbre les deux noeuds
        Noeud* tmp_a = (*a)->noeud;
        (*a)->noeud = NULL;
        //on créer un nouveau noeud où on va insérer les deux noeuds
        insererNoeudArbre(tmp_a, NULL, *a);
        insererNoeudArbre(n, NULL, *a);
        return;
    }

    //Cas 3 noeud interne
    if ((n->x <= parent->xc) && (n->y >= parent->yc))
    //cas no
        insererNoeudArbre(n, &((*a)->no), *a);
    //cas ne
    if ((n->x >= parent->xc) && (n->y >= parent->yc))
        insererNoeudArbre(n, &((*a)->ne), *a);
    //cas so
    if ((n->x <= parent->xc) && (n->y <= parent->yc))
        insererNoeudArbre(n, &((*a)->so), *a);
    //cas se
    if ((n->x >= parent->xc) && (n->y <= parent->yc))
        insererNoeudArbre(n, &((*a)->se), *a);

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
        if ((x < arbre->xc) && (y < arbre->yc)) {
            return rechercheCreeNoeudArbre(R, &(arbre->so), arbre, x, y);
        }
        if ((x > arbre->xc) && (y > arbre->yc)) {
            return rechercheCreeNoeudArbre(R, &(arbre->ne), arbre, x, y);
        }
        if ((x < arbre->xc) && (y > arbre->yc)) {
            return rechercheCreeNoeudArbre(R, &(arbre->no), arbre, x, y);
        }
        if ((x > arbre->xc) && (y < arbre->yc)) {
            return rechercheCreeNoeudArbre(R, &(arbre->se), arbre, x, y);
        }
    }
    
    return NULL;
}

//Question 4
/*Retourne le noeud de R correspondant, sinon cree le noeud et l'ajoute dans R*/
Reseau* reconstitueReseauArbre(Chaines* C) {
    //Creation du réseau
    Reseau* reseau = creer_reseau();
    reseau->gamma=C->gamma;
    CellChaine* liste = C->chaines;
    
    //Creation de l'arbre
    double xmin, ymin, xmax, ymax;
    chaineCoordMinMax(C, &xmin, &ymin, &xmax, &ymax);
    ArbreQuat* a = creerArbreQuat(xmax/2, ymax/2, xmax, ymax);
    ArbreQuat* parent = NULL;


    //on parcourt toutes les CellChaines
    while(liste){
        //une chaine possede une commodite et une liste de CellNoeud avec des Noeuds
        CellCommodite* commodite = creer_cellcommodite();   //on cree la commodité
        CellPoint * liste_points = liste->points;           //liste des points dans la chaine 
        CellPoint* prec = liste_points, *suiv = NULL;       //On garde le précedent et le suivant pour ajouter dans les voisins        
        //premier point: on rechercher et l'ajoute si n'existe pas dans Reseau
        Noeud* n = rechercheCreeNoeudArbre(reseau, &a, parent, liste_points->x, liste_points->y);
        commodite->extrA = n;

        //On parcourt tous les CellPoints
        while(liste_points->suiv != NULL){
            suiv = liste_points->suiv;
            Noeud * n = rechercheCreeNoeudArbre(reseau, &a, parent, liste_points->x, liste_points->y);
            //ajout des voisins 
            
            ajouter_voisin(n, rechercheCreeNoeudArbre(reseau, &a, parent, prec->x, prec->y));
            ajouter_voisin(n, rechercheCreeNoeudArbre(reseau, &a, parent, suiv->x, suiv->y));

            prec = liste_points;
            liste_points = liste_points->suiv;
        }

        commodite->extrB = rechercheCreeNoeudArbre(reseau, &a, parent, liste_points->x, liste_points->y);
        //le suivant est NULL, on ajoute le précédent
        ajouter_voisin(commodite->extrB, rechercheCreeNoeudArbre(reseau, &a, parent, prec->x, prec->y));
        
        //on insere la commodité
        commodite->suiv = reseau->commodites;
        reseau->commodites = commodite;
        //On a ajouté commodité et noeud de la chaine à réseau, on passe à la liste suivante
        liste = liste->suiv;
    }

    return reseau;
}
