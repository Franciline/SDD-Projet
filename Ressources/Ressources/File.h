#ifndef FILE_H
#define FILE_H

#include "graphe.h"


typedef struct element {
    Sommet* s;
    struct file* prec;
    struct file* suiv;
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
