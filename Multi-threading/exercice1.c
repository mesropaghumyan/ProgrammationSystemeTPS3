#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long int N = 8000000000;

int main(void) {

    double s = 0;
    double temps;
    clock_t start, end;
    
    start = clock();

    for(double i = 1; i <= N; i++) { s = s + (1/(1+i*i)); }

    end = clock();

    temps = ((double) (end-start)) / CLOCKS_PER_SEC;

    printf("Somme = %lf ; Temps = %lf\n", s, temps);

    return 0;
}