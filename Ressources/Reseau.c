#include <stdio.h>
#include <stdlib.h>

#include "Reseau.h"
#include "Chaine.h"
#include "SVGwriter.h"


//Exercice 2

//Question 1

/* Fonction qui retourne le noeud de R correspondant dans la liste chainee, sinon cree le noeud et l'ajoute dans R et dans la liste chainee */
Noeud* rechercheCreeNoeudListe(Reseau* R, double x, double y) {
    CellNoeud* liste = R->noeuds;

    while(liste) {
        if ((liste->nd->x == x) && (liste->nd->y == y)) return liste->nd;
        liste = liste->suiv;
    }

    //Creation du noeud si il n'existe pas
    Noeud* new_noeud = creer_noeud(x, y, R->nbNoeuds + 1);

    //Ajout dans le reseau
    ajoutNoeudReseau(R, new_noeud);

    return new_noeud;
}

//Question 2

/* Fonction qui reconstitue le reseau a partir d'une liste chainee */
Reseau* reconstitueReseauListe(Chaines* C) {

    //Création du réseau
    Reseau* reseau = creer_reseau(C->gamma);

    CellChaine* liste = C->chaines;

    //On parcourt toutes les CellChaine

    while(liste) {
        //Une chaine possede une commodite et une liste de CellNoeud avec des Noeud
        CellCommodite* commodite = creer_cellcommodite();   //On cree la commodite
        CellPoint* liste_points = liste->points;            //Liste des points dans la chaine 
        CellPoint* prec = liste_points;                     //On garde le precedent pour ajouter dans les voisins
        CellPoint* suiv = NULL;                             //On garde le suivant pour ajouter dans les voisins

        //Premier point: on recherche et l'ajoute si il n'existe pas dans Reseau
        Noeud* n = rechercheCreeNoeudListe(reseau, liste_points->x, liste_points->y);

        commodite->extrA = n;

        //On parcourt tous les CellPoint
        while(liste_points->suiv != NULL) {
            suiv = liste_points->suiv;

            Noeud* n = rechercheCreeNoeudListe(reseau, liste_points->x, liste_points->y); 
            
            //Ajout des voisins
            ajouter_voisin(n, rechercheCreeNoeudListe(reseau, prec->x, prec->y));
            ajouter_voisin(n, rechercheCreeNoeudListe(reseau, suiv->x, suiv->y));

            prec = liste_points;
            liste_points = liste_points->suiv;
        }

        commodite->extrB = rechercheCreeNoeudListe(reseau, liste_points->x, liste_points->y);
        //Le suivant est NULL, on ajoute le precedent
        ajouter_voisin(commodite->extrB, rechercheCreeNoeudListe(reseau, prec->x, prec->y)); 
        
        //On insere la commodite dans le reseau
        commodite->suiv = reseau->commodites;
        reseau->commodites = commodite;

        liste = liste->suiv;
    }

    return reseau;
}

//Exercice 3

//Question 1

/* Fonction qui retourne le nombre de liaisons que possede le reseau */
int nbLiaisons(Reseau* R) {

    //Nb liaisons est donne par la somme des nb de voisins de chaque CellNoeud divise par 2
    int nb_liaisons = 0; 
    CellNoeud* noeud_parcours = R->noeuds;

    //On parcourt tous les noeuds
    while(noeud_parcours) {

        int nb_voisins = 0;
        CellNoeud* liste_voisins = noeud_parcours->nd->voisins; //Voisins de ce noeud

        //On compte le nombre de voisins de ce noeud
        while(liste_voisins) {
            nb_voisins++;
            liste_voisins = liste_voisins->suiv;
        }

        nb_liaisons += nb_voisins;
        noeud_parcours = noeud_parcours->suiv;
    }

    return nb_liaisons/2;
}

/* Fonction qui retourne le nombre de commodite que possede le reseau */
int nbCommodites(Reseau* R) {
    int nbc = 0;
    CellCommodite* commodite = R->commodites;
    while(commodite) {
        nbc++;
        commodite = commodite->suiv;
    }
    
    return nbc;
}

//Question 2

/* Fonction qui ecrit le reseau dans un fichier */
void ecrireReseau(Reseau* R, FILE* f) {
    if (f == NULL) {
        printf("Erreur lors du chargement du fichier \n");
        exit(1);
    }

    CellNoeud* noeuds_reseau = R->noeuds;                //Recuperation de la liste des noeuds
    CellNoeud* liaisons_reseau = R->noeuds;              //Recuperation de la liste des noeuds pour les voisins (liaisons)
    CellCommodite* commodites_reseau = R->commodites;    //Recuperation de la liste des commodites

    int nb_noeuds = R->nbNoeuds;
    int nb_liaisons = nbLiaisons(R);
    int nb_commodites = nbCommodites(R);

    //Ecriture des 4 premieres lignes du fichier (constantes)
    fprintf(f, "NbNoeuds: %d\n", nb_noeuds);
    fprintf(f, "NbLiaisons: %d\n", nb_liaisons);
    fprintf(f, "NbCommodites: %d\n", nb_commodites);
    fprintf(f, "Gamma: %d\n", R->gamma);
    fprintf(f, "\n");

    //Ecriture des lignes qui commencent par "v" (noeuds du reseau)
    while(noeuds_reseau) {
        int num = noeuds_reseau->nd->num;
        double x = noeuds_reseau->nd->x;
        double y = noeuds_reseau->nd->y;
        fprintf(f, "v %d %f %f\n", num, x, y);

        noeuds_reseau = noeuds_reseau->suiv;
    }
    fprintf(f, "\n");
    
    //Ecriture des lignes qui commencent par "l" (liaisons du reseau)
    while(liaisons_reseau) {
        Noeud* n = liaisons_reseau->nd;
        CellNoeud* liste_n_vois = n->voisins;

        while(liste_n_vois != NULL) {
            Noeud* n_vois = liste_n_vois->nd;
            if (n->num > n_vois->num) {
                fprintf(f, "l %d %d\n", n_vois->num, n->num);
            }
            liste_n_vois = liste_n_vois->suiv;
        }

        liaisons_reseau = liaisons_reseau->suiv;
    }
    fprintf(f, "\n");
    
    //Ecriture des lignes qui commencent par "k" (commodites du reseau)
    for (int i = 0; i<nb_commodites; i++) {
        Noeud* a = commodites_reseau->extrA;
        Noeud* b = commodites_reseau->extrB;
        fprintf(f, "k %d %d\n", a->num, b->num);

        commodites_reseau = commodites_reseau->suiv;
    }
    fprintf(f, "\n");

    return;
}

//Question 3

/* Fonction qui affiche HTML Reseau */
void afficheReseauSVG(Reseau* R, char* nomInstance) {
    CellNoeud *courN, *courv;
    SVGwriter svg;
    double maxx = 0, maxy = 0, minx = 1e6, miny = 1e6;

    courN = R->noeuds;
    while(courN != NULL) {
        if (maxx < courN->nd->x)
            maxx = courN->nd->x;

        if (maxy < courN->nd->y)
            maxy = courN->nd->y;

        if (minx > courN->nd->x)
            minx = courN->nd->x;

        if (miny > courN->nd->y)
            miny = courN->nd->y;

        courN = courN->suiv;
    }

    SVGinit(&svg, nomInstance, 500, 500);
    courN = R->noeuds;
    while(courN != NULL) {
        SVGpoint(&svg, 500*(courN->nd->x - minx)/(maxx - minx), 500*(courN->nd->y - miny)/(maxy - miny));
        courv = courN->nd->voisins;

        while (courv != NULL) {
            if (courv->nd->num < courN->nd->num)
                SVGline(&svg, 500*(courv->nd->x - minx)/(maxx - minx), 500*(courv->nd->y - miny)/(maxy - miny), 500*(courN->nd->x - minx)/(maxx - minx), 500*(courN->nd->y - miny)/(maxy - miny));
            courv = courv->suiv;
        }
        courN = courN->suiv;
    }
    SVGfinalize(&svg);

    return;
}


//Fonctions de base

/* Fonction qui cree et renvoie un reseau vide */
Reseau* creer_reseau(int gamma) {
    Reseau* reseau = (Reseau *) malloc(sizeof(Reseau));
    reseau->nbNoeuds = 0;
    reseau->gamma = gamma;
    reseau->noeuds = NULL;
    reseau->commodites = NULL;

    return reseau;
}

/* Fonction qui cree et renvoie une commodite vide */
CellCommodite* creer_cellcommodite() {
    CellCommodite* cellc = (CellCommodite *) malloc(sizeof(CellCommodite));
    cellc->extrA = NULL; 
    cellc->extrB = NULL;
    cellc->suiv = NULL;

    return cellc;
}

/* Fonction qui cree et renvoie un CellNoeud vide */
CellNoeud* creer_cellnoeud(Noeud* noeud) {
    CellNoeud* celln = (CellNoeud *) malloc(sizeof(CellNoeud));
    celln->nd = noeud;
    celln->suiv = NULL;

    return celln;
}

/* Fonction qui cree et renvoie un noeud vide */
Noeud* creer_noeud(double x, double y, int num) {
    Noeud* n = (Noeud *) malloc(sizeof(Noeud));
    n->num = num;
    n->x = x;
    n->y = y;
    n->voisins = NULL;

    return n;
}

/* Fonction qui ajoute voisin aux voisins de n */
void ajouter_voisin(Noeud* n, Noeud* voisin) {
    if ((voisin == NULL) || (n == voisin)) return;

    //On recupere la liste de voisins actuelle
    CellNoeud* liste_voisin = n->voisins; 

    //On verifie si voisin est deja parmi les voisins
    while(liste_voisin) {   //Si dans voisins, la CellNoeud contient le meme noeud voisin
        if (liste_voisin->nd == voisin) return;
        liste_voisin = liste_voisin->suiv;
    }

    //Sinon on cree un CellNoeud et on ajoute le noeud
    CellNoeud* new_voisin = creer_cellnoeud(voisin);

    //On insere le voisin dans la liste des voisins
    new_voisin->suiv = n->voisins;
    n->voisins = new_voisin;
    
    return;
}

/* Fonction qui renvoie le nombre de commodites dans le reseau */
int nb_commodite(Reseau* r) {
    if (r == NULL) return 0;
    int nb = 0;
    CellCommodite* parcours = r->commodites;
    while(parcours) {
        nb++;
        parcours = parcours->suiv;
    }

    return nb;
}

/* Fonction qui ajoute un noeud dans le reseau */
void ajoutNoeudReseau(Reseau* reseau, Noeud* noeud) {
    CellNoeud* celln = (CellNoeud *) malloc(sizeof(CellNoeud));

    //Creation du noeud
    celln->nd = noeud;
    celln->suiv = reseau->noeuds;

    //Ajout dans reseau
    reseau->noeuds = celln;
    reseau->nbNoeuds = reseau->nbNoeuds + 1;  //On incremente le nombre de noeuds

    return;
}

//Fonctions de desallocation

/* Fonction qui libere un reseau */
void liberer_reseau(Reseau* r) {
    liberer_commodite(r->commodites);
    liberer_cellnoeud(r->noeuds);
    free(r);

    return;
}

/* Fonction qui libere un CellNoeud */
void liberer_cellnoeud(CellNoeud* c) {
    //On libere les Noeud et les Cellnoeud du reseau
    while(c) {
        CellNoeud* next = c->suiv;
        liberer_Noeud(c->nd);
        free(c);
        c = next;
    }

    return;
}

/* Fonction qui libere une commodite */
void liberer_commodite(CellCommodite* c) {
    //On libere toutes les commodites sans liberer les noeuds
    while(c) {
        CellCommodite* next = c->suiv;
        free(c);
        c = next;
    }

    return;
}

/* Fonction qui libere un noeud */
void liberer_Noeud(Noeud* n) {
    liberer_voisins(n);
    free(n);

    return;
}

/* Fonction qui libere les voisins d'un noeud */
void liberer_voisins(Noeud* n) {
    //On libere tout les Cellnoeud utilises pour les voisins
    //sans liberer les noeuds
    CellNoeud* vois = n->voisins, *suiv;
    while(vois) {
        suiv = vois->suiv;
        free(vois);
        vois = suiv;
    }

    return;
}
