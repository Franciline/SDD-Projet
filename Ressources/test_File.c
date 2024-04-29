#include "File.h"
#include "graphe.h"
#include <assert.h>

/*Test de la structure File*/
int main(){

    //Creation des sommets et de la file
    File* file = creer_file();
    assert(est_vide(file) ==  1);

    Sommet* s1 = creerSommet(1, 1, 1);
    Sommet* s2 = creerSommet(2, 2 ,2);
    Sommet* s3 = creerSommet(3, 3, 3);
    assert(s1 != NULL); assert(s2 != NULL); assert(s3 != NULL);

    //on enfile des sommets
    enfiler(file, s1);
    assert(file->premier->s->num == file->dernier->s->num);
    enfiler(file, s2);
    assert(file->premier->s->num == 1); assert(file->dernier->s->num == 2);
    enfiler(file, s3);
    assert(file->premier->s->num == 1); assert(file->dernier->s->num == 3);

    assert(est_vide(file) ==  0);

    //on defile des sommets
    Sommet * s = defiler(file);
    assert(s->num == 1); 
    free(s);

    s = defiler(file);
    assert(s->num == 2); 
    free(s);

    s = defiler(file);
    assert(s->num == 3);
    free(s);

    assert(est_vide(file) == 1);
    liberer_file(file);
    return 0;
}
