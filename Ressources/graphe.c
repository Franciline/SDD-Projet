#include <stdlib.h>
#include <stdio.h>

#include "graphe.h"
#include "Reseau.h"
#include "File.h"


//Exercice 7

//Question 1

/* Fonction qui cree un graphe a partir d'un reseau */
Graphe* creerGraphe(Reseau* r) {
    if (r == NULL) return NULL;

    Graphe* graphe = initGrapheVide(r->nbNoeuds, r->gamma, nb_commodite(r));
    
    //On cree les commodites du graphe
    CellCommodite* parcours = r->commodites;
    int nb_tab = 0;     //indice dans le tableau de commodites

    while(parcours) {
        Commod commod = creerCommod(parcours->extrA->num, parcours->extrB->num);
        //Ajout au tableau de commodites
        graphe->T_commod[nb_tab] = commod; 
        nb_tab++;

        parcours = parcours->suiv;
    }

    //On cree les sommets du graphe
    CellNoeud* noeuds = r->noeuds;

    //Parcours des noeuds
    while(noeuds) {     
        Sommet* sommet = creerSommet(noeuds->nd->num, noeuds->nd->x, noeuds->nd->y);
        graphe->T_som[sommet->num - 1] = sommet;      //On le sauvegarde dans le tableau
        noeuds = noeuds->suiv;
    }

    noeuds = r->noeuds; 
    
    //On parcourt les noeuds et leurs voisins pour creer les aretes
    while(noeuds) { 
        CellNoeud* voisin = noeuds->nd->voisins;
        //on parcourt les voisins
        while(voisin) {  
            if (noeuds->nd->num < voisin->nd->num) { //Pour n'ajouter qu'une fois l'arete, on met une condition
                Arete* arete = creerArete(noeuds->nd->num, voisin->nd->num);

                //On insere l'arete pour les deux sommets
                ajouteArete(graphe->T_som[arete->u-1], arete);
                ajouteArete(graphe->T_som[arete->v-1], arete);
            }
            voisin = voisin->suiv;
        }
        noeuds = noeuds->suiv;
    }

  return graphe;
}

//Question 2

/* Fonction qui retourne le plus petit nombre d'aretes entre deux sommets u et v avec un parcours en largeur */
int plus_petit_nb_aretes(Graphe* g, Sommet* u, Sommet* v) {

    //Tableau de distance initialise a -1
    int tableauD[g->nbsom]; 
    
    File* file = creer_file();

    for (int i=0; i<g->nbsom; i++) {
        tableauD[i] = -1; 
    }

    tableauD[u->num - 1] = 0;       //Distance entre u et lui-meme mis a 0
    int num_voisin, actuel_num;     //Stockage du numero de l'extremite de l'arete 

    //On ajoute dans la file le sommet u
    enfiler(file, u);

    Sommet* actuel;
    
    while(!est_vide(file)) {        //Tant que la file n'est pas vide

        actuel = defiler(file);     //parcours en largeur
        actuel_num = actuel->num;   //le numero du sommet actuel

        //On parcourt les voisins du sommet actuel
        Cellule_arete* voisins = actuel->L_voisin;

        //On parcourt les sommets voisins
        while(voisins) {
            //On recupere le numero du voisin qui est soit u, soit v de l'arete a
            if (voisins->a->u == actuel_num)
                num_voisin = voisins->a->v;
            else num_voisin = voisins->a->u;
            
            //On verifie que le sommet n'a pas ete visite
            if (tableauD[num_voisin - 1] == -1) {
                tableauD[num_voisin - 1] = tableauD[actuel_num - 1] + 1;    //On le visite et on stock la distance 
                enfiler(file, g->T_som[num_voisin - 1]);                    //On ajoute ce sommet a la file 
            } 
            else {
                //Cas : il existe un chemin plus court
                if (tableauD[num_voisin - 1] > tableauD[actuel_num - 1] + 1) 
                    tableauD[num_voisin - 1] = tableauD[actuel_num - 1] + 1;
            }

            voisins = voisins->suiv;
        }
    }
    liberer_file(file);

    return tableauD[v->num - 1];
}

//Question 3

/* Fonction qui retourne la plus petite chaine entre deux sommets u et v */
int* plus_petit_nb_aretes_liste(Graphe* g, Sommet* u, Sommet* v) {
    File* file = creer_file();

    int tableauD[g->nbsom];     //Tableau de distance
    int tableauP[g->nbsom];     //Tableau de peres

    for (int i=0; i<g->nbsom; i++) {
        tableauD[i] = -1; 
        tableauP[i] = 0;
    }

    tableauD[u->num-1] = 0;         //Distance entre u et lui-meme mis a 0
    tableauP[u->num-1] = -1;        //u est racine et n'a pas de pere
    int num_voisin, num_actuel ;    //Stock le numero de l'extremite de l'arete 

    //On ajoute dans la file le sommet u
    enfiler(file, u);

    Sommet* actuel;
    
    while(!est_vide(file)) {        //Tant que la file n'est pas vide
        actuel = defiler(file);     //Parcours en largeur
        num_actuel = actuel->num;   //Le numero du sommet actuel

        //On parcourt les voisins du sommet actuel
        Cellule_arete* voisins = actuel->L_voisin;

        //On parcourt les sommets voisins
        while(voisins) {

            //On recupere le numero du voisin qui est soit u, soit v de l'arete a
            if (voisins->a->u == num_actuel)
                num_voisin = voisins->a->v;
            else num_voisin = voisins->a->u;

            //On verifie que le sommet n'a pas ete visite
            if (tableauD[num_voisin - 1] == -1){
                tableauD[num_voisin - 1] = tableauD[num_actuel - 1] + 1;    //On le visite et on store la distance 
                tableauP[num_voisin - 1] = num_actuel ;                     //On recupere le pere
                enfiler(file, g->T_som[num_voisin - 1]);                    //On ajoute ce sommet a la file 
            } 
            else {
                //Cas : il existe un chemin plus court, on remplace
                if (tableauD[num_voisin - 1] > tableauD[num_actuel - 1] + 1) {
                    tableauD[num_voisin - 1] = tableauD[num_actuel - 1] + 1;
                    tableauP[num_voisin - 1] = num_actuel;
                }
            }
            voisins = voisins->suiv;
        }
    }
    liberer_file(file);

    //On cree la chaine d'entiers
    int* liste_chaine = (int *) calloc(g->nbsom, sizeof(int));

    //Extremites de la chaine
    liste_chaine[0] = u->num;
    liste_chaine[tableauD[v->num - 1]] = v->num;

    //On remonte la chaine de peres
    int pere = tableauP[v->num - 1];
    while(pere != -1) {
        liste_chaine[tableauD[pere-1]] = pere;
        pere = tableauP[pere-1];
    }
    
    return liste_chaine;
}

// Question 4

/* Fonction qui renvoie 1 (vrai) si le nombre de chaines qui passe par chaque arete est inferieur a gamma, 0 (faux) sinon */
int reorganiseReseau(Reseau* r) {
    Graphe* g = creerGraphe(r);
    int n = g->nbsom;

    //Creation de la matrice et initialisation a 0
    int** matrice = (int **) malloc(sizeof(int *)*n);
    for (int i=0; i<n; i++) {
        matrice[i] = (int *) malloc(sizeof(int)*n);
        for (int j=0; j<n; j++) {
            matrice[i][j] = 0;
        }
    }

    //On parcourt toutes les commodites
    Sommet** liste_sommets = g->T_som;

    for (int i=0; i<g->nbcommod; i++){
        int u = g->T_commod[i].e1;
        int v = g->T_commod[i].e2;

        //La chaine minimale entre les deux extremites
        int* chaine = plus_petit_nb_aretes_liste(g, liste_sommets[u-1], liste_sommets[v-1]);

        //On parcourt cette chaine et on incremente la matrice
        for (int j = 0; j < g->nbsom-1; j++){
            if (chaine[j+1] != 0){
                int u = chaine[j], v = chaine[j+1];
                if (u < v) 
                    matrice[u-1][v-1]++; 
                else                         
                    matrice[v-1][u-1]++;
            }
            else break;
        }

        free(chaine);
    }

    //Verification que tab[i][j] <= gamma
    for (int i=0; i<n; i++) {
        for (int j=i; j<n; j++) {
            if (matrice[i][j] > g->gamma) {

                //Desallocation
                liberer_Graphe(g);
                for (int i=0; i<n; i++) free(matrice[i]);
                free(matrice);

                return 0;
            }
        }
    }

    //Desallocation
    liberer_Graphe(g);
    for (int i=0; i<n; i++) free(matrice[i]);
    free(matrice);

    return 1;
}

//Fonctions implementees par nous-meme

/* Fonction qui cree un graphe et l'initialise */
Graphe* initGrapheVide(int nbsom, int gamma, int nbcommod) {
    Graphe* graphe = (Graphe *) malloc(sizeof(Graphe)); 

    graphe->nbsom = nbsom;
    graphe->gamma = gamma;
    graphe->nbcommod = nbcommod;

    graphe->T_som = (Sommet **) malloc(sizeof(Sommet*)*nbsom);

    for (int i=0; i<graphe->nbsom; i++) {
        graphe->T_som[i] = NULL;
    }
    graphe->T_commod = (Commod *) malloc(sizeof(Commod)*nbcommod);

    return graphe;
}

/* Fonction qui renvoie une commodite et l'initialise */
Commod creerCommod(int e1, int e2) {
    Commod commod;
    commod.e1 = e1;
    commod.e2 = e2;

    return commod;
}

/* Fonction qui cree un sommet et l'initialise aux valeurs */
Sommet* creerSommet(int num, double x, double y) {
    Sommet* sommet = (Sommet *) malloc(sizeof(Sommet));
    sommet->num = num;
    sommet->x = x;
    sommet->y = y;
    sommet->L_voisin = NULL;

    return sommet;
}

/* Fonction qui cree une arete d'extremite u et v */
Arete* creerArete(int u, int v) {
    Arete* arete = (Arete *) malloc(sizeof(Arete));
    arete->u = u;
    arete->v = v;

    return arete;
}

/*Cree une Cellule_arete d'arete a*/
Cellule_arete* creerCellule_arete(Arete* a) {
    Cellule_arete* ca = (Cellule_arete *) malloc(sizeof(Cellule_arete));
    ca->a = a;
    ca->suiv = NULL;

    return ca;
}

/* Fonction qui ajoute une arete a aux voisins de u */
void ajouteArete(Sommet* u, Arete* a) {
    //On cree une cellule pour l'arete
    Cellule_arete* cella = creerCellule_arete(a);

    //On l'ajoute aux aretes de u
    cella->suiv = u->L_voisin;
    u->L_voisin = cella;

    return;
}


//Fonctions de desallocation

/* Fonction qui libere un Graphe */
void liberer_Graphe(Graphe* graphe) {
    //Libere les commodites
    free(graphe->T_commod);

    //libere tableau de sommets
    
    for (int i=0; i<graphe->nbsom; i++) {
        liberer_Sommet(graphe, graphe->T_som[i]);
        graphe->T_som[i] = NULL;
    }
    free(graphe->T_som);
    
    free(graphe);

    return;
}

/* Fonction qui libere un sommet et ses aretes voisins */
void liberer_Sommet(Graphe* graphe, Sommet* sommet){
    if (sommet == NULL) return;

    Cellule_arete* voisins = sommet->L_voisin, *vois_suiv;

    while(voisins) {

        //On libere l'arete
        if (voisins->a != NULL) {

            //On recherche l'autre Cellule arete dans les voisins de l'autre sommet 
            Sommet* extremite;
            if (sommet->num == voisins->a->u) extremite = graphe->T_som[voisins->a->v - 1];
            else extremite = graphe->T_som[voisins->a->u - 1];

            Cellule_arete* parcours = extremite->L_voisin;
            while(parcours->a != voisins->a) parcours = parcours->suiv;
            free(voisins->a);
            voisins->a = NULL;
            parcours->a = NULL;
        }

        vois_suiv = voisins->suiv;

        //On libere la Cellule arete 
        free(voisins);
        voisins = vois_suiv;
    }
    free(sommet);

    return;
}
