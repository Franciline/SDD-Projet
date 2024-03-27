#ifndef HACHAGE_H
#define HACHAGE_H
#include "Reseau.h"

typedef struct{
  int nbElement; //pas necessaire ici
  int tailleMax;
  CellNoeud ** T;
} TableHachage ;

int h(TableHachage* t, int k);
int f(int x, int y);

Reseau* reconstitueReseauHachage(Chaines *C, int M);
Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y);
TableHachage* initTableHachage(int taille);

//Desallocation
void liberer_tablehachage(TableHachage* t);

#endif