#include "Reseau.h"
#include "Chaine.h"
#include <stdio.h>
#include <stdlib.h>
#define EPSILON 0.000001

//EXERCICE 2

//fonctions de base
/*Créer un réseau vide*/
Reseau* creer_reseau(){
    Reseau* reseau = (Reseau*)(malloc(sizeof(Reseau)));
    reseau->nbNoeuds = 0;
    reseau->gamma = 0;
    reseau->noeuds = NULL;
    reseau->commodites = NULL;

    return reseau;
}

CellCommodite* creer_cellcommodite(){
    CellCommodite* cellc = (CellCommodite*)(malloc(sizeof(CellCommodite)));
    cellc->extrA = NULL; 
    cellc->extrB = NULL;
    cellc->suiv = NULL;
    return cellc;

}

CellNoeud* creer_cellnoeud(){
    CellNoeud* celln = (CellNoeud*)(malloc(sizeof(CellNoeud)));
    celln -> nd = NULL;
    celln->suiv=NULL;
    return celln;
}

Noeud* creer_noeud(){
    Noeud* n = (Noeud*)(malloc(sizeof(Noeud)));
    n->num = 0;
    n->x = 0;
    n->y = 0;
    n->voisins = NULL;
    return n;
}


//Question 1
/*Retourne le noeud de R correspondant, sinon créer le noeud et l'ajoute dans R*/
Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y){

    CellNoeud * liste = R->noeuds;

    while (liste){
        if ((liste->nd->x - x < EPSILON) && (liste->nd->y - y < EPSILON)) return liste;
        liste = liste->suiv;
    }

    //création du noeud
    Noeud * new_noeud = creer_noeud();
    new_noeud->x = x;
    new_noeud->y = y;
    new_noeud->num = R->nbNoeuds + 1;
    new_noeud->voisins = NULL;

    //creation de la cellule
    CellNoeud * new_celln = (CellNoeud*)(malloc(sizeof(CellNoeud)));
    new_celln -> nd = new_noeud;
    new_celln -> suiv = R->noeuds;
    
    //ajout dans R
    R->noeuds = new_celln;
    R->nbNoeuds = R->nbNoeuds + 1;

    return new_noeud;
}

//Question 2
/*Reconstiture le réseau à partir de la liste chainée*/
Reseau* reconstitueReseauListe(Chaines *C){

    //Création du réseau
    Reseau* reseau = creer_reseau();
    reseau->gamma=C->gamma;

    CellChaine* liste = C->chaines;

    //on parcourt toutes les chaines
    while(liste){
        CellCommodite* commodite = creer_cellcommodite();
        CellPoint * liste_points = liste->points;

        //on ajoute les points au réseau

        //pour chaque point il faut avjouter voisin (?) prec suiv dans liste?
        //fonction prec creer cellnoeud pour chaque noeud, et augmente nb points
        
        //premier point
        Noeud* n = rechercheCreeNoeudListe(reseau, liste_points->x, liste_points->y);

        //on sauvegarde la commodité
        commodite->extrA = n;
        //parcours les autres points
        while(liste_points->suiv != NULL){
            liste_points=liste_points->suiv;
            Noeud * n = rechercheCreeNoeudListe(reseau, liste_points->x, liste_points->y);
        }

        //on arrive au dernier point
        commodite->extrB = n;
        commodite->suiv = reseau->commodites;
        reseau->commodites = commodite;

        //ici on a ajouté commodité et noeud de la chaine à réseau
        //on passe à la liste suivante

        liste = liste->suiv;

    }

    return reseau;
}
