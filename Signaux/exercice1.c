#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

long long int N = 496688;
double s = 0;

void sig_handler(int signum){
  printf("Somme = %lf\n", s);
  alarm(1);
}
 
int main(){

    double temps;
    clock_t start, end;

    start = clock();

    signal(SIGALRM,sig_handler); // Register signal handler
    alarm(1);

    for(double i=1; i < N; i++){
        
        s = s + (1/(1+i*i));
        pause();
    }

    end = clock();

    temps = ((double) (end-start)) / CLOCKS_PER_SEC;

    printf("Temps = %lf\n", temps);
 
return 0;
}