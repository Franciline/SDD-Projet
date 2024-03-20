#include <stdio.h>
#include <stdlib.h>

int f(int x, int y){
    return y + (x + y)*(x + y + 1)/2;
} 

int main(){
    for (int i = 1; i < 11; i++){
        for (int j = 1; j < 11; j++){
            printf("%d\n", f(i, j));
        }
    }
}