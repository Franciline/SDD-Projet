<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Chaine.h"

// Exercice 1

Chaines* creer_chaine() {
    Chaines* chaine = (Chaines*) malloc(sizeof(Chaines));
    chaine->gamma = 0;
    chaine->nbChaines = 0;
    chaine->chaines = NULL;
}


Chaines* lectureChaine(FILE *f) {
    FILE* fichier = fopen(f, "r");

    if (fichier == NULL) {
        printf("Erreur lors du chargement du fichier %s\n", f);
        exit(1);
    }

    char nbChain_s[10];
    int nbChain_i;

    char gamma_s[10];
    int gamma_i;

    int num;
    int nb_pts;
    double x;
    double y;

    Chaines* chaine = creer_chaine();

    CellChaine* cellC_suiv;
    CellPoint* cellP_suiv;

    int TAILLE_MAX = 20;
    char ligne[TAILLE_MAX];

    // On recupere la 1ere ligne du fichier qui contient nbChain
    fgets(ligne, sizeof(ligne), fichier);
    sscanf(ligne, "%ms %d", &nbChain_s, &nbChain_i);
    
    // On recupere la 2eme ligne du fichier qui contient gamma
    fgets(ligne, sizeof(ligne), fichier);
    sscanf(ligne, "%ms %d", &gamma_s, &gamma_i);

    while(fgets(ligne, TAILLE_MAX, fichier) != NULL) {
        fscanf(fichier, "%d %d", &num, &nb_pts);
        //sscanf(ligne, "%d %d %f", num, nb_pts, liste_points);
        
        CellChaine* cellC = (CellChaine*) malloc(sizeof(CellChaine));
        cellC->numero = num;
        chaine->chaines = cellC;

        CellPoint* cellP = (CellPoint*) malloc(sizeof(CellPoint));

        for (int i = 0; i<nb_pts; i++) {
            fscanf(fichier, "%f %f", &x, &y);
            CellPoint* cellP = (CellPoint*) malloc(sizeof(CellPoint));
            cellP->x = x;
            cellP->y = y;
            cellP->suiv = cellC->points;
            cellC->points = cellP;
        }

        cellC->suiv = chaine->chaines;
        chaine->chaines = CellC;
    }
    
    return chaine;
}

void ecrireChaine(Chaines *C, FILE* f){
    if (f == NULL) return;

    fprintf(f, "NbChain: %d\n", C->nbChaines);
    fprintf(f, "Gamma: %d\n", C->gamma);

    CellChaine * tmp_cell = C->chaines;
    while(tmp_cell){
        //on compte le nombre de points dans la liste chainée 
        int nb_point = 0;
        CellPoint * tmp_point = tmp_cell->points;
        while(tmp_point){
            nb_point++;
            tmp_point = tmp_point->suiv;
        }

        fprintf(f, "%d %d ", tmp_cell->numero, nb_point);
        tmp_point = tmp_cell->points;
        while(tmp_point){
            fprintf(f, "%f %f ", tmp_point->x, tmp_point->y);
            tmp_point=tmp_point->suiv;
        }
        fprintf(f, "\n");
    }
    
    fclose(f);
    return;
}
