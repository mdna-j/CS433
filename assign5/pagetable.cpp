/**
* Assignment 5: Page replacement algorithms
 * @file pagetable.cpp
 * @author Jose Medina
 * @brief This class represents a traditional pagetable data structure.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code


#include "pagetable.h"
#include <cstddef>   


// Constrcutor
PageTable::PageTable(int num_pages) {
    pages.resize(num_pages);

    for(int i = 0; i < num_pages; ++i){
        pages[i].valid = false;                  // initalizing the validity of each page in the table
        pages[i].dirty = false;                  // Not used in this assignment, but included for completeness
        pages[i].frame_num = -1;                 // -1 indicates no frame is assigned yet
    }
}

// Destructor
PageTable::~PageTable() {
}

int PageTable::size() {
    return static_cast<int>(pages.size());                        // returns the page size for (Algorithm functions)
}