#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int N = 3;
int counter = 0;
sem_t S;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/*

*/
void threadRDV(int i){
    sleep(rand()%5);
    printf("Hello from thread %d , came at %d\n", i, counter);

    pthread_mutex_lock(&mutex);
    counter++;

    if(counter == N){
        printf("All threads are here\n");
        for (int i = 0; i < N; i++) {
            sem_post(&S);
        }
    }
    pthread_mutex_unlock(&mutex);
    sem_wait(&S);
    sleep(rand()%5);
    pthread_exit(0);
}

int main() {
    pthread_t threads[N];
    sem_init(&S,0,0);
    sleep(rand()%5);

    for (int i = 0; i < N; i++) {
        pthread_create(&threads,NULL,threadRDV,(void *)i);
    }
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i],NULL);
    }
    sem_destroy(&S);
    pthread_exit(0);
    return 0;
}
