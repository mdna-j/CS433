/**
* Assignment 5: Page replacement algorithms
 * @file fifo_replacement.cpp
 * @author Jose Medina
 * @brief A class implementing the FIFO page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "fifo_replacement.h"
#include "pagetable.h"

FIFOReplacement::FIFOReplacement(int num_pages, int num_frames) : Replacement(num_pages, num_frames) {}

FIFOReplacement::~FIFOReplacement() {}

// Access an invalid page, but free frames are available
void FIFOReplacement::load_page(int page_num) {
    fifo.push(page_num);                                                    // pushes new page number into the queue
    page_table[page_num].valid = true;                                        // makes the valid bit as true
}

// Access an invalid page and no free frames are available
int FIFOReplacement::replace_page(int page_num) {
    int page = fifo.front();                                                 // accesses front of queue
    fifo.pop();                                                              // pops the front of the queue

    page_table[page].valid = false;                                          // valid bit set to false for the removed page
    page_table[page_num].valid = true;                                       // valid bit set to true for the new page
    page_table[page_num].frame_num = page_table[page].frame_num;

    fifo.push(page_num);                                                  // pushes new page to be into the queue at the back
    return page;
}