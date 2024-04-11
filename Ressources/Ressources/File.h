#ifndef FILE_H
#define FILE_H

#include "graphe.h"
#include "Reseau.h"


typedef struct element {
    Sommet* s;
    struct element* prec;
    struct element* suiv;
} Element;

typedef struct file {
    Element* premier;
    Element* dernier;
} File;


File* creer_file();
int est_vide(File* f);
void enfiler(File* f, Sommet* s);
Sommet* defiler(File* f);
//void afficher_file(File* f);

#endif
