#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Chaine.h"
#include "SVGwriter.h"

#define TAILLE_MAX 512
// Exercice 1

//fonctions de bases
/*Creer une chaine*/
Chaines* creer_chaine() {
    Chaines* chaine = (Chaines*)malloc(sizeof(Chaines));
    chaine->gamma = 0;
    chaine->nbChaines = 0;
    chaine->chaines = NULL;
    return chaine;
}

//Question 1
/*Fonction de lecture des chaines depuis un fichier'*/
Chaines* lectureChaines(FILE *f) {
    if (f == NULL) {
        printf("Erreur lors du chargement du fichier \n");
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

    for (int i = 0; i<nbChain; i++){
        fgets(ligne, sizeof(ligne), f);
        sscanf(ligne, "%d %d %[^\n]\n", &num, &nb_pts, ligne);
        CellChaine* cellC = (CellChaine*) malloc(sizeof(CellChaine));
        cellC->points = NULL;
        cellC->numero = num;

        for (int i = 0; i<nb_pts; i++) {
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

//Question 2: fonction d'écriture
/*Fonction écriture des chaines dans un fichier*/
void ecrireChaines(Chaines *C, FILE* f){
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
            fprintf(f, "%lf %lf ", tmp_point->x, tmp_point->y);
            tmp_point=tmp_point->suiv;
        }
        fprintf(f, "\n");
        tmp_cell = tmp_cell->suiv;
    }
    
    return;
}

//Question 3
/*Affichage des chaines*/
void afficheChainesSVG(Chaines *C, char* nomInstance){
    //int i;
    double maxx=0,maxy=0,minx=1e6,miny=1e6;
    CellChaine *ccour;
    CellPoint *pcour;
    double precx,precy;
    SVGwriter svg;
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        while (pcour!=NULL){
            if (maxx<pcour->x) maxx=pcour->x;
            if (maxy<pcour->y) maxy=pcour->y;
            if (minx>pcour->x) minx=pcour->x;
            if (miny>pcour->y) miny=pcour->y;  
            pcour=pcour->suiv;
        }
    ccour=ccour->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        SVGlineRandColor(&svg);
        SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny)); 
        precx=pcour->x;
        precy=pcour->y;  
        pcour=pcour->suiv;
        while (pcour!=NULL){
            SVGline(&svg,500*(precx-minx)/(maxx-minx),500*(precy-miny)/(maxy-miny),500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            precx=pcour->x;
            precy=pcour->y;    
            pcour=pcour->suiv;
        }
        ccour=ccour->suiv;
    }
    SVGfinalize(&svg);
}
