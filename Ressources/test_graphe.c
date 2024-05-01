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
    //test de la fonction creerGraphe
    Graphe* g = creerGraphe(reseau);
    assert(g);
    assert(g->gamma == reseau->gamma);
    assert(g->nbcommod == nb_commodite(reseau));
    assert(g->nbsom == reseau->nbNoeuds);
    
    //affichage des sommet et de leurs voisins
    printf("\nAffichage de tous les aretes\n");
    for (int i = 0; i < g->nbsom; i++){
        Sommet* s = g->T_som[i];
        Cellule_arete* vois = s->L_voisin;
        printf("\nAretes du sommet %d:\n", s->num);
        while(vois){
            printf("arete %d %d \n", vois->a->u, vois->a->v);
            vois = vois->suiv;
        }
    }
    
    //test question 2 et 3
    //affichage du plus petit nombre d'aretes et de la plus petite chaine entre deux extremites
    printf("\nAffichage du plus petit nombre d'aretes entre deux extremites\n");
    for (int i = 0; i < g->nbcommod; i++){
        printf("Nombre d'aretes minimal entre %d et %d : %d \n", g->T_commod[i].e1,g->T_commod[i].e2, plus_petit_nb_aretes(g, g->T_som[g->T_commod[i].e1 - 1], g->T_som[g->T_commod[i].e2 -1]));
        int* chaine_commod = plus_petit_nb_aretes_liste(g, g->T_som[g->T_commod[i].e1-1], g->T_som[g->T_commod[i].e2-1]);
        int i = 0;
        while(chaine_commod[i] != 0){
            printf("%d, ", chaine_commod[i]);
            i++;
        }
        printf("\n");
        free(chaine_commod);
    }

    //test question 4 
    //fonctionnement correct de reorganiseReseau
    int t = reorganiseReseau(reseau);
    printf("\nRetour de reorganiseReseau %d\n", t);
    
    fclose(lecture);
    liberer_Graphe(g);
    liberer_chaine(chaine);
    liberer_reseau(reseau);   
}