#ifndef __CHAINE_H__
#define __CHAINE_H__	
#include <stdio.h>


/* Liste chainee de points */
typedef struct cellPoint{
  double x, y;                   /* Coordonnees du point */
  struct cellPoint *suiv;       /* Cellule suivante dans la liste */
} CellPoint;

/* Cellule d'une liste (chainee) de chaines */
typedef struct cellChaine{
  int numero;                   /* Numero de la chaine */
  CellPoint *points;            /* Liste des points de la chaine */
  struct cellChaine *suiv;      /* Cellule suivante dans la liste */
} CellChaine;

/* L'ensemble des chaines */
typedef struct {
  int gamma;                    /* Nombre maximal de fibres par cable */
  int nbChaines;                /* Nombre de chaines */
  CellChaine *chaines;          /* La liste chainee des chaines */
} Chaines;


Chaines* lectureChaines(FILE* f);                       // Exercice 1 Question 1
void ecrireChaines(Chaines* C, FILE* f);                // Exercice 1 Question 2
void afficheChainesSVG(Chaines* C, char* nomInstance);  // Exercice 1 Question 3
double longueurChaine(CellChaine* c);                   // Exercice 1 Question 4
double longueurTotale(Chaines* C);
int comptePoints(CellChaine* c);                        // Exercice 1 Question 5
int comptePointsTotal(Chaines* C);

Chaines* generationAleatoire(int nbChaines, int nbPointsChaine, int xmax, int ymax);  // Exercice 6 Question 2

// Fonctions de base
Chaines* creer_chaine();
double distance(CellPoint* a, CellPoint* b);

//Fonctions de desallocation
void liberer_chaine(Chaines* C);
void liberer_cellchaine(CellChaine* c);
void liberer_cellpoint(CellPoint* p);

#endif
