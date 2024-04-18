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




    
}   
