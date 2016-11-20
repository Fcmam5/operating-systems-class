#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t s1;
sem_t s2;


void afficher1() {
    for(int i=0;i<10;i++){
    sem_wait(&s1);
    printf("1\n");
    sem_post(&s2);
    }
    pthread_exit(0);
}

void afficher2() {
    for(int i=0;i<10;i++){
    sem_wait(&s2);
    printf("2\n");
    sem_post(&s1);
    }
    pthread_exit(0);
}


void afficher3() {
    for(int i=0;i<10;i++){
    sem_wait(&s2);
    printf("3\n");
    sem_post(&s1);
    }
    pthread_exit(0);
}

int main() {
    pthread_t th1,th2,th3;
    sem_init(&s1,0,1);
    sem_init(&s2,0,0);


    printf("Printing 1(2 xor 3)1(2 xor 3)...\n");
    pthread_create(&th1, NULL, (void*)afficher1,NULL);
    pthread_create(&th2, NULL, (void*)afficher2,NULL);
    pthread_create(&th3, NULL, (void*)afficher3,NULL);
    pthread_join(th1,NULL);
    pthread_join(th2,NULL);
    pthread_join(th3,NULL);
    sem_destroy(&s1);
    sem_destroy(&s2);

    return 0;
}
