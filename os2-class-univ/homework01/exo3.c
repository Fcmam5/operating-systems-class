#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

double result = 0;
int N = 3;

void produit_scalaire_seq(double v[], double u[], int n) {
    int i;
    double rslt;
    for (i = 0; i < n; i++) {
        rslt += v[i]*u[i];
    }
    pthread_mutex_lock(&mutex);
    result += rslt;
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}

int main(int argc, char const *argv[]) {
    pthread_t threads[N];
    int n;
    n = N;
    double x[N], y[N];

    for (int k = 0; k < n; k++) {
        x[k] = rand()%5;
        y[k] = rand()%5;
    }

    for (int i = 0; i < N; i++) {
        pthread_create(&threads[i], NULL, produit_scalaire_seq, (void *)(x,y,n));
    }
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Somme est: %f\n", result);
    return 0;
}
