/*
* Écrire un programme qui lance des threads producteurs et des threads consommateurs qui
* partagent un buffer de taille N géré de façon circulaire.
*/
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define N 100 //buffer size
#define nbProd 5 //consumers
#define nbCons 5 //producers

char buffer[N];
int nextin = 0, nextout = 0; //indices d’entrée et de sortie du buffer
int count = 0; // nb objets dans le buffer

pthread_cond_t notfull = PTHREAD_COND_INITIALIZER;
pthread_cond_t notempty = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// déposer un caractère x dans le buffer
void produce_char ( char x){
    for (int i = 0; i < N; i++) {
        if (count == N)
            pthread_cond_wait(&notfull,&mutex);
        pthread_mutex_lock(&mutex);
        buffer [nextin] = x;
        nextin = (nextin + 1) % N;
        count ++;
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&notempty);
    }
    pthread_exit(0);
}

/* Fonction exécutée par le thread consommateur */
void take (char *x) {
    // retirer un caractère du buffer
    for (int i = 0; i < N; i++) {
        if (count == 0)
            pthread_cond_wait(&notempty, &mutex) ;
        pthread_mutex_lock(&mutex);
        *x = buffer [nextout] ;
        nextout = (nextout + 1) % N;
        count --;
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&notfull);
    }
    pthread_exit(0);
}


int main(int argc, char const *argv[]) {
    pthread_t producers[nbProd];
    pthread_t consumers[nbCons];

    for (int i = 0; i < nbProd; i++) {
        if(pthread_create(producers[i],NULL,(void *)produce_char,(void *)i)){
            printf("Error creating thread nb:%d\n", i+1);
            exit(-1);
        }
    }

    for (int i = 0; i < nbCons; i++) {
        if(pthread_create(consumers[i],NULL,(void *)take,NULL)){
            printf("Error creating thread nb:%d\n", i+1);
            exit(-1);
        }
    }
    printf("Waiting producers to finish\n");
    for (int i = 0; i < nbProd; i++) {
        pthread_join(producers[i],NULL);
    }

    printf("Waiting consumers to finish\n");
    for (int i = 0; i < nbCons; i++) {
        pthread_join(consumers[i],NULL);
    }
    return 0;
}
