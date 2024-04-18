#include "File.h"
#include "graphe.h"
#include <stdlib.h>
#include "Reseau.h"
#include "ArbreQuat.h"
#include "assert.h"

/*Test de la structure grahe*/
int main(){

    FILE * lecture = fopen("00014_burma.cha", "r");
    Chaines* test = lectureChaines(lecture);
    Reseau* test_reseau = reconstitueReseauArbre(test);

    //test question 1
    Graphe* g = creerGraphe(test_reseau);
    assert(g->gamma == test_reseau->gamma);
    assert(g->nbcommod == nb_commodite(test_reseau));
    assert(g->nbsom == test_reseau->nbNoeuds);
    
    
    //test des voisins
    /*
    for (int i = 1; i < g->nbsom+1; i++){
        Sommet* s = g->T_som[i];
        Cellule_arete* vois = s->L_voisin;
        printf("\n sommet %d:\n", s->num);
        
        while(vois){
            printf("arete %d %d \n", vois->a->u, vois->a->v);
            vois = vois->suiv;
        }
    }
    */

    //test question 2
    for (int i = 0; i < g->nbcommod; i++){
        printf("les sommets %d %d ",g->T_commod[i].e1,g->T_commod[i].e2);
        printf("nb aretes %d \n", plus_petit_nb_aretes(g, g->T_som[g->T_commod[i].e1], g->T_som[g->T_commod[i].e2]));
    }

    libererGraphe(g);
}