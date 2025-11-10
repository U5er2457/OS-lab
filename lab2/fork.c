#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void child_create(int numberOfChildren) {
    for (int i = 0; i < numberOfChildren; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            printf("Dijete #%d\n", i+1);
            exit(0);
        } else {
            printf("Roditelj #%d\n", i+1);
            wait(NULL);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Ispravno korištenje: %s <numberOfChildren>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int numberOfChildren = atoi(argv[1]);

    if (numberOfChildren <= 0) {
        fprintf(stderr, "Broj djece ne može biti manji od 0.\n");
        return EXIT_FAILURE;
    }

    setbuf(stdout, NULL);

    child_create(numberOfChildren);

    return EXIT_SUCCESS;
}
