#ifndef HACHAGE_H
#define HACHAGE_H

#include "Reseau.h"

typedef struct{
  int nbElement; //pas necessaire ici
  int tailleMax;
  CellNoeud** T;
} TableHachage ;

#endif