/**
* Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.cpp
 * @author Jose Medina
 * @brief This Scheduler class implements the FCSF scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler_fcfs.h"
#include "pcb.h"

// member functions init, print_results, and simulate here

    /**
    * @brief Constructor for a new SchedulerFCFS object
    */
SchedulerFCFS::SchedulerFCFS() {}           // constructor for SchedulerFCFS

    /**
    * @brief Deconstructor for a new SchedulerFCFS object
    */
SchedulerFCFS::~SchedulerFCFS() {}          // deconstructor for SchedulerFCFS

    /**
     * @brief This function is called once before the simulation starts.
     *        It is used to initialize the scheduler.
     * @param process_list The list of processes in the simulation.
     */
void SchedulerFCFS::init(std::vector<PCB>& process_list) {
    this->process_queue_ = process_list;    // loads the process_list into this class process_list (process_queue_)
}

    /**
     * @brief This function simulates the scheduling of processes in the ready queue.
     *        It stops when all processes are finished.
     */
void SchedulerFCFS::simulate() {
    unsigned int current_time = 0;          // start time for scheduling (elapsed time)
    int i = 0;                              // current index for while loop (iterating through process)

    while(i < process_queue_.size()){       // if i < the size of the process queue
        // Calculate wait time
        process_queue_[i].wait_time = current_time;  // wait time is the current time (since all arrive at 0)
        
        cout << "Running Process " << process_queue_[i].name << " for " << process_queue_[i].burst_time << " time units " << endl;

        current_time += process_queue_[i].burst_time;     // update current time after executing the process
        
        process_queue_[i].turnaround_time = current_time; // turnaround time is completion time
        i++;                                              // increments the current process in the queue                               
    }
}

    /**
     * @brief This function is called once after the simulation ends.
     *        It is used to print out the results of the simulation.
     */
void SchedulerFCFS::print_results() {
    unsigned int total_wait_time = 0;                     // calculation for total wait time
    unsigned int total_turnaround_time = 0;               // calculation for total turnaround time
    int i = 0;                                            // current index for while loop (iterating through process)

    while(i < process_queue_.size()){                     // if i < the size of the process queue
        cout << process_queue_[i].name << " turn-around time = " << process_queue_[i].turnaround_time << ", waiting time = " << process_queue_[i].wait_time << endl;
        total_wait_time += process_queue_[i].wait_time;   // adds all the processes wait times into the total wait time
        total_turnaround_time += process_queue_[i].turnaround_time; // adds all the processes turnaround times into the total turnaround time
        i++;                                                         // increments the current process in the queue                               
    }

    double average_wait_time = (double)(total_wait_time) / process_queue_.size();                   // gets the average of all the wait times
    double average_turnaround_time = (double)(total_turnaround_time) / process_queue_.size();       // gets the average of all the turnaround times

    cout << "Average turn-around time = " << average_turnaround_time << ", Average waiting time: " << average_wait_time << endl;
}
