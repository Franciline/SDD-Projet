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


//fonctions demandees

Graphe* creerGraphe(Reseau* r);                                     // Exercice 1 Question 1 
int plus_petit_nb_aretes(Graphe* g, Sommet* u, Sommet* v);          // Exercice 1 Question 2
int* plus_petit_nb_aretes_liste(Graphe* g, Sommet* u, Sommet* v);   // Exercice 1 Question 3
int reorganiseReseau(Reseau* r);                                    // Exercice 1 Question 4

//fonctions implementees par nous meme

Graphe* initGrapheVide(int nbsom, int gamma, int nbcommod);         // Initialise et renvoie un graphe 
Commod creerCommod(int e1, int e2);                                 // Initialise et renvoie une commodite (structure)    
Sommet* creerSommet(int num, double x, double y);                   // Initialise et renvoie un sommet
Arete* creerArete(int u, int v);                                    // Initialise et renvoie une arete
Cellule_arete* creerCellule_arete(Arete * a);                       // Initialise et renvoie une cellule arete

//Desallocation

void liberer_Graphe(Graphe* graphe);                                // Libere un graphe
void liberer_Commod(Commod* commod);                                // Libere une commodite
void liberer_Sommet(Graphe* graphe, Sommet* sommet);                // Libere un sommet
# endif
