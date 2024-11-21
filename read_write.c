#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

sem_t resource, rmutex; // Semaphores for resource and reader count
int reader_count = 0;   // Number of active readers

void* reader(void* arg) {
    int id = *((int*)arg);

    sem_wait(&rmutex);          // Lock to update reader_count
    reader_count++;
    if (reader_count == 1) {    // First reader locks the resource
        sem_wait(&resource);
    }
    sem_post(&rmutex);          // Unlock after updating reader_count

    // Reading section
    printf("Reader %d is reading\n", id);

    sem_wait(&rmutex);          // Lock to update reader_count
    reader_count--;
    if (reader_count == 0) {    // Last reader unlocks the resource
        sem_post(&resource);
    }
    sem_post(&rmutex);          // Unlock after updating reader_count

    return NULL;
}

void* writer(void* arg) {
    int id = *((int*)arg);

    sem_wait(&resource);        // Writer locks the resource

    // Writing section
    printf("Writer %d is writing\n", id);

    sem_post(&resource);        // Writer unlocks the resource
    return NULL;
}

int main() {
    pthread_t r1, r2, w1, w2;
    int id1 = 1, id2 = 2;

    sem_init(&resource, 0, 1);  // Initialize resource semaphore
    sem_init(&rmutex, 0, 1);    // Initialize mutex for reader count

    // Create reader and writer threads
    pthread_create(&r1, NULL, reader, &id1);
    pthread_create(&w1, NULL, writer, &id1);
    pthread_create(&r2, NULL, reader, &id2);
    pthread_create(&w2, NULL, writer, &id2);

    // Wait for threads to finish
    pthread_join(r1, NULL);
    pthread_join(w1, NULL);
    pthread_join(r2, NULL);
    pthread_join(w2, NULL);

    // Destroy semaphores
    sem_destroy(&resource);
    sem_destroy(&rmutex);

    return 0;
}
