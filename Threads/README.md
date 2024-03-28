# Water Tank Simulation using Multithreading

This C program simulates the filling and draining of a water tank using multithreading. It demonstrates the use of pthreads for creating and managing threads and a mutex for synchronizing access to a shared resource.

### Getting Started

To compile the program, make sure you have a C compiler installed. You can compile the program using the following command:

```bash
gcc -o water_tank water_tank.c -pthread
```

After compiling, you can run the program by executing the generated executable:
```bash
 ./water_tank
 ``` 
 
 
# Producer-Consumer Problem Solution using Threads and Semaphores

This code provides a solution to the classic Producer-Consumer problem using threads and semaphores in C. In the Producer-Consumer problem, there are two types of threads: producers and consumers. Producers produce items and place them into a shared buffer, while consumers consume these items from the buffer.

## Dependencies
This code requires pthread.h for threading support.
It also uses semaphore.h for semaphore implementation.
Standard input/output operations are used, hence stdio.h.
unistd.h is used for the sleep() function.
Functionality

The shared buffer has a fixed size defined by BUFFER_SIZE.
There are NUM_PRODUCERS producer threads and NUM_CONSUMERS consumer threads.
The buffer, in, and out variables are shared among all threads.
Semaphores empty and full are used to track the empty and full spaces in the buffer, respectively.
A mutex (pthread_mutex_t mutex) is employed for mutual exclusion while accessing the buffer.

## How It Works

Producers produce items and put them into the buffer. They wait if the buffer is full (sem_wait(&empty)), and signal that an item has been produced (sem_post(&full)).
Consumers consume items from the buffer. They wait if the buffer is empty (sem_wait(&full)), and signal that an item has been consumed (sem_post(&empty)).
Mutual exclusion is ensured while accessing the buffer using the mutex (pthread_mutex_lock(&mutex) and pthread_mutex_unlock(&mutex)).
Both producers and consumers sleep for 1 second between each operation to simulate real-world scenarios.

## Usage

Compile the code using a C compiler.
Execute the compiled binary.
## Notes

The code runs indefinitely until manually terminated.
Output statements indicate the actions performed by producers and consumers.
The print_buffer() function is provided for debugging purposes to display the current state of the buffer.
