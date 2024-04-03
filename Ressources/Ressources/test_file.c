#include "File.h"

int main(int argc, char* argv) {
    File* f = creer_file();

    Sommet* s1 = (Sommet*) malloc(sizeof(Sommet));
    s1->num = 1;
    s1->x = 0;
    s1->y = 0;
    s1->L_voisin = NULL;

    Sommet* s2 = (Sommet*) malloc(sizeof(Sommet));
    s2->num = 2;
    s2->x = 10;
    s2->y = 10;
    s2->L_voisin = NULL;

    Sommet* s3 = (Sommet*) malloc(sizeof(Sommet));
    s3->num = 3;
    s3->x = 20;
    s3->y = 20;
    s3->L_voisin = NULL;

    Sommet* s4 = (Sommet*) malloc(sizeof(Sommet));
    s4->num = 4;
    s4->x = 30;
    s4->y = 30;
    s4->L_voisin = NULL;

    enfiler(f, s1);
}