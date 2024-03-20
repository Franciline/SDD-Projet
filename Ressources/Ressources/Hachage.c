#include "Hachage.h"
#include <math.h>

int h(TableHachage* t, int k) {
    int M = t->nbElement;
    double A = (sqrt(5) - 1) / 2;

    return floor(M*(k*A - floor(k*A)));
}