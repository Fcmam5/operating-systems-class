#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
/*
*   Exercice1
*   Implémenter la jointure (join()) à l'aide des variables de condition.
*/
pthread_cond_t cond =PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex =PTHREAD_MUTEX_INITIALIZER;

int fils_terminer;

void thr_join() {
    /* Thread join */
    pthread_mutex_lock(&mutex);
    while (fils_terminer) {
        pthread_cond_wait(&cond, &mutex);
    }
    pthread_mutex_unlock(&mutex);
}

void func() {
    printf("Thread started\n");
    sleep(rand() % 5);
    pthread_mutex_lock(&mutex);
    fils_terminer = 1;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}

int main(void) {
    pthread_t th1;
    fils_terminer = 0;

    printf("Launching\n");
    pthread_create(&th1, NULL,(void *) func,NULL);
    printf("Stopped\n");

    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);
    return 0;
}
