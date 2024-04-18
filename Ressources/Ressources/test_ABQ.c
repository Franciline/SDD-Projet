#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Chaine.h"
#include "Reseau.h"
#include "ArbreQuat.h"

/*Test de la structure ArbreQuat*/
int main(){
    
    //creation de l'arbre quaternaire, d'un noeud et d'un reseau
    ArbreQuat *a = creerArbreQuat(5, 5, 10, 10), *nul = NULL;
    assert(a->coteX== 10);
    assert(a->coteY == 10);
    
    Reseau *r = creer_reseau();
    Noeud *n1 = creer_noeud(8, 2, 0);
    Noeud *n2 = creer_noeud(7, 1, 1);
    Noeud *n3 = creer_noeud(6, 4, 2);

    //les coordonnees sont choisi par rapport à l'axe des abscisses et des ordonnees usuelles

    //cas un arbre vide: insertion de (8,2) par rapport a (5,5), donc au SE
    insererNoeudArbre(n1, &nul, a);
    assert(a->so == NULL); assert(a->se != NULL); assert(a->no == NULL); assert(a->ne == NULL);
    assert(nul->noeud->x == 8);
    assert(nul->noeud->y == 2);
    assert(nul->xc == 7.5);
    assert(nul->yc == 2.5);

    ArbreQuat *fils_se = nul;

    //cas feuille: insertion de (7,1) et (8,2) par rapport a fils_se (7.5, 2.5) donc SO et SE
    insererNoeudArbre(n2, &fils_se, a);
    assert(fils_se->so != NULL); assert(fils_se->se != NULL); assert(fils_se->no == NULL); assert(fils_se->ne == NULL);
    assert(nul->so->noeud->x == 7);
    assert(nul->so->noeud->y == 1);
    assert(nul->se->noeud->x == 8);
    assert(nul->se->noeud->y == 2);

    //cas noeud interne: insertion de (6,2) dans fils_se, donc au NO
    insererNoeudArbre(n3, &fils_se, a);
    assert(fils_se->so != NULL); assert(fils_se->se != NULL); assert(fils_se->no != NULL); assert(fils_se->ne == NULL);
    assert(nul->no->noeud->x == 6);
    assert(nul->no->noeud->y == 4);
    
    //recherche du noeud n2 existant, le nombre de noeuds dans le reseau n'est donc pas incremente
    Noeud * noeud = rechercheCreeNoeudArbre(r, &a, NULL, 7, 1);
    assert(noeud != NULL); assert(r->nbNoeuds == 0); 

    //recherche d'un neoud inexistant, creation du noeud et le nombre de noeuds dans le reseau est incremente
    Noeud * noeud2 = rechercheCreeNoeudArbre(r, &a, NULL, 1, 9);
    assert(noeud2 != NULL); assert(r->nbNoeuds == 1);
    
    //le noeud (1,9) est insere au NO de l'arbre a
    assert(a->so == NULL); assert(a->se != NULL); assert(a->no != NULL); assert(a->ne == NULL);
    
    liberer_Noeud(n1); liberer_Noeud(n2); liberer_Noeud(n3);
    liberer_arbre(a);
    liberer_reseau(r);

    return 0;
}