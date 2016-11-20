#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>

/*
The idea is #TWO wait for #ONE
        and #THREE for #TWO
        and #Algerie for #THREE
*/
sem_t s0;
sem_t s1; //Declaration
sem_t s2;
sem_t s3;

void func1(void){
    int i;
    for (i=0; i<4; i++){
        sleep(rand()%5);
        sem_wait(&s0);
        printf("One, ...\n");
        sem_post(&s1);
    }
    pthread_exit(0);
}

void func2(void){
    int i;
    for (i=0; i<4; i++){
        sleep(rand()%5);
        sem_wait(&s1);
        printf("Two, ...\n");
        sem_post(&s2);
    }

    pthread_exit(0);
}

void func3(void){
    int i;
    for (i=0; i<4; i++){
        sleep(rand()%5);
        sem_wait(&s2);
        printf("Three, ...\n");
        sem_post(&s3);
    }

    pthread_exit(0);
}

void func4(void){
    int i;
    for (i=0; i<4; i++){
        sleep(rand()%5);
        sem_wait(&s3);
        printf("Viva l'Algérie.\n");
        sem_post(&s0);
    }

    pthread_exit(0);
}

int main(){
    sem_init(&s0,0,1);
    sem_init(&s1,0,0);
    sem_init(&s2,0,0);
    sem_init(&s3,0,0);
    pthread_t th1, th2, th3, th4;
    srand(time(NULL));
    if(pthread_create(&th1, NULL, (void*) func1, NULL)){
        fprintf(stderr,"thread1");
        exit(EXIT_FAILURE);
    }

    if(pthread_create(&th2, NULL, (void*) func2, NULL)){
        fprintf(stderr,"thread2");
        exit(EXIT_FAILURE);
    }

    if(pthread_create(&th3, NULL, (void*) func3, NULL)){
        fprintf(stderr,"thread3");
        exit(EXIT_FAILURE);
    }

    if(pthread_create(&th4, NULL, (void*) func4, NULL)){
        fprintf(stderr,"thread4");
        exit(EXIT_FAILURE);
    }

    pthread_join(th1,NULL);
    pthread_join(th2,NULL);
    pthread_join(th3,NULL);
    pthread_join(th4,NULL);
    sem_destroy(&s0);
    sem_destroy(&s1);
    sem_destroy(&s2);
    sem_destroy(&s3);
    pthread_exit(0);
}
