#include "File.h"
#include "graphe.h"
#include <stdlib.h>
#include "Reseau.h"
#include "ArbreQuat.h"
#include "assert.h"

/*Test de la structure graphe*/
int main(){

    FILE * lecture = fopen("00014_burma.cha", "r");
    Chaines* chaine = lectureChaines(lecture);
    Reseau* reseau = reconstitueReseauArbre(chaine);

    //test question 1
    Graphe* g = creerGraphe(reseau);
    assert(g);
    assert(g->gamma == reseau->gamma);
    assert(g->nbcommod == nb_commodite(reseau));
    assert(g->nbsom == reseau->nbNoeuds);
    
    
    //affichage des voisins
    printf("\nAffichage de tous les aretes\n");
    for (int i = 1; i < g->nbsom+1; i++){
        Sommet* s = g->T_som[i];
        Cellule_arete* vois = s->L_voisin;
        printf("\nAretes du sommet %d:\n", s->num);
        while(vois){
            printf("arete %d %d \n", vois->a->u, vois->a->v);
            vois = vois->suiv;
        }
    }
    
    
    //test question 2
    //affichage du plus petit nombre d'aretes entre deux extremites
    printf("\nAffichage du plus petit nombre d'aretes entre deux extremites\n");
    for (int i = 0; i < g->nbcommod; i++){
        printf("Nombre d'aretes minimal entre %d et %d : %d \n", g->T_commod[i].e1,g->T_commod[i].e2, plus_petit_nb_aretes(g, g->T_som[g->T_commod[i].e1], g->T_som[g->T_commod[i].e2]));
    }
    

    
    fclose(lecture);
    liberer_Graphe(g);
    liberer_chaine(chaine);
    liberer_reseau(reseau);
    
}