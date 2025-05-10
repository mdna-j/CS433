/**
* Assignment 5: Page replacement algorithms
 * @file lru_replacement.cpp
 * @author Jose Medina
 * @brief A class implementing the LRU page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code


#include "lru_replacement.h"

// TODO: Add your implementation here
LRUReplacement::LRUReplacement(int num_pages, int num_frames) : Replacement(num_pages, num_frames) {}

// TODO: Add your implementations for desctructor, touch_page, load_page, replace_page here
LRUReplacement::~LRUReplacement() {}

// Accesss a page alreay in physical memory
void LRUReplacement::touch_page(int page_num)
{
    lru.remove(page_num);                                     // finds and removes page number in the table if it exists
    lru.push_front(page_num);                                     // pushed the page number to the front (most recently used)
    page_table[page_num].valid = true;
}

// Access an invalid page, but free frames are available
void LRUReplacement::load_page(int page_num) {
    page_table[page_num].valid = true;
    lru.push_front(page_num);                                     // add to the front as the most recently used
}

// Access an invalid page and no free frames are available
int LRUReplacement::replace_page(int page_num) {
    int page = lru.back();                                          // accesses the least recently used page
    lru.pop_back();                                                 // removes the least recently used page from the queue
    page_table[page].valid = false;
    lru.push_front(page_num);                                    // add the new page as the most recently used
    page_table[page_num].valid = true;
    return page;
}
