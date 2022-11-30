#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

long long int N = 8000000000;

int T = 1;

void* somme(void* arg) {
    double index = *(double*)arg;

    double end;
    double s = 0;
    double start = index * (N/T);

    if(index != T-1) { end = (index+1)*(N/T); }
    else             { end = N; }

    for(double i = start+1; i < end+1; i++) {
        s = s + (1/(1+i*i)); 
       //printf("Thread %lf -> Somme = %lf\n", index, s);
    }

    *(double*)arg = s;
    return arg;
}

int main(void) {

    int i;
    double* r_ptr;
    double globalSum = 0;
    double temps;
    clock_t start, end;

    pthread_t thread_id[T];

    start = clock();

    for(i = 0; i < T; i++) {
        double *nb = malloc(sizeof(int));
        *nb = (double)i;
        if(pthread_create(&thread_id[i], NULL, somme, nb) != 0) { perror("Erreur lors de la création du thread\n"); }
    }

    for(i = 0; i < T; i++) {
        if(pthread_join(thread_id[i], &r_ptr) != 0) { perror("Erreur lors de la jointure du thread\n"); }
        globalSum = globalSum + *r_ptr;
        free(r_ptr);
    }

    end = clock();

    temps = ((double) (end-start)) / CLOCKS_PER_SEC;

    printf("Somme total = %lf ; Temps = %lf ; Nb de Threads = %d\n", globalSum, temps, T);

    return 0;
}