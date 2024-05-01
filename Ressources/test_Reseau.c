#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Chaine.h"
#include "Reseau.h"

/*Test de la structure Reseau*/
int main(){

    FILE* source = fopen("00014_burma.cha", "r");
    FILE* destination = fopen("test_w_Reseau.txt", "w");

    Chaines* chaines = lectureChaines(source);

    //test creer_reseau
    Reseau* reseau = creer_reseau(2);
    assert(reseau);

    //test reconstitueReseauListe et nb_commodite
    Reseau* reseau_rec = reconstitueReseauListe(chaines);
    assert(chaines->nbChaines == nb_commodite(reseau_rec));

    //test ecriture et affichage
    ecrireReseau(reseau_rec, destination);
    afficheReseauSVG(reseau_rec, "test_Reseau");

    //test creation de noeuds
    Noeud* noeud1 = creer_noeud(2, 2, 2);
    Noeud *noeud2 = creer_noeud(1, 1, 1);
    assert(noeud1); assert(noeud2);

    //test ajout de voisin
    ajouter_voisin(noeud1, noeud2);
    assert(noeud1->voisins != NULL);

    //test ajout de noeud au reseau
    int nb_noeud = reseau_rec->nbNoeuds;
    ajoutNoeudReseau(reseau_rec, noeud1);
    ajoutNoeudReseau(reseau_rec, noeud2);
    assert(reseau_rec->nbNoeuds == nb_noeud + 2);

    liberer_chaine(chaines);
    liberer_reseau(reseau);
    liberer_reseau(reseau_rec);
    fclose(source);
    fclose(destination);

}