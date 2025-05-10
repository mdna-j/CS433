/**
* Assignment 5: Page replacement algorithms
 * @file lifo_replacement.cpp
 * @author Jose Medina
 * @brief A class implementing the Last in First Out (LIFO) page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "lifo_replacement.h"

LIFOReplacement::LIFOReplacement(int num_pages, int num_frames) : Replacement(num_pages, num_frames) {}

LIFOReplacement::~LIFOReplacement() {}

// Access an invalid page, but free frames are available
void LIFOReplacement::load_page(int page_num) {
    page_table[page_num].frame_num = n_frames;                      // sets frame number of page table to number of frames available in the stack
    page_table[page_num].valid = true;                              // validates the bit of the page table being added
    lifo.push(page_num);                                         // pushes the page_number into the top of the stack
}

// Access an invalid page and no free frames are available
int LIFOReplacement::replace_page(int page_num) {
    int page = lifo.top();                                          // accesses the top of the stack into the page
    lifo.pop();                                                     // removes the top of the stack
    page_table[page].valid = false;                                 // sets the valid member variable to false once we get rid of the old page

    lifo.push(page_num);                                         // places the new page into the stack
    page_table[page_num].valid = true;                              // validates the bit that was added
    page_table[page_num].frame_num = page_table[page].frame_num;    // sets frame number of page table to number of frames available
    return page;                                                    // returns old page for use outside of function
}