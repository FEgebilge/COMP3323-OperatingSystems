#include <stdio.h>
#include <pthread.h>

pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex for protecting the counter

int water_level = 0;

void *filler(void *arg){
    if (water_level <= 20){
        pthread_mutex_lock(&counter_mutex); // Lock the mutex before accessing the shared resource
        while (water_level < 100){
            water_level += 10;
            printf("Filler worked, Water level is: %d\n", water_level);
        }
        pthread_mutex_unlock(&counter_mutex); // Unlock the mutex after accessing the shared resource
        pthread_exit(NULL);
    }
}

void *drainer(void *arg){
        pthread_mutex_lock(&counter_mutex); // Lock the mutex before accessing the shared resource
        if (water_level > 0){ 
            water_level -= 10; 
            printf("Drainer worked, Water level is: %d\n", water_level);
        }
        pthread_mutex_unlock(&counter_mutex); // Unlock the mutex after accessing the shared resource
        pthread_exit(NULL);
}


int main()
{
    pthread_t thread1, thread2;
    for(int i = 0; i < 100; i++){
        pthread_create(&thread1, NULL, filler, NULL); // Create threads
        pthread_create(&thread2, NULL, drainer, NULL);
        pthread_join(thread1, NULL); // Join threads
        pthread_join(thread2, NULL);
    }
    pthread_mutex_destroy(&counter_mutex); // Clean up the mutex
    return 0;
}
