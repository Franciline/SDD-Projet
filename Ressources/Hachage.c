#include <math.h>
#include <stdlib.h>

#include "Hachage.h"
#include "Reseau.h"


//Exercice 4

//Question 3

/* Retourne le noeud du reseau R correspondant, sinon cree le noeud et l'ajoute dans le reseau R */
Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y) {
    //On recupere l'indice grace a la fonction de hachage
    int i = h(H, f(x, y));

    //Liste de noeuds situee a la position i
    CellNoeud* liste = H->T[i];

    //On cherche si le noeud existe deja
    while(liste){
        if ((liste->nd->x == x) && (liste->nd->y == y)){
            return liste->nd;
        }
        liste = liste->suiv;
    }

    //Cas ou le noeud n'existe pas on cree un nouveau noeud
    Noeud* new_noeud = creer_noeud(x, y, R->nbNoeuds + 1);

    //On ajoute le noeud dans le reseau
    ajoutNoeudReseau(R, new_noeud);

    //On ajoute le noeud dans la table de hachage
    ajoutNoeudHachage(H, new_noeud, i);

    return new_noeud;
}

//Question 4

/* Reconstitue le reseau a partir de la liste chainee et en utilisant le tableau de hachage */
Reseau* reconstitueReseauHachage(Chaines* C, int M){

    //Creation du reseau
    Reseau* reseau = creer_reseau(C->gamma);
    CellChaine* liste = C->chaines;
    TableHachage* tableH = initTableHachage(M);

    //On parcourt toutes les CellChaine
    while(liste){
        //Une chaine possede une commodite et une liste de CellNoeud avec des Noeud
        CellCommodite* commodite = creer_cellcommodite();   //On cree la commodite
        CellPoint* liste_points = liste->points;            //Liste des points dans la chaine
        CellPoint* prec = liste_points;                     //On garde le precedent pour ajouter dans les voisins
        CellPoint* suiv = NULL;                             //On garde le suivant pour ajouter dans les voisins

        //Premier point : on recherche et l'ajoute si il n'existe pas encore dans Reseau
        Noeud* n = rechercheCreeNoeudHachage(reseau, tableH, liste_points->x, liste_points->y);
        commodite->extrA = n;

        //On parcourt tous les CellPoint
        while(liste_points->suiv != NULL){
            suiv = liste_points->suiv;
            Noeud* n = rechercheCreeNoeudHachage(reseau, tableH, liste_points->x, liste_points->y);
            
            //Ajout des voisins 
            ajouter_voisin(n, rechercheCreeNoeudHachage(reseau, tableH, prec->x, prec->y));
            ajouter_voisin(n, rechercheCreeNoeudHachage(reseau, tableH, suiv->x, suiv->y));

            prec = liste_points;
            liste_points = liste_points->suiv;
        }

        commodite->extrB = rechercheCreeNoeudHachage(reseau, tableH, liste_points->x, liste_points->y);
        //Le suivant est NULL, on ajoute le precedent
        ajouter_voisin(commodite->extrB, rechercheCreeNoeudHachage(reseau, tableH, prec->x, prec->y)); 
        
        //On insere la commodite
        commodite->suiv = reseau->commodites;
        reseau->commodites = commodite;
        //On a ajoute commodite et noeud de la chaine a reseau, on passe a la liste suivante
        liste = liste->suiv;
    }
    
    liberer_tablehachage(tableH);

    return reseau;
}


//Fonctions de base

/* Cle de hachage */
int f(int x, int y){
    return y + (x + y)*(x + y + 1)/2;
} 

/* Fonction de hachage */
int h(TableHachage* t, int k) {
    int M = t->tailleMax;
    double A = (sqrt(5) - 1)/2;
    return floor(M*(k*A - floor(k*A)));
}

/* Alloue la memoire et initialise une table de hachage vide */
TableHachage* initTableHachage(int taille){
    TableHachage* tableH = (TableHachage *) malloc(sizeof(TableHachage));
    tableH->nbElement = 0;
    tableH->tailleMax = taille;
    tableH->T = (CellNoeud **) malloc(sizeof(CellNoeud *)*taille);
    for (int i=0; i<taille; i++){
        tableH->T[i] = NULL;
    }

    return tableH;
}

/*ajoute un noeud dans le reseau*/
void ajoutNoeudReseau(Reseau* reseau, Noeud* noeud){
    CellNoeud* celln = (CellNoeud *) malloc(sizeof(CellNoeud));

    //creation du noeud
    celln->nd = noeud;
    celln->suiv = reseau->noeuds;

    //ajout dans reseau
    reseau->noeuds = celln;
    reseau->nbNoeuds = reseau->nbNoeuds + 1;  //On incremente le nombre de noeuds
}


/*Ajoute un noeud dans la tbale de hachage a la position i*/
void ajoutNoeudHachage(TableHachage* H, Noeud* noeud, int position){
    //Creation de la cellule pour la table de hachage H
    CellNoeud* new_cellnH = creer_cellnoeud(noeud);         //On affecte le noeud dans la cellule
    new_cellnH->suiv = H->T[position];                      //On ajoute en tete de la liste de CellNoeud 

    //Ajout dans la table de hachage
    H->T[position] = new_cellnH;
    H->nbElement++;
}

/* Libere le tableau de hachage */
void liberer_tablehachage(TableHachage* t){
    //On libere la table et les cellNoeud
    for (int i=0; i<t->tailleMax; i++){
        CellNoeud* c = t->T[i];
        while(c){
            CellNoeud* next = c->suiv;
            free(c);
            c = next;
        }
    }
    free(t->T);
    free(t);

    return;
}

