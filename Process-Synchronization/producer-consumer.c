#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5 // Size of the buffer

int buffer[BUFFER_SIZE]; // Shared buffer
int in = 0; // Next empty slot in the buffer
int out = 0; // Next full slot in the buffer

sem_t empty; // Semaphore to count empty slots
sem_t full;  // Semaphore to count full slots
pthread_mutex_t mutex; // Mutex for mutual exclusion

void* producer(void* arg) {
    int item;
    while (1) {
        item = rand() % 100; // Produce an item (random number)
        
        sem_wait(&empty); // Decrease count of empty slots
        pthread_mutex_lock(&mutex); // Enter critical section

        // Add item to buffer
        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE; // Circular increment

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&full); // Increase count of full slots
        
        sleep(1); // Simulate time taken to produce an item
    }
}

void* consumer(void* arg) {
    int item;
    while (1) {
        sem_wait(&full); // Decrease count of full slots
        pthread_mutex_lock(&mutex); // Enter critical section

        // Remove item from buffer
        item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE; // Circular increment

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&empty); // Increase count of empty slots
        
        sleep(1); // Simulate time taken to consume an item
    }
}

int main() {
    pthread_t prod, cons;

    sem_init(&empty, 0, BUFFER_SIZE); // Initialize empty semaphore to buffer size
    sem_init(&full, 0, 0); // Initialize full semaphore to 0
    pthread_mutex_init(&mutex, NULL); // Initialize mutex

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
