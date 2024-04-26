# Resource Allocation System

This repository contains a resource allocation system implemented in C. The system manages resource allocation for various job types within an organization to ensure efficient utilization of resources and prevent deadlock situations.

## Overview

The resource allocation system consists of a set of processes (job types) and a set of resources. Each process requires a certain number of resources to execute, and the system must allocate these resources in a manner that prevents deadlock and ensures that all processes can complete their execution safely.

## Features

- **Process Management**: The system manages multiple job types, each with its resource requirements.
- **Resource Allocation**: Resources are allocated to processes based on their requirements and the availability of resources in the system.
- **Deadlock Avoidance**: The system employs a deadlock avoidance algorithm to ensure that resources are allocated in a manner that prevents deadlock situations.
- **Safety Check**: The system performs a safety check to determine if the current resource allocation state is safe or not.

## Getting Started

To compile and run the resource allocation system, follow these steps:

1. Clone the repository to your local machine:

```bash
git clone https://github.com/FEgebilge/resource-allocation-system.git
```

2. Navigate to the project directory:

```bash
cd resource-allocation-system
```

3. Compile the source code using a C compiler (e.g., GCC):

```bash
gcc -o resource_allocation resource_allocation.c
```

4. Run the executable:

```bash
./resource_allocation
```

## Usage

Upon running the executable, the system will output whether it is currently in a safe state or not. If it is in a safe state, it will display the safe sequence of processes and the corresponding job types.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

Feel free to customize this README file further to suit your project's specific details and requirements.
