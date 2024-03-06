#include "Reseau.h"
#include "Chaine.h"
#include <stdio.h>
#include <stdlib.h>
#define EPSILON 0.000001

//EXERCICE 2

//fonctions de base
/*Renvoie un réseau vide*/
Reseau* creer_reseau(){
    Reseau* reseau = (Reseau*)(malloc(sizeof(Reseau)));
    reseau->nbNoeuds = 0;
    reseau->gamma = 0;
    reseau->noeuds = NULL;
    reseau->commodites = NULL;

    return reseau;
}

/*Renvoie une commodité vide*/
CellCommodite* creer_cellcommodite(){
    CellCommodite* cellc = (CellCommodite*)(malloc(sizeof(CellCommodite)));
    cellc->extrA = NULL; 
    cellc->extrB = NULL;
    cellc->suiv = NULL;
    return cellc;

}

/*Renvoie un CellNoeud vide*/
CellNoeud* creer_cellnoeud(){
    CellNoeud* celln = (CellNoeud*)(malloc(sizeof(CellNoeud)));
    celln -> nd = NULL;
    celln->suiv=NULL;
    return celln;
}

/*Renvoie un noeud vide*/
Noeud* creer_noeud(){
    Noeud* n = (Noeud*)(malloc(sizeof(Noeud)));
    n->num = 0;
    n->x = 0;
    n->y = 0;
    n->voisins = NULL;
    return n;
}

/*Ajoute voisin aux voisins de n*/
void ajouter_voisin(Noeud* n, Noeud* voisin){
    if (voisin = NULL) return;

    CellNoeud * liste_voisin = n->voisins;
    //on vérifie si dedans;
    while(liste_voisin){
        if (liste_voisin->nd->num == voisin->num) return ;
    }
    //sinon on créer cellule et ajoute le noeud
    CellNoeud* new_voisin = creer_cellnoeud();
    new_voisin -> nd = voisin;

    //on affecte ce voisin par insertion en tête
    new_voisin->suiv = n->voisins;
    n->voisins = new_voisin;
}


//Question 1
/*Retourne le noeud de R correspondant, sinon créer le noeud et l'ajoute dans R*/
Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y){

    CellNoeud * liste = R->noeuds;

    while (liste){
        if ((liste->nd->x - x < EPSILON) && (liste->nd->y - y < EPSILON)) return liste;
        liste = liste->suiv;
    }

    //création du noeud
    Noeud * new_noeud = creer_noeud();
    new_noeud->x = x;
    new_noeud->y = y;
    new_noeud->num = R->nbNoeuds + 1;
    new_noeud->voisins = NULL;

    //creation de la cellule
    CellNoeud * new_celln = (CellNoeud*)(malloc(sizeof(CellNoeud)));
    new_celln -> nd = new_noeud;
    new_celln -> suiv = R->noeuds;
    
    //ajout dans R
    R->noeuds = new_celln;
    R->nbNoeuds = R->nbNoeuds + 1;

    return new_noeud;
}

//Question 2
/*Reconstiture le réseau à partir de la liste chainée*/
Reseau* reconstitueReseauListe(Chaines *C){

    //Création du réseau
    Reseau* reseau = creer_reseau();
    reseau->gamma=C->gamma;

    CellChaine* liste = C->chaines;

    //on parcourt toutes les CellChaines
    while(liste){
        //une chaine possède une commodité, une liste de CellNoeud avec des Noeuds
        CellCommodite* commodite = creer_cellcommodite();
        CellPoint * liste_points = liste->points;
        CellPoint* prec = NULL, *suiv = NULL;

        //premier point: on rechercher et l'ajoute si n'existe pas
        Noeud* n = rechercheCreeNoeudListe(reseau, liste_points->x, liste_points->y);

        //on sauvegarde la commodité
        commodite->extrA = n;

        //On parcourt tous les CellPoints
        while(liste_points->suiv != NULL){
            suiv = liste->points;
            Noeud * n = rechercheCreeNoeudListe(reseau, liste_points->x, liste_points->y);
            prec = liste_points;
            //ajout des voisins
            ajouter_voisin(n, prec);
            ajouter_voisin(n, suiv);
            liste_points=liste_points->suiv;
        }

        //on arrive au dernier point
        commodite->extrB = rechercheCreeNoeudListe(reseau, liste_points->x, liste_points->y);
        ajouter_voisin(commodite->extrB, prec); //le suivant est NULL
        
        //on insere en tete la commodité
        commodite->suiv = reseau->commodites;
        reseau->commodites = commodite;

        //On a ajouté commodité et noeud de la chaine à réseau, on passe à la liste suivante
        liste = liste->suiv;

    }

    return reseau;
}

//EXERCICE 3

//Question 1
/*Retourne le nombre de liaisons que possède le réseau*/
int nbLiaisons(Reseau *R){
    //nb liaisons est donné par la somme des nb de voisins de chaque CellNoeud / 2 
    int nb_liaisons = 0; 
    CellNoeud* noeud_parcours = R->noeuds;

    //on parcours tous les noeuds
    while(noeud_parcours){

        int nb_voisins = 0;
        CellNoeud* liste_voisins = noeud_parcours->nd->voisins; //les voisins de ce noeud

        //on compte le nombre de voisins de ce noeud
        while(liste_voisins){
            nb_voisins ++;
            liste_voisins = liste_voisins->suiv;
        }

        nb_liaisons += nb_voisins;
        noeud_parcours = noeud_parcours->suiv;
    }
    return nb_liaisons / 2;
}

/*Retourne le nombre de commodité que possède le réseau*/
int nbCommodites(Reseau *R){
    int nbc = 0;
    CellCommodite* commodite = R->commodites;
    while(commodite){
        nbc++;
        commodite = commodite->suiv;
    }
    return nbc;
}

// Question 2
/*Ecrit le reseau dans un fichier*/
void ecrireReseau(Reseau *R, FILE *f) {
    if (f == NULL) {
        printf("Erreur lors du chargement du fichier \n");
        exit(1);
    }

    CellNoeud noeuds_reseau = R->noeuds;                //Recuperation de la liste des noeuds
    CellNoeud liaisons_reseau = R->noeuds;              //Recuperation de la liste des noeuds pour les voisins (liaisons)
    CellCommodite commodites_reseau = R->commodites;    //Recuperation de la liste des commodites

    int nb_noeuds = R->nbNoeuds;
    int nb_liaisons = nbLiaisons(R);
    int nb_commodites = nbCommodites(R);

    // Ecriture des 4 premieres lignes du fichier
    fprintf(f, "NbNoeuds: %d\n", nb_noeuds);
    fprintf(f, "NbLiaisons: %d\n", nb_liaisons);
    fprintf(f, "NbCommodites: %d\n", nb_commodites);
    fprintf(f, "Gamma: %d\n", R->gamma);
    fprintf(f, "\n");

    // Ecriture des lignes commencant par "v" (noeuds du reseau)
    for (int i = 0; i<nb_noeuds; i++) {
        int num = noeuds_reseau->nd->num;
        double x = noeuds_reseau->nd->x;
        double y = noeuds_reseau->nd->y
        fprintf(f, "v %d %f %f\n", num, x, y);

        noeuds_reseau = noeuds_reseau->suiv;
    }
    fprintf(f, "\n");
    
    // Ecriture des lignes commencant par "l" (liaisons du reseau)
    for (int i = 0; i<nb_liaisons; i++) {
        Noeud* n = liaisons_reseau->nb;
        CellNoeud* liste_n_vois = n->voisins;

        while (liste_n_vois != NULL) {
            Noeud* n_vois = liste_n_vois->nd;
            fprintf(f, "l %d %d\n", n_vois->num, n->num);

            liste_n_vois = liste_n_vois->suiv;
        }

        liaisons_reseau = liaisons_reseau->suiv;
    }
    fprintf(f, "\n");
    
    // Ecriture des lignes commencant par "k" (commodites du reseau)
    for (int i = 0; i<nb_commodites; i++) {
        Noeud* a = commodites_reseau->extraA;
        Noeud* b = commodites_reseau->extraB;
        fprintf(f, "k %d %d\n", a->num, b->num);

        commodites_reseau = commodites_reseau->suiv;
    }
    fprintf(f, "\n");
}
