#ifndef __RESEAU_H__
#define __RESEAU_H__
#include "Chaine.h"
#include <stdio.h>

typedef struct noeud Noeud;

/* Liste chainee de noeuds (pour la liste des noeuds du reseau ET les listes des voisins de chaque noeud) */
typedef struct cellnoeud {
    Noeud *nd;                      /* Pointeur vers le noeud stocké */
    struct cellnoeud *suiv;         /* Cellule suivante dans la liste */
} CellNoeud;

/* Noeud du reseau */
struct noeud{
   int num;                        /* Numero du noeud */
   double x, y;                    /* Coordonnees du noeud*/
   CellNoeud *voisins;             /* Liste des voisins du noeud */
}; //Noeud

/* Liste chainee de commodites */
typedef struct cellCommodite {
    Noeud *extrA, *extrB;           /* Noeuds aux extremites de la commodite */
    struct cellCommodite *suiv;     /* Cellule suivante dans la liste */
} CellCommodite;

/* Un reseau */
typedef struct {
    int nbNoeuds;                   /* Nombre de noeuds du reseau */
    int gamma;                      /* Nombre maximal de fibres par cable */
    CellNoeud *noeuds;              /* Liste des noeuds du reseau */
    CellCommodite *commodites;      /* Liste des commodites a relier */
} Reseau;

Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y);
Reseau* reconstitueReseauListe(Chaines *C);
void ecrireReseau(Reseau *R, FILE *f);
int nbLiaisons(Reseau *R);
int nbCommodites(Reseau *R);
void afficheReseauSVG(Reseau *R, char* nomInstance);

//fonctions implementees par nous meme

Reseau* creer_reseau(int gamma);
CellCommodite* creer_cellcommodite();
CellNoeud* creer_cellnoeud(Noeud* noeud);
Noeud* creer_noeud(double x, double y, int num); 
void ajouter_voisin(Noeud* n, Noeud* voisin);
int nb_commodite(Reseau* r);
void ajoutNoeudReseau(Reseau* reseau, Noeud* noeud);

//Desallocation

void liberer_reseau(Reseau* r);
void liberer_cellnoeud(CellNoeud * c);
void liberer_commodite(CellCommodite* c);
void liberer_voisins(Noeud* n);
void liberer_Noeud(Noeud* n);

#endif