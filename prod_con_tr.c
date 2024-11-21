#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_ITEMS 10

sem_t empty, full;
pthread_mutex_t mutex;
int buffer[MAX_ITEMS];
int in = 0, out = 0;

void* producer(void* param) {
    for (int i = 0; i < MAX_ITEMS; i++) {
        sem_wait(&empty); // Wait for an empty slot
        pthread_mutex_lock(&mutex); // Enter critical section
        
        buffer[in] = i; // Produce item
        printf("Produced: %d\n", buffer[in]);
        in = (in + 1) % MAX_ITEMS;
        
        pthread_mutex_unlock(&mutex); // Leave critical section
        sem_post(&full); // Signal that there is a new item
    }
    return NULL;
}

void* consumer(void* param) {
    for (int i = 0; i < MAX_ITEMS; i++) {
        sem_wait(&full); // Wait for a full slot
        pthread_mutex_lock(&mutex); // Enter critical section
        
        int item = buffer[out]; // Consume item
        printf("Consumed: %d\n", item);
        out = (out + 1) % MAX_ITEMS;
        
        pthread_mutex_unlock(&mutex); // Leave critical section
        sem_post(&empty); // Signal that there is an empty slot
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;
    
    sem_init(&empty, 0, MAX_ITEMS); // Initially all slots are empty
    sem_init(&full, 0, 0); // Initially no items are produced
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
