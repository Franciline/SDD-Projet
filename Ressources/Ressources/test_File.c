#include "File.h"
#include "graphe.h"
#include <assert.h>

int main(){
    File* f = creer_file();
    Sommet* s1 = creerSommet(1, 0, 0);
    Sommet* s2 = creerSommet(2, 0 ,0);
    Sommet* s3 = creerSommet(3, 0, 0);

    assert( est_vide(f) ==  1);

    //on enfile des sommets
    enfiler(f, s1);
    printf("on enfile s1, premier element sommet %d, dernier sommet %d\n", f->premier->s->num,f->dernier->s->num);
    enfiler(f, s2);
    printf("on enfile s2, premier element sommet %d, dernier sommet %d\n", f->premier->s->num,f->dernier->s->num);
    enfiler(f, s3);
    printf("on enfile s3, premier element sommet %d, dernier sommet %d\n", f->premier->s->num,f->dernier->s->num);

    assert( est_vide(f) ==  0 );

    //on defile des sommets
    Sommet * s = defiler(f);
    printf("On defile: sommet %d \n", s->num);
    s = defiler(f);
    printf("On defile: sommet %d \n", s->num);
    s = defiler(f);
    printf("On defile: sommet %d \n", s->num);

    assert( est_vide(f) ==  1);

    return 0;
}
