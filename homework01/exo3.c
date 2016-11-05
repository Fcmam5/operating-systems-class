#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

double result = 0;
int N = 3;

typedef struct matrice{
    double v[];
    double u[];
    int n;
}

/*
La fonction suivante calcule séquentiellement le produit scalaire des vecteurs u et v de taille n
et stocke le résultat dans la variable globale result initialisée à 0.

On souhaite écrire un programme multithread qui calcule le produit scalaire de manière
parallèle. Écrire un programme qui démarre N threads, chacun des N threads calcule une
partie du produit scalaire et stocke le résultat partielle dans une variable partagée result
initialisée à 0.
*/
void produit_scalaire_seq(matrice *mt) {
    int i;

    for (i = 0; i < n; i++) {
        result += v[i]*u[i];
    }
}

int main() {
    pthread_t threads[N];
    matrice m;

    return 0;
}
