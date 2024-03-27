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

    insererNoeudArbre(n, &nul, a);
    printf("bien insérer SO %d %d %d %d\n", a->so != NULL,  a->se != NULL,  a->no != NULL,  a->ne != NULL);
    printf("coté %lf %lf \n", a->coteX,  a->coteY);
    ArbreQuat* fils = a->se;
    printf("coté 2  %lf %lf \n", fils->xc, fils->yc);

    insererNoeudArbre(n2, &fils, a);
    printf("bien insérer SO %d %d %d %d\n", fils->so != NULL,  fils->se != NULL,  fils->no != NULL,  fils->ne != NULL);
    printf("coordonnée %lf %lf et %lf %lf\n", fils->so->noeud->x, fils->so->noeud->y, fils->se->xc, fils->se->yc);

    Noeud * neoud = rechercheCreeNoeudArbre(r, &a, NULL, 7, 1);
    printf("pas nul noeud %d, nb de noeud réseau %d \n", neoud != NULL, r->nbNoeuds);

    Noeud * neoud2 = rechercheCreeNoeudArbre(r, &a, NULL, 1, 1);
    printf("pas nul noeud %d, nb de noeud réseau %d \n", neoud2 != NULL, r->nbNoeuds);
    printf("bien insérer SO %d %d %d %d\n", a->so != NULL,  a->se != NULL,  a->no != NULL,  a->ne != NULL);
    printf("nb de noeud réseau %d \n",r->nbNoeuds);
    
}