#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long int N = 10000000000;

int main(void) {

    double temps;
    clock_t start, end;

    double i, A = 0, B = 0;

    start = clock();

    for(i = 1; i < N; i++) { A = A + (1/(17+i*i)); }

    for(i = 1; i < N; i++) { B = B + (1/(A+i*i)); }

    end = clock();

    temps = ((double) (end-start)) / CLOCKS_PER_SEC;

    printf("A = %lf ; B = %lf ; Temps = %lf\n", A, B, temps);

    return 0;
}