#include <stdio.h>
#include <stdlib.h>

#include "Chaine.h"
#include "Reseau.h"
#include "ArbreQuat.h"

int main(){
    ArbreQuat * a = creerArbreQuat(5, 5, 10, 10), *nul = NULL;
    Noeud * n = creer_noeud();
    Reseau* r = creer_reseau();
    n->x = 8;
    n->y = 2;

    Noeud * n2 = creer_noeud();
    n2->x = 7;
    n2->y = 1;


    //insertion de (8,2) par rapport a (5,5), donc SE
    insererNoeudArbre(n, &nul, a);
    printf("bien insérer SE %d %d %d %d\n", a->so != NULL,  a->se != NULL,  a->no != NULL,  a->ne != NULL);
    printf("coté de a %lf %lf, cote de son nul SE %lf %lf \n", a->coteX,  a->coteY, nul->coteX,  nul->coteY);
    printf("coordonnees du fils SE  %lf %lf \n", nul->xc, nul->yc);

    //insertion dans une feuille: on insert (7,1) et (8,2) par rapport a ((7.5, 7.5))
    insererNoeudArbre(n2, &nul, a);
    printf("2 insertions dans la feuille niveau SE et SO %d %d %d %d\n", nul->so != NULL,  nul->se != NULL,  nul->no != NULL,  nul->ne != NULL);
    printf("coordonnée de l'arbre cree SO noeud: x = %lf y = %lf et SE noeud x=  %lf y=  %lf\n", nul->so->noeud->x, nul->so->noeud->y, nul->se->noeud->x, nul->se->noeud->y);

    Noeud * noeud = rechercheCreeNoeudArbre(r, &a, NULL, 7, 1);
    printf("comme noeud existant %d, nb de noeud réseau vaut 0 : %d \n", noeud != NULL, r->nbNoeuds);

    Noeud * neoud2 = rechercheCreeNoeudArbre(r, &a, NULL, 1, 9);
    printf("noeud inexistant mais cree %d, nb de noeud réseau vaut 1:  %d \n", neoud2 != NULL, r->nbNoeuds);
    //le noeud (1,9) a ete inserer en NO
    printf("bien insérer NO et SE du debut %d %d %d %d\n", a->so != NULL,  a->se != NULL,  a->no != NULL,  a->ne != NULL);
    
}