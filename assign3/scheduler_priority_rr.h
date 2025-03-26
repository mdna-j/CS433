/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority_rr.h
 * @author Jose Medina
 * @brief This Scheduler class implements the Priority RR scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#ifndef ASSIGN3_SCHEDULER_PRIORITY_RR_H
#define ASSIGN3_SCHEDULER_PRIORITY_RR_H

#include "scheduler.h"
#include "pcb.h"
#include <vector>

class SchedulerPriorityRR : public Scheduler {
private:
    int m_time_quantum;                 // Time quantum for Round-Robin
    std::vector<PCB> process_queue_;    // Queue of processes
public:
    /**
     * @brief Construct a new SchedulerPriorityRR object
     * 
     * @param time_quantum Time quantum for round-robin scheduling
     */
    SchedulerPriorityRR(int time_quantum = 10);

    /**
     * @brief Destroy the SchedulerPriorityRR object
     */
    ~SchedulerPriorityRR() override;

    /**
     * @brief Initializes the scheduler with a list of processes
     * @param process_list The list of processes to schedule
     */
    void init(std::vector<PCB>& process_list) override;

    /**
     * @brief Runs the simulation, alternating between priority and round-robin scheduling
     */
    void simulate() override;

    /**
     * @brief Prints the results of the scheduling simulation
     */
    void print_results() override;

private:
    /**
     * @brief Sorts processes by priority
     * @param process_list List of processes
     */
    void sort_by_priority(std::vector<PCB>& process_list);

    /**
     * @brief Simulates round-robin scheduling
     * @param current_time Current simulation time
     */
    void round_robin_simulation(unsigned int& current_time);

    /**
     * @brief Simulates priority scheduling
     * @param current_time Current simulation time
     */
    void priority_simulation(unsigned int& current_time);
};

#endif // ASSIGN3_SCHEDULER_PRIORITY_RR_H