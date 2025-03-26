/**
 * @file scheduler_priority.cpp
 * @author Jose Medina
 * @brief This Scheduler class implements the Priority scheduling algorithm.
 * @version 0.1
 */
// You must complete all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code.

#include "scheduler_priority.h"
#include "pcb.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// Member functions init, print_results, and simulate

/**
 * @brief Construct a new SchedulerPriority object
 */
SchedulerPriority::SchedulerPriority() {}

/**
 * @brief Destroy the SchedulerPriority object
 */
SchedulerPriority::~SchedulerPriority() {}

/**
 * @brief This function is called once before the simulation starts.
 *        It is used to initialize the scheduler.
 * @param process_list The list of processes in the simulation.
 */
void SchedulerPriority::init(std::vector<PCB>& process_list) {
    // Loads the process list into this class' process queue
    process_queue_ = process_list;
}

/**
 * @brief This function is called once after the simulation ends.
 *        It is used to print out the results of the simulation.
 */
void SchedulerPriority::print_results() {
    unsigned int total_wait_time = 0;           // Calculation for total wait time
    unsigned int total_turnaround_time = 0;     // Calculation for total turnaround time
    int i = 0;                                  // Current index for while loop (iterating through processes)

    // Iterate through each process in the queue and print the results
    while (i < process_queue_.size()) {
        cout << process_queue_[i].name 
             << " turn-around time = " << process_queue_[i].turnaround_time
             << ", waiting time = " << process_queue_[i].wait_time << endl;
        
        // Add individual process wait and turnaround times to the totals
        total_wait_time += process_queue_[i].wait_time;
        total_turnaround_time += process_queue_[i].turnaround_time;
        
        i++;  // Move to the next process
    }

    // Calculate the average wait time and turnaround time
    double average_wait_time = static_cast<double>(total_wait_time) / process_queue_.size();
    double average_turnaround_time = static_cast<double>(total_turnaround_time) / process_queue_.size();

    // Print the averages
    cout << "Average turn-around time = " << average_turnaround_time 
         << ", Average waiting time = " << average_wait_time << endl;
}

/**
 * @brief This function simulates the scheduling of processes in the ready queue.
 *        It stops when all processes are finished.
 */
void SchedulerPriority::simulate() {
    // Sort the process queue by priority
    sort(process_queue_);
    
    unsigned int current_time = 0;  // Start time for scheduling (elapsed time)
    int i = 0;  // Current index for while loop (iterating through processes)

    // Iterate through each process in the sorted queue
    while (i < process_queue_.size()) {
        process_queue_[i].wait_time = current_time;  // Set wait time as the current time
        
        // Print the process being run
        cout << "Running Process " << process_queue_[i].name 
             << " for " << process_queue_[i].burst_time << " time units" << endl;

        // Update the current time based on the process burst time
        current_time += process_queue_[i].burst_time;
        
        // Set turnaround time as the time at which the process finishes
        process_queue_[i].turnaround_time = current_time;
        
        i++;  // Move to the next process in the queue
    }
}

/**
 * @brief This function sorts the processes in the current list by priority.
 *        It stops when all processes are sorted.
 */
void SchedulerPriority::sort(std::vector<PCB>& process_list) {
    // Using insertion sort to sort the process list by priority
    for (int i = 1; i < process_list.size(); ++i) {
        PCB current = process_list[i];  // Store the current process
        int j = i - 1;  // Set j to the previous element

        // Shift processes with lower priority to the right
        while (j >= 0 && process_list[j].priority < current.priority) {
            process_list[j + 1] = process_list[j];  // Shift process
            j = j - 1;  // Move to the previous process
        }

        // Insert the current process at the correct position
        process_list[j + 1] = current;
    }
}
