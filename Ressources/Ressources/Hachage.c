#include "Hachage.h"
#include <math.h>
#include <stdlib.h>
#include "Reseau.h"
#define TAILLE 20


//fonction de bases
/*clé de hachage*/
int f(int x, int y){
    return y + (x + y)*(x + y + 1)/2;
} 

/*fonction de hachage*/
int h(TableHachage* t, int k) {
    int M = t->tailleMax;
    double A = (sqrt(5) - 1) / 2;
    return floor(M*(k*A - floor(k*A)));
}

/*Alloue et initialise une table de hachage vide*/
TableHachage* initTableHachage(int taille){
    //Création et init de la table de hachage pour le réseau
    TableHachage * tableH = (TableHachage*)malloc(sizeof(TableHachage));
    tableH -> nbElement = 0;
    tableH -> tailleMax = taille;
    tableH -> T=(CellNoeud**)malloc(sizeof(CellNoeud*)*taille);
    for (int i = 0; i < taille; i++){
        tableH->T[i] = NULL;
    }
    return tableH;
}

//EXO 4

//Question 3
/*Retourne le noeud de R correspondant, sinon crée le noeud et l'ajoute dans R*/
Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y) {
    //On recupere l'indice grace a la fonction de hachage
    int i = h(H, f(x, y));

    //Liste de noeuds située a la position i
    CellNoeud* liste = H->T[i];

    //On cherche si le noeud existe deja ou pas
    while (liste){
        //égalité des doubles 
        if ((liste->nd->x == x) && (liste->nd->y == y)){
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

//Question 4
/*Reconstitue le réseau à partir de la liste chaine et en utilisant le tableau de hachage*/
Reseau* reconstitueReseauHachage(Chaines *C, int M){

    //Création du réseau
    Reseau* reseau = creer_reseau();
    reseau->gamma=C->gamma;
    CellChaine* liste = C->chaines;
    TableHachage * tableH = initTableHachage(TAILLE);

    //on parcourt toutes les CellChaines
    while(liste){
        //une chaine possède une commodité et une liste de CellNoeud avec des Noeuds
        CellCommodite* commodite = creer_cellcommodite();   //on crée la commodité
        CellPoint * liste_points = liste->points;           //liste des points dans la chaine 
        CellPoint* prec = liste_points, *suiv = NULL;       //On garde le précédent et le suivant pour ajouter dans les voisins        
        //premier point: on rechercher et l'ajoute si n'existe pas dans Reseau
        Noeud* n = rechercheCreeNoeudHachage(reseau, tableH, liste_points->x, liste_points->y);
        commodite->extrA = n;

        //On parcourt tous les CellPoints
        while(liste_points->suiv != NULL){
            suiv = liste_points->suiv;
            Noeud * n = rechercheCreeNoeudHachage(reseau, tableH, liste_points->x, liste_points->y);
            
            //ajout des voisins 
            
            ajouter_voisin(n, rechercheCreeNoeudHachage(reseau, tableH, prec->x, prec->y));
            ajouter_voisin(n, rechercheCreeNoeudHachage(reseau, tableH, suiv->x, suiv->y));

            prec = liste_points;
            liste_points = liste_points->suiv;
        }

        commodite->extrB = rechercheCreeNoeudHachage(reseau, tableH, liste_points->x, liste_points->y);
        //le suivant est NULL, on ajoute le précédent
        ajouter_voisin(commodite->extrB, rechercheCreeNoeudHachage(reseau, tableH, prec->x, prec->y)); 
        
        //on insere la commodité
        commodite->suiv = reseau->commodites;
        reseau->commodites = commodite;
        //On a ajouté commodité et noeud de la chaine à réseau, on passe à la liste suivante
        liste = liste->suiv;
    }
    
    //liberer_tablehachage(tableH);
    return reseau;
}

/*Libere le tableau de hachage*/
void liberer_tablehachage(TableHachage* t){
    //on lberer juste la table et les cellNoeuds
    for (int i = 0; i < t->tailleMax;i ++){
        CellNoeud * c = t->T[i];
        while(c){
            CellNoeud* next = c->suiv;
            free(c);
            c = next;
        }
    }
    free(t->T);
    free(t);
}
