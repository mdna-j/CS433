/**
 * Assignment 1: priority queue of processes
 * @file pcbtable.h
 * @author: Jose Medina
 * @brief This is the implementation file for the PCBTable class.
 * // You must complete all parts marked as "TODO". Delete "TODO" after you are done.
 * // Remember to add sufficient comments to your code.
 */

#include "pcbtable.h"
#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief Construct a new PCBTable object of the given size (number of PCBs)
 *
 * @param size: the capacity of the PCBTable
 */
PCBTable::PCBTable(int size) {
   // Purpose: Initializes the PCBTable with the given size, resizing the table and filling it with nullptr.
    table.resize(size, nullptr);
}

/**
 * @brief Destroy the PCBTable object. Make sure to delete all the PCBs in the table.
 */
PCBTable::~PCBTable() {
   // Purpose: Cleans up the dynamically allocated memory by deleting all the PCB objects and clearing the table.
    for (PCB* pcb : table) { 
        delete pcb;  // Delete each PCB object to free memory
    }
    table.clear();  // Clear the vector to remove all elements
}

/**
 * @brief Get the PCB at index "idx" of the PCBTable.
 *
 * @param idx: the index of the PCB to get
 * @return PCB*: pointer to the PCB at index "idx", or nullptr if out of bounds.
 */
PCB* PCBTable::getPCB(unsigned int idx) {
    // Purpose: Returns the PCB at the specified index, or nullptr if the index is out of bounds.
    if (table.size() <= idx) {
        return nullptr;  // Return nullptr if the index is invalid
    }
    return table[idx];  // Return the PCB at the given index
}

/**
 * @brief Add a PCB pointer to the PCBTable at index idx.
 *
 * @param pcb: the PCB to add
 * @param idx: the index where the PCB should be placed
 */
void PCBTable::addPCB(PCB *pcb, unsigned int idx) {
    // Purpose: Adds a PCB at the specified index. If the index is greater than the current size, it adds the PCB to the end.

    if (table.size() <= idx) {
        table.push_back(pcb);  // If index is out of range, add PCB at the end
    } else {
        table.insert(table.begin() + idx, pcb);  // Insert PCB at the specified index
    }
    pcb->display();  // Display PCB details after adding
}
