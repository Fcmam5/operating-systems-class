#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
/*
* the output of: gcc -Wall exo1.c -lpthread -o exe && ./exe 100 |grep FIN | wc -l
* is: 100, All threads finished before quitting
*/

//copied form the PDF
void fonctionThread(void){
    pthread_t mon_tid;
    mon_tid = pthread_self(); //pthread_self(): obtain ID of the calling thread
    int i, nbreIters;
    nbreIters = rand()%100;
    i = 0;
    printf("Thread (0x)%x : DEBUT\n", (int)mon_tid);
    while(i < nbreIters) i++;
    printf("Thread (0x)%x : FIN\n", (int)mon_tid);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    int nbThreads;
    int rc;
    nbThreads = atoi(argv[1]); //ASCII to int function

    if(argc ==2 ){
        pthread_t threads[nbThreads];
        for (int i = 0; i < nbThreads; i++) {
            rc = pthread_create(&threads[i], NULL, fonctionThread,NULL);
            //TODO: it gives a warning, I should fix it
        }

        for (int i = 0; i < nbThreads; i++) {
            pthread_join(threads[i], NULL);
            if(rc){
                printf("Error creating thread, error code= %d\n", rc);
                exit(-1);
            }
        }
        pthread_exit(0);

        return 0;
    }
    else{
            printf("1 Argument expected (ex: %s 5)\n", argv[0]);
            exit(-2);
    }
}
