#include "graphe.h"
#include "Reseau.h"
#include <stdlib.h>
#include <stdio.h>
#include "File.h"
#include "assert.h"

//Question 1

/*Cree un graphe a partir d'un reseau*/
Graphe* creerGraphe(Reseau* r){
    if (r == NULL) return NULL;

    Graphe* graphe = initGrapheVide(r->nbNoeuds,r->gamma,nb_commodite(r));
    
    //On cree les commodites du graphe
    CellCommodite* parcours = r->commodites;
    int nb_tab = 0;     //indice dans le tableau de commodites

    while(parcours){
        Commod commod = creerCommod(parcours->extrA->num,parcours->extrB->num);
        //ajout au tableau de commodites
        graphe->T_commod[nb_tab] = commod; 
        nb_tab++;

        parcours = parcours->suiv;
    }

    //On cree les sommets du graphe
    CellNoeud *noeuds = r->noeuds;

    //parcours des noeuds
    while (noeuds){     
        Sommet* sommet = creerSommet(noeuds->nd->num,noeuds->nd->x, noeuds->nd->y);
        graphe->T_som[sommet->num] = sommet; //on le sauvegarde dans le tableau, l'indice commence à 1 
        noeuds = noeuds->suiv;
    }

    noeuds = r->noeuds; 
    
    //On parcourt les noeuds et leurs voisins pour creer les aretes
    while(noeuds){ 
        CellNoeud* voisin = noeuds->nd->voisins;
        //on parcours les voisins
        while(voisin){  
            if (noeuds->nd->num < voisin->nd->num){ //pour n'ajouter qu'une fois l'arete
                Arete * arete = creerArete(noeuds->nd->num, voisin->nd->num);

                //on creer deux Cellule_arete pour les deux sommets
                Cellule_arete * cella1 = creerCellule_arete(arete);
                Cellule_arete * cella2 = creerCellule_arete(arete);
                assert(cella2->a == cella1->a);
                
                //on insere l'arete dans les voisins des sommets concernes
                cella1->suiv = graphe->T_som[arete->u]->L_voisin; 
                graphe->T_som[arete->u]->L_voisin = cella1;

                cella2->suiv = graphe->T_som[arete->v]->L_voisin; 
                graphe->T_som[arete->v]->L_voisin = cella2;
            }
            voisin = voisin->suiv;
        }
        noeuds = noeuds->suiv;
    }
  return graphe;
}

//Question 2

/*Retourne le plus petit nombre d'aretes entre deux sommets avec un parcours en largeur*/
int plus_petit_nb_aretes(Graphe* g, Sommet* u, Sommet* v){

    //le tableau va contenir -1 si le sommet n'a pas ete visite, sinon la distance minimum par rapport au noeud de depart
    int tableau[g->nbsom+1]; //comme les sommets commencent à 1, on rajoute nbsomme + 1 pour le tableau
    
    File * file = creer_file();

    for (int i = 0; i < g->nbsom+1; i++){
        tableau[i] = -1; 
    }

    tableau[u->num] = 0; //distance entre u et lui meme mis a 0
    int num_voisin; //stock le numero de l'extremite de l'arete 

    //on ajoute dans la file le sommet u
    enfiler(file, u);

    //on ajoute les voisins de u dans la file
    Cellule_arete* voisins_u = u->L_voisin;

    while(voisins_u){ 
        //on cherche le sommet voisin du noeud u puis on l'enfile
        if (voisins_u->a->u == u->num)
            enfiler(file, g->T_som[voisins_u->a->v]);
        else enfiler(file, g->T_som[voisins_u->a->u]);

        voisins_u = voisins_u->suiv;
    }

    Sommet* actuel;
    
    while(!est_vide(file)){ //Tant que la file n'est pas vide

        actuel = defiler(file) ; //parcours en largeur
        int actuel_num = actuel->num; //le numero du sommet actuel

        //on parcourt les voisins du sommet actuel
        Cellule_arete* voisins = actuel->L_voisin;

        //on parcours les sommets voisins
        while(voisins){
            //on recupere le numero du voisin qui est soit u, soit v de l'arete a
            if (voisins->a->u == actuel_num)
                num_voisin = voisins->a->v;
            else num_voisin = voisins->a->u;
            
            //on verifie que le sommet n'a pas ete visite
            if (tableau[num_voisin] == -1){
                tableau[num_voisin] = tableau[actuel_num] + 1; //on le visite et on store la distance 
                enfiler(file, g->T_som[num_voisin]); //on ajoute ce sommet a la file
            } 
            else{
                if (tableau[num_voisin] > tableau[actuel_num] + 1) //si il existait un chemin plus court
                    tableau[num_voisin] = tableau[actuel_num] + 1;
            }

            //on verifie si c'est le sommet v
            if (num_voisin == v->num) {
                liberer_file(file);
                return tableau[num_voisin];
            }
            voisins = voisins->suiv;
        }
    }
    
    liberer_file(file);
    return -1;
}

//Question 3

/*Retourne la plus petite chaine entre deux sommets*/
int* plus_petit_nb_aretes_liste(Graphe* g, Sommet* u, Sommet* v){

    File * file = creer_file();

    //le tableau va contenir -1 si le sommet n'a pas ete visite, sinon la distance minimum par rapport au noeud de depart
    int* liste_chaine = (int*)calloc(g->nbsom, sizeof(int));

    int tableau[g->nbsom+1]; //comme les sommets commencent à 1, on rajoute nbsomme + 1 pour le tableau

    for (int i = 0; i < g->nbsom+1; i++){
        tableau[i] = -1; 
    }

    tableau[u->num] = 0; //distance entre u et lui meme mis a 0
    int num_voisin, actuel_num ; //stock le numero de l'extremite de l'arete 

    //on ajoute dans la file le sommet u
    enfiler(file, u);

    Sommet* actuel;
    liste_chaine[0] = u->num;
    
    while(!est_vide(file)){ //Tant que la file n'est pas vide
        actuel = defiler(file) ; //parcours en largeur
        actuel_num = actuel->num; //le numero du sommet actuel

        //on update le tableau de int, a telle distance il y aura tel sommet
        liste_chaine[tableau[actuel_num]] = actuel_num;

        //on parcourt les voisins du sommet actuel
        Cellule_arete* voisins = actuel->L_voisin;

        //on parcours les sommets voisins
        while(voisins){
            //on recupere le numero du voisin qui est soit u, soit v de l'arete a
            if (voisins->a->u == actuel_num)
                num_voisin = voisins->a->v;
            else num_voisin = voisins->a->u;

            //on verifie que le sommet n'a pas ete visite
            if (tableau[num_voisin] == -1){
                tableau[num_voisin] = tableau[actuel_num] + 1; //on le visite et on store la distance 
                enfiler(file, g->T_som[num_voisin]); //on ajoute ce sommet a la file
            } 
            else{
                if (tableau[num_voisin] > tableau[actuel_num] + 1) //si il existait un chemin plus court
                    tableau[num_voisin] = tableau[actuel_num] + 1;
            }

            //on verifie si c'est le sommet v
            if (num_voisin == v->num){
                liste_chaine[tableau[num_voisin]] = num_voisin;
                break;
            }
            voisins = voisins->suiv;
            
        }
        if (num_voisin == v->num) break;
    }

    liberer_file(file);
    return liste_chaine;
}

// Question 4

/* Fonction qui renvoie 1 (vrai) si le nombre de chaines qui passe par chaque arete est inferieur a gamma, 0 (faux) sinon*/
int reorganiseReseau(Reseau* r) {
    Graphe* g = creerGraphe(r);
    int n = g->nbsom;

    // Creation de la matrice
    int** matrice = (int**) malloc(sizeof(int*) * n);
    for (int i = 0; i<n; i++) {
        matrice[i] = (int*) malloc(sizeof(int) * n);
        for (int j = 0; j<n; j++) {
            matrice[i][j] = 0;
        }
    }

    Sommet** liste_sommets = g->T_som;

    for (int i = 0; i < g->nbcommod; i++){
        int u = g->T_commod[i].e1;
        int v = g->T_commod[i].e2;
        //la chaine
        int* chaine = plus_petit_nb_aretes_liste(g, liste_sommets[u], liste_sommets[v]);
        for (int i = 0; i < g->nbsom - 1; i++){
            if (chaine[i+1] != 0) {
                //pour matrice triangulaire superieur
                if (chaine[i] < chaine[i+1]) matrice[chaine[i] - 1][chaine[i+1] - 1]++; 
                else matrice[chaine[i+1] - 1][chaine[i] - 1]++;
            }
        }
    }

    // Verification que le nombre de chaines qui passe par chaque arete du graphe est inferieur a gamma
    for (int i = 0; i<n; i++) {
        for (int j = i; j<n; j++) {
            if (matrice[i][j] > g->gamma) {
                return 0;
            }
        }
    }

    //desallocation
    liberer_Graphe(g);
    for (int i = 0; i < n; i++){
        free(matrice[i]);
    }
    free(matrice);

    return 1;
}

//fonctions implementees par nous meme

/*Cree un graphe et l'initialise*/
Graphe* initGrapheVide(int nbsom, int gamma, int nbcommod){
    Graphe * graphe = (Graphe*) malloc(sizeof(Graphe)); 

    graphe->nbsom = nbsom;
    graphe->gamma = gamma;
    graphe->nbcommod = nbcommod;

    graphe->T_som = (Sommet**)malloc(sizeof(Sommet*)*(nbsom + 1));

    for (int i = 0; i < graphe->nbsom + 1; i++){
        graphe->T_som[i] = NULL;
    }
    graphe->T_commod = (Commod*)malloc(sizeof(Commod)*nbcommod);

    return graphe;
}

/*Renvoie une commodite (structure) et l'initialise*/
Commod creerCommod(int e1, int e2){
    Commod commod;
    commod.e1 = e1;
    commod.e2 = e2;
    return commod;
}

/*Cree un sommet et l'initialise aux valeurs*/
Sommet* creerSommet(int num, double x, double y){
    Sommet* sommet = (Sommet*)malloc(sizeof(Sommet));
    sommet->num = num;
    sommet->x = x;
    sommet->y = y;
    sommet->L_voisin = NULL; //recherche de comm
    return sommet;
}

/*Cree une arete d'extremite u et v*/
Arete* creerArete(int u, int v){
    Arete * arete = (Arete*)malloc(sizeof(Arete));
    arete->u = u;
    arete->v = v;
    return arete;
}

/*Cree une Cellule_arete d'arete a*/
Cellule_arete* creerCellule_arete(Arete * a){
    Cellule_arete * ca = (Cellule_arete*)malloc(sizeof(Cellule_arete));
    ca->a = a;
    ca->suiv = NULL;
    return ca;
}


//Desallocation

/*Libere le graphe*/
void liberer_Graphe(Graphe* graphe){
    //Libere les commodites
    free(graphe->T_commod);

    //libere tableau de sommets
    
    for (int i = 0; i < graphe->nbsom + 1; i++) {liberer_Sommet(graphe, graphe->T_som[i]); graphe->T_som[i] = NULL;}
    free(graphe->T_som);
    
    free(graphe);
}

/*Libere un sommet et ses aretes voisins*/
void liberer_Sommet(Graphe* graphe, Sommet* sommet){
    if (sommet == NULL) return;

    Cellule_arete* voisins = sommet->L_voisin, *vois_suiv;

    while(voisins){

        //on libere l'arete
        if (voisins->a != NULL) {

            //on recherche l'autre Cellule arete dans les voisins de l'autre sommet 
            Sommet* extremite;
            if (sommet->num == voisins->a->u) extremite = graphe->T_som[voisins->a->v];
            else extremite = graphe->T_som[voisins->a->u];

            Cellule_arete* parcours = extremite->L_voisin;
            while(parcours->a!=voisins->a) parcours = parcours->suiv;
            free(voisins->a);
            voisins->a = NULL;
            parcours->a = NULL;
        }

        vois_suiv = voisins->suiv;

        //on liberere la Cellule arete 
        assert(voisins->a == NULL);
        free(voisins);
        voisins = vois_suiv;
    }
    free(sommet);
}
