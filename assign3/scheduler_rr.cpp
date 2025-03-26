/**
 * @file scheduler_rr.h
 * @author Jose Medina
 * @brief This Scheduler class implements the RoundRobin (RR) scheduling algorithm.
 * @version 0.1
 */
// You must complete all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code.

#include "scheduler_rr.h"
#include <vector>

// Member functions init, print_results, and simulate are defined here.

    /**
     * @brief Construct a new SchedulerRR object.
     * 
     * @param time_quantum The time quantum for the RoundRobin scheduling.
     */
SchedulerRR::SchedulerRR(int time_quantum){
    this->m_time_quantum = time_quantum;    // Set the time quantum for the scheduler.
}

    /**
     * @brief Destroy the SchedulerRR object.
     */
SchedulerRR::~SchedulerRR() {}

    /**
     * @brief This function is called once before the simulation starts.
     *        It is used to initialize the scheduler.
     * 
     * @param process_list The list of processes in the simulation.
     */
void SchedulerRR::init(std::vector<PCB>& process_list){
    this->process_queue_ = process_list;    // Initialize the process queue with the given process list.
}

    /**
     * @brief This function simulates the scheduling of processes in the ready queue.
     *        It stops when all processes are finished.
     */
void SchedulerRR::simulate() {
    unsigned int current_time = 0;                    // Track the current time in the simulation.
    std::vector<PCB> process_queue = process_queue_;  // Local copy of the process queue for simulation.
    int i = 0;                                        // Index for iterating through the process queue.

    while (!process_queue.empty()) {                  // Continue until all processes are finished.
        PCB &current_process = process_queue[i];      // Get the current process from the queue.

        if (current_process.burst_time > m_time_quantum) {  // If burst time is greater than the time quantum.
            cout << "Running Process " << current_process.name << " for " << m_time_quantum << " time units\n";

            current_time += m_time_quantum;                 // Increment current time by the time quantum.
            current_process.burst_time -= m_time_quantum;   // Decrease burst time by the time quantum.
            
            // Move the process to the end of the queue to continue later.
            process_queue.push_back(current_process);    // Add the current process to the end of the queue.
            process_queue.erase(process_queue.begin() + i);  // Remove the process from the front of the queue.
        } else {                                           // If burst time is less than or equal to the time quantum.
            cout << "Running Process " << current_process.name << " for " << current_process.burst_time << " time units\n";

            current_time += current_process.burst_time;    // Add burst time to the current time.
            current_process.wait_time = current_time - (process_queue_[current_process.id].burst_time);  // Calculate wait time.
            current_process.turnaround_time = current_time; // Set the turnaround time.

            process_queue_[current_process.id] = current_process;  // Update the original queue with the modified process.
            
            process_queue.erase(process_queue.begin() + i);  // Remove the completed process from the queue.
        }
    }
}

    /**
     * @brief This function is called once after the simulation ends.
     *        It is used to print out the results of the simulation.
     */
void SchedulerRR::print_results() {
    unsigned int total_wait_time = 0;           // Calculate total wait time.
    unsigned int total_turnaround_time = 0;     // Calculate total turnaround time.
    int i = 0;                                  // Index for iterating through the process queue.

    while(i < process_queue_.size()){           // Iterate through the process queue.
        cout << process_queue_[i].name << " turn-around time = " << process_queue_[i].turnaround_time 
             << ", waiting time = " << process_queue_[i].wait_time << endl;

        total_wait_time += process_queue_[i].wait_time;             // Add wait time to the total wait time.
        total_turnaround_time += process_queue_[i].turnaround_time; // Add turnaround time to the total turnaround time.
        i++;                                                        // Move to the next process in the queue.  
    }

    // Calculate and print average wait time and turnaround time.
    double average_wait_time = (double)(total_wait_time) / process_queue_.size();               
    double average_turnaround_time = (double)(total_turnaround_time) / process_queue_.size();   

    cout << "Average turn-around time = " << average_turnaround_time 
         << ", Average waiting time: " << average_wait_time << endl;
}
