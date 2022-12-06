#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

long long int N = 10;
int NB_FILS;

int main(void) {

    printf("Nombre de fils ?\n>> ");
    scanf("%d", &NB_FILS);

    double id = -1;
    int i = 0;
    int pid;

    while((id == -1) && (i < NB_FILS)) {

        pid = fork();

        if(pid == - 1) { perror("Erreur, échec lors de la création d'un fils\n"); }
        else if(pid != 0) {
            id = -1;
            wait(0);
        }
        else if(pid == 0) {
            id = (double)i;
        }
        i++;
    }

    if(id == -1) {
        
        char * somme = (char *) malloc( 64000 );

        FILE* ff = fopen("somme.txt", "r");
        if(ff == NULL) {
            printf("Erreur, le fichier n'a pas pu être ouvert.\n");
            return EXIT_FAILURE;
        }

        double resGlobal = 0;
        int cmpt = 0;
        int cmpt_p = 0;

        while ( ! feof( ff ) ) {
            fgets( somme, 100, ff );
            cmpt++;
        }

        char nb[64000];
        char *eptr;
        double ss;

        while(somme[cmpt] != '\0') {
            if(somme[cmpt] == ';') {
                ss = strtod(nb, &eptr);
                resGlobal = resGlobal + ss;
                nb[0] = '\0';
                cmpt_p = 0;
                cmpt++;
            } else {
                nb[cmpt_p] = somme[cmpt];
                cmpt_p++;
                cmpt++;
            }
        }

    } else {
        double end;
        double s = 0;
        double start = (id) * (N/NB_FILS);
       
        if(id != NB_FILS-1) { end = (id+1)*(N/NB_FILS); }
        else             { end = N; }
        for(double i = start+1; i < end+1; i++) { s = s + (1/i/i); }

        char buffer[64000];
        sprintf(buffer, "%f", s);

        FILE* f = fopen("somme.txt", "a");

        if(f == NULL) {
            printf("Erreur, le fichier n'a pas pu être ouvert.\n");
            return EXIT_FAILURE;
        }

        fprintf(f, "%s;", buffer);
        fclose(f);
    }

    return 0;
}