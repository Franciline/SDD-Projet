#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Chaine.h"
#include "Reseau.h"
#include "Hachage.h" 

/*Test de la structure table de hachage*/
int main(){
    //Creation de la table de hachage
    TableHachage* tableH = initTableHachage(10);
    assert(tableH);
    assert(tableH->nbElement == 0); 
    assert(tableH->tailleMax == 10);

    Reseau *r = creer_reseau();
    Noeud *n1 = creer_noeud(8, 2, 1);
    CellNoeud * cellN = creer_cellnoeud(n1);

    int indice = h(tableH, f(8, 2)); //indice du noeud dans la table de hachage
    tableH->T[indice] = cellN;

    //recherche de n1 existant, le nombre de noeud dans le reseau n'incremente pas
    rechercheCreeNoeudHachage(r, tableH, 8, 2);
    assert(r->nbNoeuds == 0);
    
    //recherche d'un noeud inexistant, le nombre de noeud dans le reseau incremente 
    rechercheCreeNoeudHachage(r, tableH, 1, 1);
    assert(r->nbNoeuds == 1);

    liberer_tablehachage(tableH);
    liberer_Noeud(n1);
    liberer_reseau(r);
}   
