/**
 * Assignment 1: priority queue of processes
 * @file pcb.h
 * @author Jose Medina
 * @brief This is the header file for the PCB class, a process control block.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to addPCB sufficient comments to your code

#pragma once
#include <iostream>
#include <string>
using namespace std;

/**
 * @brief A process control block (PCB) represents a process in the system.
 *        It contains the following fields:
 *        - process ID (PID)
 *        - process name
 *        - burst time
 *        - priority
 *        - arrival_time
 *        - wait_time
 *        - turnaround_time
 *        - remaining_time
 *        - completion_time
 */
class PCB {
public:
    // Name of the process
    string name;
    // The unique process ID
    unsigned int id;
    // The priority of a process. Larger number represents higher priority
    unsigned int priority;
    // The CPU burst time of the process
    unsigned int burst_time;
    // The arrival time of the process
    unsigned int arrival_time;
    // The wait time of the process
    unsigned int wait_time;
    // The turnaround time of the process
    unsigned int turnaround_time;
    // The remaining burst time for the process
    unsigned int remaining_time;
    // The completion time of the process
    unsigned int completion_time;

    /**
     * @brief Construct a new PCB object
     * @param name: The name of the process.
     * @param id: Unique ID for each process
     * @param priority: The priority of the process (range 1-50). Larger number means higher priority
     * @param burst_time: The burst time of the process
     */
    PCB(string name, unsigned int id = 0, unsigned int priority = 1, unsigned int burst_time = 0) {
        this->name = name;
        this->id = id;
        this->priority = priority;
        this->burst_time = burst_time;
        this->arrival_time = 0;
        this->wait_time = 0;
        this->turnaround_time = 0;
        this->remaining_time = burst_time;
        this->completion_time = 0; // Initialize completion_time to 0
    }

    /**
     * @brief Destructor for the PCB class.
     */
    ~PCB() {}

    /**
     * @brief Print the details of the PCB object.
     */
    void print() const {
        cout << "Process " << id << ": " << name << " has priority " << priority 
             << ", burst time " << burst_time /*<< ", remaining time " << remaining_time
             << ", completion time " << completion_time */ << endl;
    }
};