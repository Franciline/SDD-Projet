#ifndef __RESEAU_H__
#define __RESEAU_H__

#include "Chaine.h"
#include <stdio.h>


typedef struct noeud Noeud;

/* Liste chainee de noeuds (pour la liste des noeuds du reseau ET les listes des voisins de chaque noeud) */
typedef struct cellnoeud {
    Noeud* nd;                      /* Pointeur vers le noeud stocke */
    struct cellnoeud *suiv;         /* Cellule suivante dans la liste */
} CellNoeud;

/* Noeud du reseau */
struct noeud{
   int num;                        /* Numero du noeud */
   double x, y;                    /* Coordonnees du noeud */
   CellNoeud* voisins;             /* Liste des voisins du noeud */
}; //Noeud

/* Liste chainee de commodites */
typedef struct cellCommodite {
    Noeud *extrA, *extrB;           /* Noeuds aux extremites de la commodite */
    struct cellCommodite* suiv;     /* Cellule suivante dans la liste */
} CellCommodite;

/* Un reseau */
typedef struct {
    int nbNoeuds;                   /* Nombre de noeuds du reseau */
    int gamma;                      /* Nombre maximal de fibres par cable */
    CellNoeud* noeuds;              /* Liste des noeuds du reseau */
    CellCommodite* commodites;      /* Liste des commodites a relier */
} Reseau;


Noeud* rechercheCreeNoeudListe(Reseau* R, double x, double y);  // Exercice 2 Question 1
Reseau* reconstitueReseauListe(Chaines* C);                     // Exercice 2 Question 2
void ecrireReseau(Reseau* R, FILE* f);
int nbLiaisons(Reseau* R);
int nbCommodites(Reseau* R);
void afficheReseauSVG(Reseau* R, char* nomInstance);

//Fonctions implementees par nous-meme

Reseau* creer_reseau(int gamma);
CellCommodite* creer_cellcommodite();
CellNoeud* creer_cellnoeud(Noeud* noeud);
Noeud* creer_noeud(double x, double y, int num); 
void ajouter_voisin(Noeud* n, Noeud* voisin);
int nb_commodite(Reseau* r);
void ajoutNoeudReseau(Reseau* reseau, Noeud* noeud);

//Fonctions de desallocation

void liberer_reseau(Reseau* r);             // Fonction qui libere un Reseau
void liberer_cellnoeud(CellNoeud* c);       // Fonction qui libere un CellNoeud
void liberer_commodite(CellCommodite* c);   // Fonction qui libere un CellCommodie
void liberer_voisins(Noeud* n);             // Fonction qui libere les voisins d'un noeud n
void liberer_Noeud(Noeud* n);               // Fonction qui libere un Noeud

#endif
