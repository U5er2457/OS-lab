#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 100000

int zbroj = 0;

pthread_mutex_t mutex;

void* increment(void* arg) {
    pthread_mutex_lock(&mutex);
    zbroj += 1;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Korištenje: %s <broj_dretvi>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int broj_dretvi = atoi(argv[1]);
    if (broj_dretvi <= 0 || broj_dretvi > MAX) {
        fprintf(stderr, "Unesite pozitivan broj dretvi (od 1 do %d).\n", MAX);
        return EXIT_FAILURE;
    }

    pthread_t threads[broj_dretvi];

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < broj_dretvi; i++) {
        if (pthread_create(&threads[i], NULL, increment, NULL) != 0) {
            perror("Kreiranje dretvi nije uspjelo!");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < broj_dretvi; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Konačna vrijednost varijable zbroj: %d\n", zbroj);

    pthread_mutex_destroy(&mutex);

    return EXIT_SUCCESS;
}

/* gcc dretve.c -o dretve */
