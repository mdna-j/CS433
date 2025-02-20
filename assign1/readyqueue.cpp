#include <iostream>
#include "readyqueue.h"
#include "pcb.h"

using namespace std;

// Purpose: Constructor for the ReadyQueue class. Initializes queue properties.
ReadyQueue::ReadyQueue() {
    capacity = 100;  // Default maximum capacity
    heap = new PCB*[capacity];  // Dynamically allocate memory for PCB pointers
    count = 0;  // Initialize the queue size to 0
}

// Purpose: Destructor - Frees dynamically allocated memory.
ReadyQueue::~ReadyQueue() {
    delete[] heap;  // Deallocate memory to prevent leaks
}

// Purpose: Adds a PCB to the ready queue and sets its state to READY.
void ReadyQueue::addPCB(PCB *pcbPtr) {
    if (count == capacity) {  // Check if queue is full
        cout << "Queue is full!" << endl;
        return;
    }
    heap[count] = pcbPtr;  // Add new PCB to the end of the heap
    heap[count]->setState(ProcState::READY);  // Set PCB state to READY
    bubbleUp(count);  // Restore heap order
    count++;  // Increase queue size
}

// Purpose: Removes and returns the highest-priority PCB, setting its state to RUNNING.
PCB* ReadyQueue::removePCB() {
    if (count == 0) {  // Check if queue is empty
        cout << "Queue is empty!" << endl;
        return nullptr;
    }

    PCB* highestPriorityPCB = heap[0];  // Store highest-priority PCB
    heap[0] = heap[count - 1];  // Move last PCB to the root
    count--;  // Reduce queue size
    bubbleDown(0);  // Restore heap order
    highestPriorityPCB->setState(ProcState::RUNNING);  // Set PCB state to RUNNING
    return highestPriorityPCB;  // Return removed PCB
}

// Purpose: Moves a PCB down the heap to maintain heap order (used in removePCB).
void ReadyQueue::bubbleDown(int index) {
    int leftChild = 2 * index + 1;  // Left child index
    int rightChild = 2 * index + 2;  // Right child index
    int largest = index;  // Assume current index is the largest

    // Compare left child with the current largest
    if (leftChild < count && heap[leftChild]->getPriority() > heap[largest]->getPriority()) {
        largest = leftChild;
    }
    // Compare right child with the current largest
    if (rightChild < count && heap[rightChild]->getPriority() > heap[largest]->getPriority()) {
        largest = rightChild;
    }

    // Swap if the largest is not the current index
    if (largest != index) {
        swap(heap[index], heap[largest]);
        bubbleDown(largest);  // Recursively bubble down
    }
}

// Purpose: Moves a PCB up the heap to maintain heap order (used in addPCB).
void ReadyQueue::bubbleUp(int index) {
    int parentIndex = (index - 1) / 2;  // Parent index calculation

    // Swap with parent if the priority is higher
    if (index > 0 && heap[index]->getPriority() > heap[parentIndex]->getPriority()) {
        swap(heap[index], heap[parentIndex]);
        bubbleUp(parentIndex);  // Recursively bubble up
    }
}


ReadyQueue::ReadyQueue(const ReadyQueue& other) {
    // Purpose: Copies heap memory from another ReadyQueue to prevent shallow copies.
    capacity = other.capacity;
    count = other.count;
    
    // Allocate new memory for the heap
    heap = new PCB*[capacity];
    
    // Copy each PCB pointer (deep copy)
    for (int i = 0; i < count; i++) {
        heap[i] = new PCB(*other.heap[i]);  // Create a new PCB object by copying existing one
    }
}


ReadyQueue& ReadyQueue::operator=(const ReadyQueue& other) {
    // Purpose: Clears current heap memory and copies from another ReadyQueue.

    if (this == &other) {
        return *this;  // Self-assignment check
    }

    // Free existing heap memory
    for (int i = 0; i < count; i++) {
        delete heap[i];
    }
    delete[] heap;

    // Copy new values
    capacity = other.capacity;
    count = other.count;
    heap = new PCB*[capacity];

    for (int i = 0; i < count; i++) {
        heap[i] = new PCB(*other.heap[i]);  // Deep copy each PCB
    }

    return *this;
}

// Purpose: Returns the number of PCBs in the queue.
int ReadyQueue::size() {
    return count;  // Return current queue size
}

// Purpose: Displays all PCBs currently in the queue.
void ReadyQueue::displayAll() {
    cout << "Display Processes in ReadyQueue:" << endl;
    for (int i = 0; i < count; i++) {
        heap[i]->display();  // Call display function of each PCB
    }
}
