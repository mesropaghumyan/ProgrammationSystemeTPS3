#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define __deprecated_msg(_msg) __attribute__((__deprecated__(_msg)))

long long int N = 10;
int NB_FILS = 3;

int main(void) {

    // Déclaration des variables
    int pid;
    double id = -1;
    int i = 0;

    //Boucle permettant de créer des fils
    while ((id==-1) && (i<NB_FILS)) {
        pid = fork();
        if(pid != 0) {
            id = -1;
            wait(0);
        }
        else { id = (double)i; }

        i++;
    }

    if(id==-1) {
        char * somme = (char *) malloc( 100 );

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

        char nb[100];
        char *eptr;
        double ss;

        // transformation
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

        printf("somme : %lf\n", resGlobal);

    }
    else {
        sleep(1);
        double end;
        double s = 0;
        double start = (id) * (N/NB_FILS);
        if(id != NB_FILS-1) { end = (id+1)*(N/NB_FILS); }
        else             { end = N; }
        for(double i = start+1; i < end+1; i++) { s = s + (1/(1+i*i)); }

        char buffer[100];
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
