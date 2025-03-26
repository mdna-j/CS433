/**
 * @file scheduler_sjf.cpp
 * @author Jose Medina
 * @brief Implementation of the Shortest Job First (SJF) scheduling algorithm.
 */
// You must complete all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code.

#include "scheduler_sjf.h"
#include "pcb.h"
#include <vector>

// Member functions init, print_results, and simulate here

/**
 * @brief Construct a new SchedulerSJF object.
 */
SchedulerSJF::SchedulerSJF() {}

/**
 * @brief Destroy the SchedulerSJF object.
 */
SchedulerSJF::~SchedulerSJF() {}

/**
 * @brief This function is called once before the simulation starts.
 *        It is used to initialize the scheduler.
 * @param process_list The list of processes in the simulation.
 */
void SchedulerSJF::init(std::vector<PCB>& process_list) {
    this->process_queue_ = process_list; // Loads the process_list into this class' process_queue_
}

/**
 * @brief This function simulates the scheduling of processes in the ready queue.
 *        It stops when all processes are finished.
 */
void SchedulerSJF::print_results() {
    unsigned int total_wait_time = 0;           // Calculation for total wait time
    unsigned int total_turnaround_time = 0;     // Calculation for total turnaround time
    int i = 0;                                  // Current index for while loop (iterating through processes)

    while(i < process_queue_.size()) {           // If i < the size of the process queue
        std::cout << process_queue_[i].name 
                  << " turn-around time = " << process_queue_[i].turnaround_time 
                  << ", waiting time = " << process_queue_[i].wait_time 
                  << std::endl;
        
        total_wait_time += process_queue_[i].wait_time;      // Adds all the processes' wait times into the total wait time
        total_turnaround_time += process_queue_[i].turnaround_time; // Adds all the processes' turnaround times into the total turnaround time
        i++;                                                            // Increments the current process in the queue                               
    }

    // Calculate average wait time and turnaround time
    double average_wait_time = static_cast<double>(total_wait_time) / process_queue_.size();
    double average_turnaround_time = static_cast<double>(total_turnaround_time) / process_queue_.size();

    std::cout << "Average turn-around time = " << average_turnaround_time 
              << ", Average waiting time: " << average_wait_time << std::endl;
}

/**
 * @brief This function simulates the scheduling of processes in the ready queue.
 *        It stops when all processes are finished.
 */
void SchedulerSJF::simulate() {
    sort(process_queue_);  // Sorts the process queue by burst time
    unsigned int current_time = 0; // Start time for scheduling (elapsed time)
    int i = 0; // Current index for while loop (iterating through processes)

    while(i < process_queue_.size()) {  // If i < the size of the process queue
        process_queue_[i].wait_time = current_time; // Wait time is the current time (since all arrive at 0)
        
        // Process execution simulation
        std::cout << "Running Process " << process_queue_[i].name 
                  << " for " << process_queue_[i].burst_time 
                  << " time units " << std::endl;

        current_time += process_queue_[i].burst_time;  // Update current time after executing the process
        process_queue_[i].turnaround_time = current_time; // Turnaround time is the completion time
        i++;  // Increments the current process in the queue                               
    }
}

/**
 * @brief This function sorts the process queue based on burst time (Shortest Job First).
 * @param process_list The list of processes to be sorted.
 */
void SchedulerSJF::sort(std::vector<PCB>& process_list) {
    for (int i = 1; i < process_list.size(); ++i) {  // Start from the second PCB element
        PCB current = process_list[i];
        int j = i - 1;  // Set j to the first PCB element

        // Sort the process list in ascending order of burst time
        while (j >= 0 && process_list[j].burst_time > current.burst_time) {
            process_list[j + 1] = process_list[j];  // Move the larger element to the right
            j = j - 1;
        }
        process_list[j + 1] = current;  // Place the current process in the correct sorted position
    }
}
