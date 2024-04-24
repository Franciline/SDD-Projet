#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Chaine.h"
#include "SVGwriter.h"

#define TAILLE_MAX 512


//Exercice 1

//Question 1

/* Fonction de lecture des chaines depuis un fichier */
Chaines* lectureChaines(FILE* f) {
    if (f == NULL) {
        printf("Il faut entrer un nom de fichier ! \n");
        exit(1);
    }

    int nbChain, gamma, num, nb_pts;
    double x, y;

    Chaines* chaine = creer_chaine();
    char ligne[TAILLE_MAX];

    // On recupere la 1ere ligne du fichier qui contient nbChain
    fgets(ligne, sizeof(ligne), f);
    sscanf(ligne, "NbChain: %d\n", &nbChain);
    
    // On recupere la 2eme ligne du fichier qui contient gamma
    fgets(ligne, sizeof(ligne), f);
    sscanf(ligne, "Gamma: %d\n", &gamma);

    chaine->nbChaines = nbChain;
    chaine->gamma = gamma;

    // On parcourt les lignes jusqu'a la fin du fichier
    for (int i=0; i<nbChain; i++){
        fgets(ligne, sizeof(ligne), f);
        sscanf(ligne, "%d %d %[^\n]\n", &num, &nb_pts, ligne);
        CellChaine* cellC = (CellChaine*) malloc(sizeof(CellChaine));
        cellC->points = NULL;
        cellC->numero = num;

        for (int j=0; j<nb_pts; j++) {
            sscanf(ligne, "%lf %lf %[^\n]\n", &x, &y, ligne);
            CellPoint* cellP = (CellPoint*) malloc(sizeof(CellPoint));
            cellP->x = x;
            cellP->y = y;
            cellP->suiv = cellC->points;
            cellC->points = cellP;
        }
        cellC->suiv = chaine->chaines;
        chaine->chaines = cellC;
    }
    return chaine;
}

//Question 2

/* Fonction d'ecriture des chaines dans un fichier */
void ecrireChaines(Chaines* C, FILE* f){
    if (f == NULL) {
        printf("Il faut entrer un nom de fichier ! \n");
        exit(1);
    }

    fprintf(f, "NbChain: %d\n", C->nbChaines);
    fprintf(f, "Gamma: %d\n", C->gamma);
    
    CellChaine* tmp_cell = C->chaines;
    while(tmp_cell){
        //On compte le nombre de points dans la liste chainee
        int nb_point = 0;
        CellPoint* tmp_point = tmp_cell->points;
        while(tmp_point){
            nb_point++;
            tmp_point = tmp_point->suiv;
        }

        fprintf(f, "%d %d ", tmp_cell->numero, nb_point);
        tmp_point = tmp_cell->points;
        while(tmp_point){
            fprintf(f, "%lf %lf ", tmp_point->x, tmp_point->y);
            tmp_point = tmp_point->suiv;
        }
        fprintf(f, "\n");
        tmp_cell = tmp_cell->suiv;
    }
}

//Question 3

/* Affichage des chaines */
void afficheChainesSVG(Chaines* C, char* nomInstance){
    double maxx=0, maxy=0, minx=1e6, miny=1e6;
    CellChaine* ccour;
    CellPoint* pcour;
    double precx, precy;
    SVGwriter svg;
    ccour = C->chaines;
    while(ccour != NULL){
        pcour = ccour->points;
        while(pcour != NULL){
            if (maxx < pcour->x) maxx = pcour->x;
            if (maxy < pcour->y) maxy = pcour->y;
            if (minx > pcour->x) minx = pcour->x;
            if (miny > pcour->y) miny = pcour->y;  
            pcour = pcour->suiv;
        }
    ccour = ccour->suiv;
    }
    SVGinit(&svg, nomInstance, 500, 500);
    ccour = C->chaines;
    while(ccour != NULL){
        pcour = ccour->points;
        SVGlineRandColor(&svg);
        SVGpoint(&svg, 500*(pcour->x - minx)/(maxx - minx), 500*(pcour->y - miny)/(maxy - miny)); 
        precx = pcour->x;
        precy = pcour->y;  
        pcour = pcour->suiv;
        while(pcour != NULL){
            SVGline(&svg, 500*(precx - minx)/(maxx - minx), 500*(precy - miny)/(maxy - miny), 500*(pcour->x - minx)/(maxx - minx), 500*(pcour->y - miny)/(maxy - miny));
            SVGpoint(&svg, 500*(pcour->x - minx)/(maxx - minx), 500*(pcour->y - miny)/(maxy - miny));
            precx = pcour->x;
            precy = pcour->y;    
            pcour = pcour->suiv;
        }
        ccour = ccour->suiv;
    }
    SVGfinalize(&svg);
}

//Question 4

/* Calcul de la longueur d'une chaine */
double longueurChaine(CellChaine* c) {
    double longueur = 0;
    CellPoint* liste_points = c->points;

    while((liste_points != NULL) && (liste_points->suiv != NULL)) {
        longueur += distance(liste_points, liste_points->suiv);
        liste_points = liste_points->suiv;
    }

    return longueur;
}

/* Calcul de la longueur totale de toutes les chaines */
double longueurTotale(Chaines* C) {
    double longueur = 0;
    CellChaine* liste_chaines = C->chaines;

    while(liste_chaines != NULL) {
        longueur += longueurChaine(liste_chaines);
        liste_chaines = liste_chaines->suiv;
    }

    return longueur;
}

//Question 5

/* Renvoie le nombre d'occurrences de points dans une chaine */
int comptePoints(CellChaine* c) {
    int nb_pts = 0;
    CellPoint* liste_points = c->points;

    while(liste_points != NULL) {
        nb_pts++;
        liste_points = liste_points->suiv;
    }

    return nb_pts;
}

/* Renvoie le nombre total d'occurrences de points dans le reseau */
int comptePointsTotal(Chaines *C) {
    int nb_pts = 0;
    CellChaine *liste_chaines = C->chaines;

    while(liste_chaines != NULL) {
        nb_pts += comptePoints(liste_chaines);
        liste_chaines = liste_chaines->suiv;
    }

    return nb_pts;
}

//Exercice 6

//Question 2

/* Genere aleatoirement nbChaines chaines contenant nbPointsChaine points */
Chaines* generationAleatoire(int nbChaines, int nbPointsChaine, int xmax, int ymax) {
    Chaines* chaines = creer_chaine();

    for (int i=0; i<nbChaines; i++) {
        CellChaine* cellC = (CellChaine*) malloc(sizeof(CellChaine));
        cellC->points = NULL;
        cellC->numero = i;

        for (int j=0; j<nbPointsChaine; j++) {
            CellPoint* cellP = (CellPoint*) malloc(sizeof(CellPoint));
            cellP->x = rand() % xmax;
            cellP->y = rand() % ymax;
            cellP->suiv = cellC->points;
            cellC->points = cellP;
        }

        cellC->suiv = chaines->chaines;
        chaines->chaines = cellC;
        chaines->nbChaines++;
    }

    return chaines;
}


// Fonctions de bases

/*Initialise une chaine vide*/
Chaines* creer_chaine() {
    Chaines* chaine = (Chaines*) malloc(sizeof(Chaines));
    chaine->gamma = 0;
    chaine->nbChaines = 0;
    chaine->chaines = NULL;
    return chaine;
}

/*Calcule la distance entre deux points a et b*/
double distance(CellPoint* a, CellPoint* b) {
    double xa = a->x;
    double ya = a->y;
    double xb = b->x;
    double yb = b->y;

    return sqrt(((xb - xa)*(xb - xa)) + ((yb - ya)*(yb - ya)));
}


//Fonctions de desallocation

/* Libere une Chaine */
void liberer_chaine(Chaines* C){
    liberer_cellchaine(C->chaines);
    free(C);
}

/* Libere une CellChaine */
void liberer_cellchaine(CellChaine* c){
    while(c){
        CellChaine* next = c->suiv;
        liberer_cellpoint(c->points);
        free(c);
        c = next;
    }
}

/* Libere un CellPoint */
void liberer_cellpoint(CellPoint* p){
    while(p){
        CellPoint* next = p->suiv;
        free(p);
        p = next;
    }
}
