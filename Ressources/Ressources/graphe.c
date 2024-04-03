#include "graphe.h"
#include <stdlib.h>
#include <stdio.h>


/*Cree un graphe a partir d'un reseau*/
Graphe* creerGraphe(Reseau* r){

    Graphe* graphe = initGrapheVide(r->nbNoeuds,r->gamma,nb_commodite(r));

    //on cree les commodites
    CellCommodite* parcours = r->commodites;
    int nb_tab = 0;     //indice dans le tableau de commodites

    while(parcours){
        Commod * commod = creerCommod(parcours->extrA->num,parcours->extrB->num);

        //ajout au tableau de commodites
        graphe->T_commod[nb_tab] = *commod;     //on ajoute la structure et non pointeur
        nb_tab++;
    }

    //on cree les sommets en parcourant la liste des noeuds
    CellNoeud *noeuds = r->noeuds;
    while (noeuds){     //parcours des noeuds
        Sommet* sommet = creerSommet(noeuds->nd->num,noeuds->nd->x, noeuds->nd->y);
        graphe->T_som[sommet->num] = sommet; //on le sauvegarde dans le tableau
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

//fonctions implementees par nous meme

/*Cree un graphe et l'initialise*/
Graphe* initGrapheVide(int nbsom, int gamma, int nbcommod){
    Graphe * graphe = (Graphe*) malloc(sizeof(Graphe)); 

    graphe->nbsom = nbsom;
    graphe->gamma = gamma;
    graphe->nbcommod = nbcommod;

    graphe->T_som = (Sommet**)malloc(sizeof(Sommet*)*nbsom);

    for (int i = 0; i < graphe->nbsom; i++){
        graphe->T_som[i] = (Sommet*) malloc(sizeof(Sommet));
        graphe->T_som[i] = NULL;
    }
    graphe->T_commod = (Commod*) malloc(sizeof(graphe->T_commod)*nbcommod);

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