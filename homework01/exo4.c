//copied code from "Fiche TP"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

sem_t S;

void mes1(void){
    sleep(rand()%5);
    sem_wait(&S);
    printf("Deux,...");
    pthread_exit(0);
}

void mes2(void){
    sleep(rand()%5);
    printf("Un,...");
    sem_post(&S);
    pthread_exit(0);

}
int main(){
    pthread_t th1, th2;
    srand(time(NULL));
    sem_init(&S,0,0);
    if(pthread_create(&th1, NULL, (void*) mes1, NULL)){
        fprintf(stderr,"thread1");
        exit(EXIT_FAILURE);
    }
    if(pthread_create(&th2, NULL, (void*) mes2, NULL)){
        fprintf(stderr,"thread2");
        exit(EXIT_FAILURE);
    }
    pthread_join(th1,NULL);
    pthread_join(th2,NULL);
    printf("\nFini!\n");
    sem_destroy(&S);
    exit(EXIT_SUCCESS);
}
