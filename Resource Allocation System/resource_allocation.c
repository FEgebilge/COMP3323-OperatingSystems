#include <stdio.h>
#include <stdbool.h>

#define P 8   // Number of processes (job types)
#define R 5   // Number of resources (Computers, Desks, Printers, Conference Rooms, Projectors)

// Function prototypes
void calculateNeed(int need[P][R], int max[P][R], int allot[P][R]);
bool isSafe(int processes[], char ** jobTypes, int avail[], int max[][R], int allot[][R]);
void printResult(int safeSeq[P], char** jobTypes);

int main() {
    int process_ids[] = {0, 1, 2, 3, 4, 5, 6, 7};  // Job types IDs
    char** jobTypes = (char*[]){"Software Developer", "Graphic Designer", "Sales Representative", "HR Manager", "Accountant", "Marketing Analyst", "Customer Support Specialist", "Project Manager"};

    // Available instances of resources. Find minimum resources required for each job type.
    // ???
    int avail[R] = {5, 0, 5, 0, 2};
    


    // Maximum R that can be allocated to processes. Look the table in the question for assignment.
    // ???
    int max[P][R] = {
    {10, 4, 1, 0, 0},  // Software Developer
    {5, 1, 8, 0, 1},  // Graphic Designer
    {1, 1, 2, 1, 2},  // Sales Representative
    {2, 2, 1, 0, 1},  // HR Manager
    {2, 1, 1, 1, 0},  // Accountant
    {2, 2, 3, 3, 2},  // Marketing Analyst
    {5, 8, 1, 0, 0},  // Customer Support Specialist
    {1, 2, 1, 2, 2}   // Project Manager
    };
    

    // Resources currently allocated to processes. Look the table in the question for assignment.
    // ???
    int allot[P][R] = {
    {0, 0, 0, 0, 2},  // Software Developer
    {1, 0, 1, 0, 0},  // Graphic Designer
    {1, 1, 0, 1, 0},  // Sales Representative
    {0, 1, 1, 1, 0},  // HR Manager
    {1, 1, 0, 0, 0},  // Accountant
    {1, 2, 0, 0, 0},  // Marketing Analyst
    {1, 2, 1, 0, 0},  // Customer Support Specialist
    {0, 1, 0, 1, 0}   // Project Manager
    }; 

    // Check system state
    // ???
    int need[P][R];
    calculateNeed(need, max, allot);
    if (isSafe(process_ids, jobTypes, avail, max, allot)) {
        printf("System is in a safe state.\n");
        printResult(process_ids, jobTypes);
    } else {
        printf("System is not in a safe state.\n");
    }
    return 0;
}

// Function to calculate need matrix
void calculateNeed(int need[P][R], int max[P][R], int allot[P][R]) {
    // Write your code here
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allot[i][j];

}

// Print result
void printResult(int safeSeq[P], char** jobTypes) {
    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < P; i++)
        printf("P%d ", safeSeq[i]);
    
    printf("\n\nOrder of job types: ");
    for (int i = 0; i < P; i++)
        printf("\n%d. %s", i + 1, jobTypes[safeSeq[i]]);
    printf("\n");
}

// Function to find the system is in a safe state or not
bool isSafe(int process_ids[], char** jobTypes, int avail[], int max[][R], int allot[][R]) {
    // Write your code here
    int work[R];
    bool finish[P] = {false};
    int safeSeq[P];
    int need[P][R];

    // Calculate need matrix
    calculateNeed(need, max, allot);
    int count = 0;

    // Initialize work array with available resources
    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }

    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                bool canExecute = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        canExecute = false;
                        break;
                    }
                }
                if (canExecute) {
                    // Execute the process
                    for (int j = 0; j < R; j++) {
                        work[j] += allot[i][j];
                    }
                    safeSeq[count] = process_ids[i];
                    finish[i] = true;
                    count++;
                    found = true;
                    break;  // Exit inner loop once a process is executed
                }
            }
        }
        if (!found) {
            break;
        }
    }
    if (count < P) {
        return false; // System is not in a safe state
    } else {
        return true; // System is in a safe state
    }
}
