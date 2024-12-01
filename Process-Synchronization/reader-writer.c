
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

sem_t mutex; // Semaphore for mutual exclusion
sem_t writeLock; // Semaphore for writers
int readCount = 0; // Count of active readers
int sharedData = 0; // Shared data

void* reader(void* arg) {
    int id = *((int*)arg);
    while (1) {
        sem_wait(&mutex); // Enter critical section for readers
        readCount++;
        if (readCount == 1) {
            sem_wait(&writeLock); // First reader locks the writer
        }
        sem_post(&mutex); // Exit critical section for readers

        // Reading section
        printf("Reader %d: read sharedData = %d\n", id, sharedData);
        sleep(1); // Simulate reading time

        sem_wait(&mutex); // Enter critical section for readers
        readCount--;
        if (readCount == 0) {
            sem_post(&writeLock); // Last reader unlocks the writer
        }
        sem_post(&mutex); // Exit critical section for readers
        sleep(1); // Simulate time between reads
    }
}

void* writer(void* arg) {
    int id = *((int*)arg);
    while (1) {
        sem_wait(&writeLock); // Request exclusive access to write

        // Writing section
        sharedData++;
        printf("Writer %d: updated sharedData to %d\n", id, sharedData);
        sleep(2); // Simulate writing time

        sem_post(&writeLock); // Release exclusive access
        sleep(2); // Simulate time between writes
    }
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int readerIds[NUM_READERS], writerIds[NUM_WRITERS];

    sem_init(&mutex, 0, 1); // Initialize mutex semaphore
    sem_init(&writeLock, 0, 1); // Initialize write lock semaphore

    for (int i = 0; i < NUM_READERS; i++) {
        readerIds[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &readerIds[i]);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        writerIds[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writerIds[i]);
    }

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&writeLock);
    
    return 0;
}
