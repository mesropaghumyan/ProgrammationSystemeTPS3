#ifdef __APPLE__
#include <dispatch/dispatch.h>
#else
#include <semaphore.h>
#endif

struct rk_sema {
#ifdef __APPLE__
    dispatch_semaphore_t    sem;
#else
    sem_t                   sem;
#endif
};

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

long long int N = 8000000000;

int T = 3;

double resA;

sem_t semaphore;

void* sommeA(void* arg) {
    sem_wait(&semaphore);
    //sleep(1);

    double index = *(double*)arg;
    double end;
    double A = 0;
    double start = index * (N/T);

    if(index != T-1) { end = (index+1)*(N/T); }
    else             { end = N; }

    for(double i = start+1; i < end+1; i++) {
        A = A + (1/(17+i*i)); 
        //printf("[TEST A] Thread %lf -> A = %lf ; i = %lf\n", index, A, i);
    }

    *(double*)arg = A;
    return arg;
    sem_post(&semaphore);
}

void* sommeB(void* arg) {
    sem_wait(&semaphore);
    //sleep(1);

    double index = *(double*)arg;
    double end;
    double B = 0;
    double start = index * (N/T);

    if(index != T-1) { end = (index+1)*(N/T); }
    else             { end = N; }

    for(double i = start+1; i < end+1; i++) {
        B = B + (1/(resA+i*i));
        //printf("[TEST B] Thread %lf -> B = %lf ; i = %lf\n", index, B, i);
    }

    *(double*)arg = B;
    return arg;
    sem_post(&semaphore);
}

int main(void) {

    int i;
    double* r_ptr;
    double* r_ptr_prime;
    double sumA = 0;
    double sumB = 0;

    double temps;
    clock_t start, end;

    pthread_t thread_id[T];

    sem_init(&semaphore, 0, 1);

    start = clock();

    for(i = 0; i < T; i++) {
        double *nb = malloc(sizeof(int));
        *nb = (double)i;
        if(pthread_create(&thread_id[i], NULL, sommeA, nb) != 0) { perror("Erreur lors de la création du thread\n"); }
    }

    for(i = 0; i < T; i++) {
        if(pthread_join(thread_id[i], &r_ptr) != 0) { perror("Erreur lors de la jointure du thread\n"); }
        sumA = sumA + *r_ptr;
        free(r_ptr);
    }


    resA = sumA;

    
    for(i = 0; i < T; i++) {
        double *nombre = malloc(sizeof(int));
        *nombre = (double)i;

        if(pthread_create(&thread_id[i], NULL, sommeB, nombre) != 0) { perror("Erreur lors de la création du thread\n"); }
    }

    for(i = 0; i < T; i++) {
        if(pthread_join(thread_id[i], &r_ptr_prime) != 0) { perror("Erreur lors de la jointure du thread\n"); }
        sumB = sumB + *r_ptr_prime;
    }

    end = clock();

    temps = ((double) (end-start)) / CLOCKS_PER_SEC;
    printf("A = %lf ; Nb de Threads = %d\n", sumA, T);
    printf("B = %lf ; Nb de Threads = %d\n", sumB, T);
    printf("Temps : %lf\n", temps);

    return 0;
}