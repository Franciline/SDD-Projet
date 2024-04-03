#ifndef FILE_H
#define FILE_H

#include "graphe.h"


typedef struct file {
    Sommet* elem;
    struct file* prec;
    struct file* suiv;
} File;


File* creer_file();
int est_vide(File* f);
void enfiler(File* f, Sommet* s);
Sommet* defiler(File* f);
void afficher_file(File* f);

#endif