#ifndef __GRAPHE_H__
#define __GRAPHE_H__
#include <stdlib.h>
#include <stdio.h>
#include "Reseau.h"

typedef struct {
int u ,v ; /* Numeros des sommets extremite */
} Arete ;


typedef struct cellule_arete {
    Arete * a ;         /* pointeur sur l’arete */
    struct cellule_arete * suiv ;
} Cellule_arete ;

typedef struct {
    int num ;           /* Numero du sommet (le meme que dans T_som) */
    double x , y ;
    Cellule_arete * L_voisin ; /* Liste chainee des voisins */
} Sommet ;

typedef struct {
    int e1 , e2 ;       /* Les deux extremites de la commodite */
} Commod ;

typedef struct {
    int nbsom ;         /* Nombre de sommets */
    Sommet ** T_som ;   /* Tableau de pointeurs sur sommets */
    int gamma ;
    int nbcommod ;      /* Nombre de commodites */
    Commod * T_commod ; /* Tableau des commodites */
} Graphe ;

//nos propres structure a implementer
typedef struct arbre_chemin {
    int num;
    struct arbre_chemin* fils;
    struct arbre_chemin* suivant;
} Arbre_chemin;

Arbre_chemin* creerArbreChemin(int n);
void ajouterFilsArbreChemin(Arbre_chemin* a,int n);

//fonctions demandees
Graphe* creerGraphe(Reseau* r);
int plus_petit_nb_aretes(Graphe* g, Sommet* u, Sommet* v);
//stockage en largeur/profondeur
int reorganiseReseau(Reseau* r);

//fonctions implementees par nous meme
Graphe* initGrapheVide(int nbsom, int gamma, int nbcommod);
Commod* creerCommod(int e1, int e2);
Sommet* creerSommet(int num, double x, double y);
Arete* creerArete(int u, int v);
Cellule_arete* creerCellule_arete(Arete * a);

//Desallocation
void libererGraphe(Graphe* graphe);
void libererCommod(Commod* commod);
void libererSommet(Sommet* sommet);
void libererCellule_arete(Cellule_arete* ca);
void libererArete(Arete* a);
# endif
