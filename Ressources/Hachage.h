#ifndef HACHAGE_H
#define HACHAGE_H

#include "Reseau.h"


typedef struct{
  int nbElement; //pas necessaire ici
  int tailleMax;
  CellNoeud** T;
} TableHachage ;


int f(int x, int y);                                                                // Exercice 4 Question 2
int h(TableHachage* t, int k);                                                      // Exercice 4 Question 3
Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y);   // Exercice 4 Question 4
Reseau* reconstitueReseauHachage(Chaines* C, int M);                                // Exercice 4 Question 5

//Fonctions de base

TableHachage* initTableHachage(int taille);         // Initialise et renvoie une table de hachage 
void ajoutNoeudHachage(TableHachage* H, Noeud* noeud, int position);

//Fonction de desallocation

void liberer_tablehachage(TableHachage* t);         // Libere la table de hachage

#endif
