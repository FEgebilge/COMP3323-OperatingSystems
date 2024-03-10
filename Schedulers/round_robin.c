#include <stdio.h>

#define MAX_NUM_PROCESSES 16

typedef struct {
    int id; // Process Names
    char is_arrived; // 0 if not arrived, 1 if arrived use for checking arrival time
    int remaining_burst_time; // Remaining Time
    
    int arrival_time; // Arrival Time
    int burst_time; // Burst Time
    int completion_time; // Completion Time
    int waiting_time; // Waiting Time
    int turnaround_time; // Turnaround Time
} Process;

typedef struct {
    Process processes[MAX_NUM_PROCESSES];
    int rear;
    int front;
} ReadyQueue;



// Circular Queue Operations for implementation of Ready Queue
Process dequeue(ReadyQueue *queue); // Remove the process from the front of the queue
int is_empty(ReadyQueue *queue); // Check if the queue is empty
int is_full(ReadyQueue *queue); // Check if the queue is full
void enqueue(ReadyQueue *queue, Process process); // Add the process to the rear of the queue


void check_arrival_time(ReadyQueue *queue, Process *processes, int time, int num_processes); // Check the arrival time of the processes and enqueue them if they have arrived
void round_robin(ReadyQueue *queue, Process *processes, int quantum, int num_processes); // Round Robin Scheduling Algorithm
void calculate_metrics(Process *processes, int num_processes); // Calculate Turnaround Time, Waiting Time
void run_process(int *time, int quantum, Process *cur_process); // Run the process for the given quantum or remaining burst time

int main() {
    // ININIALIZE THE QUEUE
    ReadyQueue queue;
    queue.rear = 0;
    queue.front = 0;

    // INITIALIZE THE PROCESSES
    Process processes[MAX_NUM_PROCESSES];
    int num_processes;
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    for(int i = 0; i < num_processes; i++) {
        processes[i].id = i;
        printf("Enter the arrival time for process %d: ", processes[i].id);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter the burst time for process %d: ", processes[i].id);
        scanf("%d", &processes[i].burst_time);
        processes[i].is_arrived = 0;
    }

    // ROUND ROBIN SCHEDULING ALGORITHM
    int quantum;
    printf("Enter the quantum: ");
    scanf("%d", &quantum);

    // IMPLEMENT ROUND ROBIN SCHEDULING ALGORITHM
    round_robin(&queue, processes, quantum, num_processes);

    // CALCULATE TURNAROUND TIME, WAITING TIME
    calculate_metrics(processes, num_processes);
}

void enqueue(ReadyQueue *queue, Process process) {
    if (is_full(queue)) {
        printf("Queue is full\n");
        return;
    }
    queue->processes[queue->rear] = process;
    queue->rear = (queue->rear + 1) % MAX_NUM_PROCESSES;
}


Process dequeue(ReadyQueue *queue) {
    if (is_empty(queue)) {
        printf("Queue is empty\n");
        // Return a default process or handle the error appropriately
        Process emptyProcess;
        emptyProcess.id = -1;
        return emptyProcess;
    }
    Process process = queue->processes[queue->front];
    queue->front = (queue->front + 1) % MAX_NUM_PROCESSES;
    return process;
}

int is_empty(ReadyQueue *queue) {
    return queue->front == queue->rear;
}

int is_full(ReadyQueue *queue) {
    return (queue->rear + 1) % MAX_NUM_PROCESSES == queue->front;
}

// check arrival time for processes
// If processed is not arrived and its arrival time is less than or equal to the current time, enqueue the process to ReadyQueue
void check_arrival_time(ReadyQueue *queue, Process *processes, int time, int num_processes) {
    for (int i = 0; i < num_processes; i++) {
        if (processes[i].is_arrived == 0 && processes[i].arrival_time <= time) {
            processes[i].is_arrived = 1;
            enqueue(queue, processes[i]);
        }
    }
}

void run_process(int *cur_time, int burst_time, Process *cur_process) {
    int start_time = *cur_time;
    *cur_time += burst_time;
    int end_time = *cur_time;
    printf("P%d [%d - %d] | ", cur_process->id, start_time, end_time);
}

// Round Robin Scheduling Algorithm with Arrival Time
void round_robin(ReadyQueue *queue, Process *processes, int quantum, int num_processes) {
    int cur_time = 0, finished_processes = 0;
    Process cur_process;
    int i = 0;
    int remaining_processes = num_processes;
    int time = 0;


    // Initialize remaining burst time for each process to burst time
    for (int i = 0; i < num_processes; i++) {
        processes[i].remaining_burst_time = processes[i].burst_time;
    }

    // Initialize the queue with the first processes by checking the arrival time of the processes.
    check_arrival_time(queue, processes, cur_time, num_processes);

   // Start of the Round Robin Algorithm. Create a loop that runs until all processes are finished. 
while (finished_processes < num_processes) {
    if (!is_empty(queue)) {
        cur_process = dequeue(queue);
        if (cur_process.remaining_burst_time <= quantum) {
            run_process(&cur_time, cur_process.remaining_burst_time, &cur_process);
            cur_process.completion_time = cur_time;
            cur_process.turnaround_time = cur_process.completion_time - cur_process.arrival_time;
            cur_process.waiting_time = cur_process.turnaround_time - cur_process.burst_time;
            processes[cur_process.id] = cur_process;
            finished_processes++;
        } else {
            run_process(&cur_time, quantum, &cur_process);
            cur_process.remaining_burst_time -= quantum;
            check_arrival_time(queue, processes, cur_time, num_processes);
            enqueue(queue, cur_process);
        }
    } else {
        cur_time++;
        check_arrival_time(queue, processes, cur_time, num_processes);
    }
}
   
   // First check if ReadyQueue is empty or not.
   // If it is NOT empty, then
   // - Dequeue the process and get the process from the front of the queue which is your current process.
   // - When you get current process. Compare process's remaining burst time with the quantum time.
   // There will be 2 cases here:
   //      1. If the remaining burst time of the process is less than or equal to the quantum, this means processed will be finished.
                // 1.1 Run the process by the remaining burst time.
                // 1.2 Update the remaining burst time of the process and the completion time (CT) of the process. Use CT for calculating TAT and WT.
                // 1.3 Add the process to the finished_processes. The process is finished.
   //      2. If the remaining burst time of the process is greater than the quantum, then
                // Run the process by the quantum time.
                // 2.1 Update remaining burst time of the current process.
                // 2.2 Need to enqueue the process to the ReadyQueue again but before doing that need to check the arrival time of the processes and enqueue them if they have arrived.

   // Increment current time.
   // If the ReadyQueue is empty, need to check the arrival time of the processes and enqueue them if they have arrived.
    
}



// Calculate TAT, WT
void calculate_metrics(Process *processes, int num_processes) {
    for(int i = 0; i < num_processes; i++) {
    processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }

    printf("\n\n");

    printf("PID\t | \tAT\t | \tBT\t | \tCT\t | \tTAT\t | \tWT\t |\n");

    float avgWT = 0;
    float avgTAT = 0;
    for(int i = 0; i < num_processes; i++) {
        printf("P%d\t | \t%d\t | \t%d\t | \t%d\t | \t%d\t | \t%d\t |\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time, processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
        avgTAT += processes[i].turnaround_time;
        avgWT += processes[i].waiting_time;
    }
    avgTAT /= num_processes;
    avgWT /= num_processes;
 
    printf("\n\n");
    printf("Average Waiting Time: %.2f\n",avgWT);
    printf("Average Turnaround Time: %.2f\n", avgTAT);
    printf("\n\n");
}

