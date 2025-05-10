/**
* Assignment 5: Page replacement algorithms
 * @file replacement.cpp
 * @author Jose Medina
 * @brief A base class for different page replacement algorithms.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include <iostream>
#include <ostream>
#include "replacement.h"

// Constructor
Replacement::Replacement(int num_pages, int num_frames) : page_table(num_pages) 
{
    n_frames = num_frames;                  // makes local copy of num_frames
}

// Destructor
Replacement::~Replacement() {}

// Simulate a single page access 
// @return true if it's a page fault
bool Replacement::access_page(int page_num, bool is_write)
{
    n_references++;
    if(page_table[page_num].valid){                         // If the page table is valid, calls touch_page function
        touch_page(page_num);
        return false;
    }

    n_pagefaults++;
    if(n_frames > 0){                                       // If the page is not valid but free frames are available, it calls the load_page function.
        load_page(page_num);
        n_frames--;
    }
    else 
    {
        replace_page(page_num);                            // If the page is not valid and no free frames are available, it calls replace_page function.
        n_pagereplacements++;
    }
    
    return true;
}

// Print out statistics of simulation
void Replacement::print_statistics() const {
        std::cout << "Number of references: \t\t" << n_references << std::endl;
        std::cout << "Number of page faults: \t\t" << n_pagefaults << std::endl;
        std::cout << "Number of page replacements: \t" << n_pagereplacements << std::endl;
}