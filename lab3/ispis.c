#include <stdio.h>
#include <stdlib.h>

int main() {
    for (int pid = 1, count = 0; count < 10 && pid < 5000; pid++) {
        char path[64];
        sprintf(path, "/proc/%d/stat", pid);

        FILE *f = fopen(path, "r");
        if (!f) continue;

        int mypid, ppid;
        char name[256], state;

        fscanf(f, "%d (%[^)]) %c %d", &mypid, name, &state, &ppid);
        fclose(f);

        printf("Proces %d: ime=%s, PID=%d, PPID=%d\n",
               ++count, name, mypid, ppid);
    }

    return 0;
}


/*

naredbe:
gcc ispis.c -o ispis
./ispis

*/