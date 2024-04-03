#include "File.h"

#include <stdlib.h>
#include <stdio.h>


//Fonction qui cree une nouvelle file
File* creer_file() {
    File* f = (File*) malloc(sizeof(File));
    f->elem = NULL;
    f->prec = NULL;
    f->suiv = NULL;
}

//Fonction qui test si la file est vide (1 si vide et 0 sinon)
int est_vide(File* f) {
    return f->elem == NULL;
}


//Fonction qui permet d'ajouter un nouvel element a la fin de la file
void enfiler(File* f, Sommet* s) {
    File* new = creer_file();
    new->elem = s;

    if (est_vide(f) == 1) {
        f = new;
    }
    else if (f->suiv == NULL) {
        new->prec = f;
        f->suiv = new;
    }
    else {
        File* suiv = f->suiv;
        while (suiv->suiv != NULL) {
            suiv = suiv->suiv;
        }
        new->prec = suiv;
        suiv->suiv = new;
    }
}


//Fonction qui retire et renvoie le premier element de la file
Sommet* defiler(File* f) {
    if (est_vide(f) == 1) {
        return NULL;
    }
    else if (f->prec == NULL) {
        return f->elem;
    }
    else {
        File* prec = f->prec;
        while(prec->prec != NULL) {
            prec = prec->prec;
        }
        Sommet* elem = prec->elem;
        free(prec);
        return elem;
    }
}


void afficher_file(File* f) {
    File* prec = f->prec;
    File* suiv = f->suiv;

    while(prec != NULL) {
        return;
    }

    while(suiv != NULL) {
        return;
    }
}