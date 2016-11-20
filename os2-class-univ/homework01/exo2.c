#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
/*
Solution without mutual excultion, with a global variable
*/

const int N = 2;
float somme = 0.00; //global variable

void lineSum(float *matrice){
    for (int i = 0; i < N; i++) {
        somme+= matrice[i];
    }
    pthread_exit(NULL);
}

int main() {
    float matrix[N][N];
    pthread_t calculatingThreads[N];

    //initializing the matrix
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = (float)(rand()%7)/5; ;//To have a random float number
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%.3f ", matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < N ; i++) {
        int rc= pthread_create(calculatingThreads, NULL, lineSum, (void *)matrix[i]);
        if (rc) {
            printf("Error code %d\n", rc);
        }
    }

    for (int i = 0; i < N; i++) {
        pthread_join(calculatingThreads[i], NULL);
    }
    printf("Ma somme est: %f\n", somme);
    pthread_exit(0);
    return 0;
}
