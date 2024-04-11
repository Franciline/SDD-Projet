#include "graphe.h"
#include "Reseau.h"
#include <stdlib.h>
#include <stdio.h>
#include "File.h"

//Question 1

/*Cree un graphe a partir d'un reseau*/
Graphe* creerGraphe(Reseau* r){
    if (r == NULL) return NULL;
    Graphe* graphe = initGrapheVide(r->nbNoeuds,r->gamma,nb_commodite(r));
    
    //on cree les commodites
    CellCommodite* parcours = r->commodites;
    int nb_tab = 0;     //indice dans le tableau de commodites

    while(parcours){
        Commod * commod = creerCommod(parcours->extrA->num,parcours->extrB->num);

        //ajout au tableau de commodites
        graphe->T_commod[nb_tab] = *commod;     //on ajoute la structure et non pointeur
        nb_tab++;

        //suivant
        parcours = parcours->suiv;
    }

    //on cree les sommets en parcourant la liste des noeuds
    CellNoeud *noeuds = r->noeuds;
    while (noeuds){     //parcours des noeuds
        Sommet* sommet = creerSommet(noeuds->nd->num,noeuds->nd->x, noeuds->nd->y);
        graphe->T_som[sommet->num] = sommet; //on le sauvegarde dans le tableau, -1 car les sommets commencent à 1
        noeuds = noeuds->suiv;
    }

    noeuds = r->noeuds; 
    while(noeuds){ //On parcourt les noeuds et leurs voisins pour creer les aretes
        CellNoeud* voisin = noeuds->nd->voisins;
        while(voisin){  //on parcours les voisins
            if (noeuds->nd->num < voisin->nd->num){ //pour n'ajouter qu'une fois une arete
                Arete * arete = creerArete(noeuds->nd->num, voisin->nd->num);

                //on creer deux structures pour les mettre dans sommet
                Cellule_arete * cella1 = creerCellule_arete(arete);
                Cellule_arete * cella2 = creerCellule_arete(arete);
                
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

/*Retourne le plus petit nombre d'aretes entre deux sommets*/
int plus_petit_nb_aretes(Graphe* g, Sommet* u, Sommet* v){

    //le tableau va contenir -1 si le sommet n'a pas ete visite, sinon la distance minimum par rapport au noeud de depart
    int * tableau = malloc(sizeof(int)*(g->nbsom+1)); //comme les sommets commencent à 1, on rajoute nbsomme + 1 pour le tableau
    
    File * file = creer_file();
    for (int i = 0; i < g->nbsom+1; i++){
        tableau[i] = -1; 
    }

    tableau[u->num] = 0; //distance entre u et lui meme
    int num_voisin = -1; //stock le numero de l'extremite de l'arete 

    //on ajoute dans la file le sommet u
    enfiler(file, u);

    //on ajoute les voisins de u dans la file
    Cellule_arete* voisins_u = u->L_voisin;

    while(voisins_u){ 
        //on cherche le sommet correspondant dans l'arete a
        if (voisins_u->a->u == u->num)
            enfiler(file, g->T_som[voisins_u->a->v]);
        else enfiler(file, g->T_som[voisins_u->a->u]);

        voisins_u = voisins_u->suiv;
    }

    while(!est_vide(file)){ //Tant que la file n'est pas vide

        Sommet* actuel = defiler(file) ; //parcours en largeur
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
                tableau[num_voisin] = tableau[actuel_num] + 1; //il a alors ete visite, la distance est incrementee
                enfiler(file, g->T_som[num_voisin]); //on ajoute ce sommet a la file
            } 
            else{
                if (tableau[num_voisin] > tableau[actuel_num] + 1) //si il existait un chemin plus court
                    tableau[num_voisin] = tableau[actuel_num] + 1;
            }

            //on verifie si c'est le sommet v
            if (num_voisin == v->num){ return tableau[num_voisin];}
            voisins = voisins->suiv;
        }
    }
    return -1;
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

    Commod* liste_commodites = g->T_commod;
    Sommet** liste_sommets = g->T_som;

    // Calcul de la plus courte chaine pour chaque commodite
    while(liste_commodites != NULL) {
        int u = liste_commodites->e1;
        int v = liste_commodites->e2;
        int plus_courte_chaine = plus_petit_nb_aretes(g, liste_sommets[u], liste_sommets[v]);

        matrice[u][v] = plus_courte_chaine;

        liste_commodites++;
    }

    // Verification que le nombre de chaines qui passe par chaque arete du graphe est inferieur a gamma
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            if (matrice[i][j] > g->gamma) {
                return 0;
            }
        }
    }
    return -1;
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
        graphe->T_som[i] = (Sommet*) malloc(sizeof(Sommet));
        graphe->T_som[i] = NULL;
    }
    graphe->T_commod = (Commod*) malloc(sizeof(Commod)*nbcommod);

    return graphe;
}

/*Cree une commodite et l'initialise*/
Commod* creerCommod(int e1, int e2){
    Commod * commod = (Commod*)malloc(sizeof(Commod));
    commod->e1 = e1;
    commod->e2 = e2;
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
void libererGraphe(Graphe* graphe){
    //unknown
}

//Libere une commodite
void libererCommod(Commod* commod){
    free(commod);
}

/*Libere un sommet*/
void libererSommet(Sommet* sommet){
    //on libere les voisins CA sans liberer les aretes
    //Comment faire pour libere qu'une fois les aretes?
    //verifier si existe et si non, oui, alors supprimer
}

/*Libere une cellule_arete*/
void libererCellule_arete(Cellule_arete* ca){
    libererArete(ca->a);
    free(ca);    
}

/*Libere une arete*/
void libererArete(Arete* a){
    free(a);
}
