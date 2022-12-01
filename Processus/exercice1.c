#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {

    int id = -1;
    int i = 0;
    int pid;

    while((id == -1) && (i < 10)) {

        pid = fork();

        if(pid == - 1) { perror("Erreur, échec lors de la création d'un fils\n"); }
        else if(pid != 0) {
            id = -1;
            wait(0);
        }
        else if(pid == 0) {
            id = i;
        }
        i++;
    }

    if(id == -1) { printf("Je suis le père\n"); }
    else { printf("Je suis le fils numéro %d\n", i); }

    return 0;
}