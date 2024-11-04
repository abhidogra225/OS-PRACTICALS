#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_ITERATIONS 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int shared_data;
int readers_ready = 0;

void *writer(void *arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        int random_number = rand() % 100; // Generate a random number

        pthread_mutex_lock(&mutex);
        shared_data = random_number;
        printf("\nWriter wrote: %d\n", shared_data);
        
        // Signal to readers that data is ready
        readers_ready = NUM_READERS;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);

        sleep(1); // Simulate some writing time
    }
    pthread_exit(NULL);
}

void *reader(void *arg) {
    int reader_id = *((int *)arg);
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        pthread_mutex_lock(&mutex);

        // Wait until the writer has updated the shared data
        while (readers_ready == 0) {
            pthread_cond_wait(&cond, &mutex);
        }

        // Read the shared data
        int data = shared_data;
        printf("Reader %d: Item READ from buffer: %d\n", reader_id, data);

        // Decrease the readers_ready count and signal writer if all readers have read the data
        readers_ready--;
        pthread_mutex_unlock(&mutex);

        sleep(1); // Simulate some reading time
    }
    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));
    pthread_t writer_thread, reader_threads[NUM_READERS];
    int reader_ids[NUM_READERS] = {1, 2, 3};

    pthread_create(&writer_thread, NULL, writer, NULL);
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_create(&reader_threads[i], NULL, reader, &reader_ids[i]);
    }

    pthread_join(writer_thread, NULL);
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(reader_threads[i], NULL);
    }

    // Clean up mutex and condition variable
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}
