
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define MAX 100
int sjedala[MAX] = {0};

pthread_mutex_t sjedala_mutex = PTHREAD_MUTEX_INITIALIZER;

void random_delay(int min, int max) {
    int delay = rand() % (max - min + 1) + min;
    sleep(delay);
}

void *check_in(void *arg) {
    int id = *((int *)arg);
    free(arg);

    random_delay(1, 5);

    random_delay(1, 3);

    int odabranoSjedalo;
    int potvrdeno = 0;

    while (!potvrdeno) {
        odabranoSjedalo = rand() % MAX;

        pthread_mutex_lock(&sjedala_mutex);

        if (sjedala[odabranoSjedalo] == 0) {
            if (rand() % 2 == 0) {
                sjedala[odabranoSjedalo] = 1;
                potvrdeno = 1;
                printf("Putnik %d uspješno odabrao sjedalo %d.\n", id, odabranoSjedalo);
            } else {
                printf("Putnik %d odbio sjedalo %d.\n", id, odabranoSjedalo);
            }
        } else {
            printf("Putnik %d odabrao sjedalo %d, ali je već zauzeto.\n", id, odabranoSjedalo);
        }

        pthread_mutex_unlock(&sjedala_mutex);

        if (potvrdeno) {
            random_delay(1, 2);
        }
    }

    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    pthread_t putnici[MAX];
    int brZauzetih = 0;
    int *id;

    for (int i = 0; i < MAX; i++) {
        id = malloc(sizeof(int));
        *id = i;
        usleep(rand() % 1000 * 1000);
        pthread_create(&putnici[i], NULL, check_in, id);
    }

    for (int i = 0; i < MAX; i++) {
        pthread_join(putnici[i], NULL);
    }

    for (int i = 0; i < MAX; i++) {
        if (sjedala[i] == 1) {
            brZauzetih++;
        }
    }

    printf("Ukupan broj zauzetih sjedala: %d\n", brZauzetih);
    printf("Ukupan broj slobodnih sjedala: %d\n", MAX - brZauzetih);

    pthread_mutex_destroy(&sjedala_mutex);

    return 0;
}

/* gcc sim.c -o sim -pthread */