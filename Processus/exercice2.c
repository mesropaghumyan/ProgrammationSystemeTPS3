#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int liste[9];

int main(void) {

    int id = -1;
    int i = 0;
    int j = 0;
    int pid;

    while((id == -1) && (i < 10)) {

        pid = fork();

        if(pid == - 1) { perror("Erreur, échec lors de la création d'un fils\n"); }
        else if(pid != 0) {
            id = -1;
            wait(0);
            liste[j] = pid;
            j++;
        }
        else if(pid == 0) {
            id = i;
        }
        i++;
    }

    if(id == -1) {
        printf("Je suis le père et voici la liste des pid de mes fils : \n");
        j = 0;
        while(j <= 9) {
            printf("%d : %d\n", j+1, liste[j]);
            j++;
        }
    }
    else {
        printf("Je suis le fils numéro %d, mon pid est %d, et mon père à pour pid %d\n", i, getpid(), getppid());
    }

    return 0;
}