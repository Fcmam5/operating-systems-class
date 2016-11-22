/*
* Écrire un programme qui lance des threads producteurs et des threads consommateurs qui
* partagent un buffer de taille N géré de façon circulaire.
*/
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define N 7 //buffer size
#define NB 3 // 3 threads each

char buffer[N];
int nextin = 0, nextout = 0; //indices d’entrée et de sortie du buffer
int count = 0; // nb objets dans le buffer

pthread_cond_t notfull = PTHREAD_COND_INITIALIZER;
pthread_cond_t notempty = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// déposer un caractère x dans le buffer
void produce_char(void **argument){
    char produced = 97+rand()%27;
    if (count == N)
        pthread_cond_wait(&notfull,&mutex);
    pthread_mutex_lock(&mutex);
    printf("I produced %c\n", produced);
    buffer [nextin] = produced;
    nextin = (nextin + 1) % N;
    count ++;
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&notempty);
    pthread_exit(0);
}

/* Fonction exécutée par le thread consommateur */
void take(void *args) {
    // retirer un caractère du buffer
    char tooked;
    if (count == 0)
        pthread_cond_wait(&notempty, &mutex) ;
    pthread_mutex_lock(&mutex);
    tooked = buffer [nextout] ;
    printf("I'm taking %c\n", tooked);
    nextout = (nextout + 1) % N;
    count --;
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&notfull);
    pthread_exit(0);
}


int main(int argc, char const *argv[]) {
    pthread_t producer[NB];
    pthread_t consumer[NB];


    printf("\nCreating Threads\n");
    for (int i = 0; i < NB; i++) {
        if(pthread_create(&producer[i],NULL,(void *)produce_char,NULL)){
            printf("Error creating thread \n");
            exit(-1);
        }
        if(pthread_create(&consumer[i],NULL,(void *)take,NULL)){
            printf("Error creating thread\n");
            exit(-1);
        }
    }

    printf("Waiting producer to finish\n");
    for (int i = 0; i < NB; i++) {
        pthread_join(producer[i],NULL);
    }
    printf("Waiting consumer to finish\n");
    for (int i = 0; i < NB; i++) {
        pthread_join(consumer[i],NULL);
    }
    pthread_cond_destroy(&notfull);
    pthread_cond_destroy(&notempty);
    pthread_mutex_destroy(&mutex);

    return 0;
}
