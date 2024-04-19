#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define TRUE 1
#define FALSE 0
using namespace std;
int flag[2];
int turn;
int shared_resource = 0;

sem_t sem;

void* process1(void* arg) {
    int i;
    for (i = 0; i < 5; i++) {
        // Entry section
        flag[0] = TRUE;
        turn = 1;
        while (flag[1] && turn == 1)
            ; // Busy wait

        // Critical section
        sem_wait(&sem);
        printf("Process 1 is in critical section\n");
        shared_resource++;
        sem_post(&sem);

        // Exit section
        flag[0] = FALSE;

        // Remainder section
        printf("Process 1 is in remainder section\n");
    }
    pthread_exit(NULL);
}

void* process2(void* arg) {
    int i;
    for (i = 0; i < 5; i++) {
        // Entry section
        flag[1] = TRUE;
        turn = 0;
        while (flag[0] && turn == 0)
            ; // Busy wait

        // Critical section
        sem_wait(&sem);
        printf("Process 2 is in critical section\n");
        shared_resource--;
        sem_post(&sem);

        // Exit section
        flag[1] = FALSE;

        // Remainder section
        printf("Process 2 is in remainder section\n");
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t tid1, tid2;

    // Initialize semaphore
    sem_init(&sem, 0, 1);

    // Create threads
    pthread_create(&tid1, NULL, process1, NULL);
    pthread_create(&tid2, NULL, process2, NULL);

    // Join threads
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    // Destroy semaphore
    sem_destroy(&sem);

    printf("Shared resource value: %d\n", shared_resource);

    return 0;
}