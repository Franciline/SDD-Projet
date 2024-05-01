#include "Reseau.h"
#include "Chaine.h"
#include <stdio.h>
#include <stdlib.h>
#include "SVGwriter.h"

//EXERCICE 2

//QUESTION 1

/*Retourne le noeud de R correspondant, sinon creer le noeud et l'ajoute dans R*/
Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y){
    CellNoeud * liste = R->noeuds;

    while (liste){
        //égalité des doubles fait avec la différence
        if ((liste->nd->x == x) && (liste->nd->y == y)) return liste->nd;
        liste = liste->suiv;
    }

    //cas ou n'existe pas
    //creation du noeud si n'existe pas
    Noeud * new_noeud = creer_noeud(x, y, R->nbNoeuds + 1);

    //creation de la cellule
    CellNoeud * new_celln = (CellNoeud*)(malloc(sizeof(CellNoeud)));
    new_celln -> nd = new_noeud; //on affecte le noeud dans la cellule
    new_celln -> suiv = R->noeuds; //on ajoute a la suite de la liste de CellNoeud dans Reseau
    
    //ajout dans R
    R->noeuds = new_celln;
    R->nbNoeuds = R->nbNoeuds + 1; //on incrémente le nombre de noeuds

    return new_noeud;
}

//QUESTION 2


/*Reconstitue le reseau à partir de la liste chainee*/
Reseau* reconstitueReseauListe(Chaines *C){

    //Création du réseau
    Reseau* reseau = creer_reseau();
    reseau->gamma=C->gamma;

    CellChaine* liste = C->chaines;

    //on parcourt toutes les CellChaines

    while(liste){
        //une chaine possede une commodite et une liste de CellNoeud avec des Noeuds
        CellCommodite* commodite = creer_cellcommodite();   //on crée la commodité
        CellPoint * liste_points = liste->points;           //liste des points dans la chaine 
        CellPoint* prec = liste_points, *suiv = NULL;       //On garde le précédent et le suivant pour ajouter dans les voisins        

        //premier point: on recherche et l'ajoute si n'existe pas dans Reseau
        Noeud* n = rechercheCreeNoeudListe(reseau, liste_points->x, liste_points->y);

        commodite->extrA = n;

        //On parcourt tous les CellPoints
        while(liste_points->suiv != NULL){
            suiv = liste_points->suiv;

            Noeud * n = rechercheCreeNoeudListe(reseau, liste_points->x, liste_points->y); 
            
            //ajout des voisins
            ajouter_voisin(n, rechercheCreeNoeudListe(reseau, prec->x, prec->y));
            ajouter_voisin(n, rechercheCreeNoeudListe(reseau, suiv->x, suiv->y));

            prec = liste_points;
            liste_points = liste_points->suiv;
        }

        commodite->extrB = rechercheCreeNoeudListe(reseau, liste_points->x, liste_points->y);
        //le suivant est NULL, on ajoute le precedent
        ajouter_voisin(commodite->extrB, rechercheCreeNoeudListe(reseau, prec->x, prec->y)); 
        
        //on insere la commodite
        commodite->suiv = reseau->commodites;
        reseau->commodites = commodite;

        //On a ajoute commodite et noeud de la chaine a réseau, on passe à la liste suivante
        liste = liste->suiv;
    }

    return reseau;
}


//EXERCICE 3

//QUESTION 1
/*Retourne le nombre de liaisons que possede le reseau*/
int nbLiaisons(Reseau *R){

    //nb liaisons est donne par la somme des nb de voisins de chaque CellNoeud / 2 
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

/*Retourne le nombre de commodite que possede le reseau*/
int nbCommodites(Reseau *R){
    int nbc = 0;
    CellCommodite* commodite = R->commodites;
    while(commodite){
        nbc++;
        commodite = commodite->suiv;
    }
    return nbc;
}

// QUESTION 2
/*Ecrit le reseau dans un fichier*/
void ecrireReseau(Reseau *R, FILE *f) {
    if (f == NULL) {
        printf("Erreur lors du chargement du fichier \n");
        exit(1);
    }

    CellNoeud *noeuds_reseau = R->noeuds;                //Recuperation de la liste des noeuds
    CellNoeud *liaisons_reseau = R->noeuds;              //Recuperation de la liste des noeuds pour les voisins (liaisons)
    CellCommodite *commodites_reseau = R->commodites;    //Recuperation de la liste des commodites

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
    while(noeuds_reseau){
        int num = noeuds_reseau->nd->num;
        double x = noeuds_reseau->nd->x;
        double y = noeuds_reseau->nd->y;
        fprintf(f, "v %d %f %f\n", num, x, y);

        noeuds_reseau = noeuds_reseau->suiv;
    }
    fprintf(f, "\n");
    
    // Ecriture des lignes commencant par "l" (liaisons du reseau)
    while(liaisons_reseau){
        Noeud* n = liaisons_reseau->nd;
        CellNoeud* liste_n_vois = n->voisins;

        while (liste_n_vois != NULL) {
            Noeud* n_vois = liste_n_vois->nd;
            if (n->num > n_vois->num) {
                fprintf(f, "l %d %d\n", n_vois->num, n->num);
            }
            liste_n_vois = liste_n_vois->suiv;
        }

        liaisons_reseau = liaisons_reseau->suiv;
    }
    fprintf(f, "\n");
    
    // Ecriture des lignes commencant par "k" (commodites du reseau)
    for (int i = 0; i<nb_commodites; i++) {
        Noeud* a = commodites_reseau->extrA;
        Noeud* b = commodites_reseau->extrB;
        fprintf(f, "k %d %d\n", a->num, b->num);

        commodites_reseau = commodites_reseau->suiv;
    }
    fprintf(f, "\n");
}

//QUESTION 3
/*Affiche HTML Reseau*/
void afficheReseauSVG(Reseau *R, char* nomInstance){
    CellNoeud *courN,*courv;
    SVGwriter svg;
    double maxx=0,maxy=0,minx=1e6,miny=1e6;

    courN=R->noeuds;
    while (courN!=NULL){
        if (maxx<courN->nd->x) maxx=courN->nd->x;
        if (maxy<courN->nd->y) maxy=courN->nd->y;
        if (minx>courN->nd->x) minx=courN->nd->x;
        if (miny>courN->nd->y) miny=courN->nd->y;
        courN=courN->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    courN=R->noeuds;
    while (courN!=NULL){
        SVGpoint(&svg,500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
        courv=courN->nd->voisins;
        while (courv!=NULL){
            if (courv->nd->num<courN->nd->num)
                SVGline(&svg,500*(courv->nd->x-minx)/(maxx-minx),500*(courv->nd->y-miny)/(maxy-miny),500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
            courv=courv->suiv;
        }
        courN=courN->suiv;
    }
    SVGfinalize(&svg);
}


//fonctions de base

/*Renvoie un reseau vide*/
Reseau* creer_reseau(){
    Reseau* reseau = (Reseau*)(malloc(sizeof(Reseau)));
    reseau->nbNoeuds = 0;
    reseau->gamma = 0;
    reseau->noeuds = NULL;
    reseau->commodites = NULL;

    return reseau;
}

/*Renvoie une commodite vide*/
CellCommodite* creer_cellcommodite(){
    CellCommodite* cellc = (CellCommodite*)(malloc(sizeof(CellCommodite)));
    cellc->extrA = NULL; 
    cellc->extrB = NULL;
    cellc->suiv = NULL;
    return cellc;

}

/*Renvoie un CellNoeud vide*/
CellNoeud* creer_cellnoeud(Noeud* noeud){
    CellNoeud* celln = (CellNoeud*)(malloc(sizeof(CellNoeud)));
    celln -> nd = noeud;
    celln->suiv=NULL;
    return celln;
}

/*Renvoie un noeud vide*/
Noeud* creer_noeud(double x, double y, int num){
    Noeud* n = (Noeud*)(malloc(sizeof(Noeud)));
    n->num = num;
    n->x = x;
    n->y = y;
    n->voisins = NULL;
    return n;
}

/*Ajoute voisin aux voisins de n*/
void ajouter_voisin(Noeud* n, Noeud* voisin){
    if (voisin == NULL || n == voisin) return;

    //on récupère la liste de voisin actuelle
    CellNoeud * liste_voisin = n->voisins; 

    //on vérifie si voisin déjà parmis les voisins;
    while(liste_voisin){    //Si dans voisins, la CellNoeud contient le même noeud voisin
        if (liste_voisin->nd == voisin) return;
        liste_voisin = liste_voisin->suiv;
    }

    //sinon on créer CellNoeud et on ajoute le noeud
    CellNoeud* new_voisin = creer_cellnoeud(voisin);

    //in insère le voisin dans la liste des voisins
    new_voisin->suiv = n->voisins;
    n->voisins = new_voisin;
    
    return;
}

/*Renvoie le nombre de commodites dans le reseau*/
int nb_commodite(Reseau* r){
    if (r == NULL) return 0;
    int nb = 0;
    CellCommodite* parcours = r->commodites;
    while (parcours){
        nb ++;
        parcours = parcours->suiv;
    }
    return nb;
}

//Desallocation

/*Libere un reseau*/
void liberer_reseau(Reseau* r){
    liberer_commodite(r->commodites);
    liberer_cellnoeud(r->noeuds);
    free(r);
}

/*Libere un CellNoeud*/
void liberer_cellnoeud(CellNoeud * c){
    //on libere les noeuds et les cellnoeuds du reseau
    while(c){
        CellNoeud * next = c->suiv;
        liberer_Noeud(c->nd);
        free(c);
        c = next;
    }
}

/*Libere une commodite*/
void liberer_commodite(CellCommodite* c){
    //on libere toutes les commodites sans liberer les noeuds
    while(c){
        CellCommodite* next = c->suiv;
        free(c);
        c = next;
    }
}

/*Libere un noeud*/
void liberer_Noeud(Noeud* n){
    liberer_voisins(n);
    free(n);
}

/*Libere les voisins d'un noeud*/
void liberer_voisins(Noeud* n){
    //on libere tout les cellnoeuds utilisé pour les voisins
    //sans liberer les noeuds
    CellNoeud* vois = n->voisins, *suiv;
    while(vois){
        suiv = vois->suiv;
        free(vois);
        vois = suiv;
    }
}