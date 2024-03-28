#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 10
#define NUM_PRODUCERS 10
#define NUM_CONSUMERS 10


int buffer[BUFFER_SIZE]={0};  // Shared buffer
int in = 0;  // Buffer in pointer
int out = 0;  // Buffer out pointer

sem_t empty;  // Semaphore to track empty spaces in buffer
sem_t full;  // Semaphore to track filled spaces in buffer
pthread_mutex_t mutex;  // Mutex for mutual exclusion

void print_buffer(void) {
    for (int i = 0; i < BUFFER_SIZE; i++) {
        printf("%d\t", buffer[i]);
    }
    printf("\n");
}

void produce_item() {
    if(buffer[in] == 0){
    buffer[in]=1;
    in = (in + 1) % BUFFER_SIZE;  
    if(in == 0){
        printf("Producer produced item, placed on %d.shelf\n", BUFFER_SIZE);
    }
    else{
    printf("Producer produced item, placed on %d.shelf\n", in);
    }
    print_buffer();
    }
}

// Function to consume an item (prints the item)
void consume_item(){
    if(buffer[out] == 1){
    buffer[out]=0;
    out = (out + 1) % BUFFER_SIZE;  
    if(out == 0){
        printf("Consumer consumed item, placed on %d.shelf\n", BUFFER_SIZE);
    }
    else{
    printf("Consumer consumed item, placed on %d.shelf\n", out);
    }
    print_buffer();
    }
}


void *producer(void *arg) {
    while(1) {
        sem_wait(&empty);  // Wait if buffer is full
        pthread_mutex_lock(&mutex);  // Enter critical section
        produce_item();
        pthread_mutex_unlock(&mutex);  // Exit critical section
        sem_post(&full);  // Signal that an item has been produced
        sleep(1);
    }
}

void *consumer(void *arg) {
    while(1) {
        sem_wait(&full);  // Wait if buffer is empty
        pthread_mutex_lock(&mutex);  // Enter critical section
        consume_item();  // Remove item from buffer
        pthread_mutex_unlock(&mutex);  // Exit critical section
        sem_post(&empty);  // Signal that an item has been consumed
        sleep(1);
    }
}

int main() {
    pthread_t producer_threads[NUM_PRODUCERS];
    pthread_t consumer_threads[NUM_CONSUMERS];

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_create(&producer_threads[i], NULL, producer, NULL);
        pthread_create(&consumer_threads[i], NULL, consumer, NULL);
    }

    // Wait for producer and consumer threads to finish
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producer_threads[i], NULL);
        pthread_join(consumer_threads[i], NULL);
    }

    // Destroy semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}