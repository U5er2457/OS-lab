
//Veličina datoteke: 7580B

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char array[100000];

int main() {
    srand(time(NULL));
        for (int i = 0; i < 100000; i++) {
            int br = rand() % 2;

            if(br==0){
                array[i] = '1';
            }
            else{
                array[i] = 'x';
            }
        }

        for (int i = 0; i < 100000; i++) {
            if (array[i] == 'x') {
                if (i < 99999 && array[i + 1] == '1') {
                    printf("-1");
                    i++;
                }
            } else {
                printf("%c", array[i]);
            }
        }
        printf("\n");
    return 0;
}
