#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int zbroj = 0;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Korištenje: %s <broj_procesa>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int broj_procesa = atoi(argv[1]);
    pid_t pid;

    for (int i = 0; i < broj_procesa; i++) {
        pid = fork();
        if (pid < 0) {
            perror("Greška prilikom izvođenja fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            zbroj += 1;
            exit(0);
        }
    }

    for (int i = 0; i < broj_procesa; i++) {
        wait(NULL);
    }

    printf("Konačna vrijednost varijable zbroj u roditeljskom procesu: %d\n", zbroj);
    return EXIT_SUCCESS;
}

/* gcc procesi.c -o procesi */
