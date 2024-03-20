#include "Hachage.h"
#include <math.h>

int h(TableHachage* t, int k) {
    int M = t->nbElement;
    double A = (sqrt(5) - 1) / 2;

    return floor(M*(k*A - floor(k*A)));
}

//Question 3
/*Retourne le noeud de R correspondant, sinon créer le noeud et l'ajoute dans R*/
Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y) {
    CellNoeud** t = H->T;
    CellNoeud* liste;

    //On recupere l'indice grace a la fonction de hachage
    int i = h(H, f(x, y));

    // Liste de noeuds située a la position i
    liste = t[i]->nd;

    //On cherche si le noeud existe deja ou pas
    while (liste){
        //égalité des doubles fait avec la différence
        if ((liste->nd->x == x) && (liste->nd->y == y)) {
            return liste->nd;
        }
        
        liste = liste->suiv;
    }

    //Cas ou le noeud n'existe pas

    //On cree un nouveau noeud
    Noeud* new_noeud = creer_noeud();
    new_noeud->x = x;
    new_noeud->y = y;
    new_noeud->num = R->nbNoeuds + 1;

    //creation de la cellule pour R
    CellNoeud * new_cellnR = (CellNoeud*)(malloc(sizeof(CellNoeud)));
    new_cellnR -> nd = new_noeud; //on affecte le noeud dans la cellule
    new_cellnR -> suiv = R->noeuds; //on ajoute à la suite de la liste de CellNoeud dans Reseau
    
    //ajout dans R
    R->noeuds = new_cellnR;
    R->nbNoeuds = R->nbNoeuds + 1; //on incrémente le nombre de noeuds

    //creation de la cellule pour H
    CellNoeud * new_cellnH = (CellNoeud*)(malloc(sizeof(CellNoeud)));
    new_cellnH -> nd = new_noeud; //on affecte le noeud dans la cellule
    new_cellnH -> suiv = H->T[i]; //on ajoute à la suite de la liste de CellNoeud dans TableHachage

    //ajout dans H
    H->T[i] = new_cellnH;
    H->nbElement++;

    return new_noeud;
}