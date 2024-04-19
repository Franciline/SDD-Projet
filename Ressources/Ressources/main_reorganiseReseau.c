#include "File.h"
#include "graphe.h"
#include <stdlib.h>
#include <stdio.h>
#include "Reseau.h"
#include "Chaine.h"
#include "ArbreQuat.h"
#include "SVGwriter.h"

/*Main pour tester reorganiseReseau sur plusieurs instances*/
int main(){
    Chaines* test = generationAleatoire(5, 100, 5000, 5000);
    test->gamma = 3;

    Reseau* reseau = reconstitueReseauArbre(test);
    int t = reorganiseReseau(reseau);
    printf("pour gamma = %d %d\n", test->gamma, t);

    liberer_chaine(test);
    liberer_reseau(reseau);

    return 0;
}