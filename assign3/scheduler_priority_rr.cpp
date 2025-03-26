/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority_rr.cpp
 * @author Jose Medina
 * @brief This Scheduler class implements the Priority RR scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code


#include "scheduler_priority_rr.h"
#include "pcb.h"
#include <iostream>
#include <algorithm>

using namespace std;

SchedulerPriorityRR::SchedulerPriorityRR(int time_quantum) : m_time_quantum(time_quantum) {}

SchedulerPriorityRR::~SchedulerPriorityRR() {}

void SchedulerPriorityRR::init(std::vector<PCB>& process_list) {
    process_queue_ = process_list; // Initialize the process queue
}

void SchedulerPriorityRR::simulate() {
    unsigned int current_time = 0;  // Current simulation time
    // Step 1: Run priority scheduling first
    priority_simulation(current_time);
    // Step 2: Use Round-Robin scheduling for remaining tasks
    round_robin_simulation(current_time);
}

void SchedulerPriorityRR::print_results() {
    unsigned int total_wait_time = 0;
    unsigned int total_turnaround_time = 0;
    for (const auto& process : process_queue_) {
        cout << "Process " << process.id << ": " << process.name
             << " has priority " << process.priority 
             << " and burst time " << process.burst_time << endl;
        total_wait_time += process.wait_time;
        total_turnaround_time += process.turnaround_time;
    }

    double average_wait_time = static_cast<double>(total_wait_time) / process_queue_.size();
    double average_turnaround_time = static_cast<double>(total_turnaround_time) / process_queue_.size();
    cout << "Average turn-around time = " << average_turnaround_time
         << ", Average waiting time: " << average_wait_time << endl;
}


void SchedulerPriorityRR::sort_by_priority(std::vector<PCB>& process_list) {
    // Sort processes by priority using insertion sort
    for (int i = 1; i < process_list.size(); ++i) {
        PCB current = process_list[i];
        int j = i - 1;
        while (j >= 0 && process_list[j].priority < current.priority) {
            process_list[j + 1] = process_list[j];
            --j;
        }
        process_list[j + 1] = current;
    }
}

void SchedulerPriorityRR::priority_simulation(unsigned int& current_time) {
    // Sort processes by priority
    sort_by_priority(process_queue_);
    for (auto& process : process_queue_) {
        process.wait_time = current_time;
        cout << "Running Process " << process.name << " for " << process.burst_time << " time units\n";
        current_time += process.burst_time;
        process.turnaround_time = current_time;
    }
}

void SchedulerPriorityRR::round_robin_simulation(unsigned int& current_time) {
    vector<PCB> process_queue_copy = process_queue_;
    int i = 0;
    while (!process_queue_copy.empty()) {
        PCB& current_process = process_queue_copy[i];
        if (current_process.burst_time > m_time_quantum) {
            cout << "Running Process " << current_process.name << " for " << m_time_quantum << " time units\n";
            current_time += m_time_quantum;
            current_process.burst_time -= m_time_quantum;
            process_queue_copy.push_back(current_process); // Re-queue process
            process_queue_copy.erase(process_queue_copy.begin() + i);
        } else {
            cout << "Running Process " << current_process.name << " for " << current_process.burst_time << " time units\n";
            current_time += current_process.burst_time;
            current_process.wait_time = current_time;
            current_process.turnaround_time = current_time;
            process_queue_copy.erase(process_queue_copy.begin() + i);
        }
    }
}