#include "Hachage.h"
#include <math.h>
#include "Reseau.h"

int f(int x, int y){
    return y + (x + y)*(x + y + 1)/2;
} 

int h(TableHachage* t, int k) {
    int M = t->nbElement;
    double A = (sqrt(5) - 1) / 2;

    return floor(M*(k*A - floor(k*A)));
}
