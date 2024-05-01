#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "File.h"


//Fonction qui cree une nouvelle file
File* creer_file() {
    File* f = (File *) malloc(sizeof(File));
    f->premier = NULL;
    f->dernier = NULL;

    return f;
}

//Fonction qui teste si la file est vide (1 si vide et 0 sinon)
int est_vide(File* f) {
    return ((f->premier == NULL) || (f->dernier == NULL));
}

//Fonction qui ajoute un nouvel element a la fin de la file
void enfiler(File* f, Sommet* s) {
    Element* e = (Element *) malloc(sizeof(Element));
    e->s = s;
    e->suiv = NULL;

    if (f->premier == NULL) {
        f->premier = e;
        f->dernier = e;
    }
    else {
        f->dernier->suiv = e;
        f->dernier = e;
    }

    return;
}

//Fonction qui retire et renvoie le premier element de la file
Sommet* defiler(File* f) {
    //Cas : file vide
    if (est_vide(f) == 1) {
        return NULL;
    }
    //Cas : un seul element dans la file
    else if (f->premier == f->dernier) {
        Sommet* s = f->premier->s;
        free(f->premier);
        f->premier = NULL;
        f->dernier = NULL;

        return s;
    }
    else {
        //On recupere le sommet du premier element dans la file
        Sommet* s = f->premier->s;
        Element* tmp = f->premier;
        f->premier = f->premier->suiv;
        //On libere l'element
        free(tmp);

        return s;
    }
}

//Fonction qui libere la file
void liberer_file(File* f) {
    Element* element = f->premier, *tmp;
    while(element) {
        tmp = element->suiv;
        free(element);
        element = tmp;
    }
    free(f);

    return;
}

//Fonction qui affiche la file
void afficher_file(File* f) {
    Element* el = f->premier;
    printf("\n\nFile :");
    while(el) {
        printf("%d ", el->s->num);
        el = el->suiv;
    }

    return;
}
