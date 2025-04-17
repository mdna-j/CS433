/**
 * Assignment 4: Producer Consumer Problem
 * @file buffer.cpp
 * @author Jose Medina
 * @brief Implementation file for the Buffer class
 * @version 0.1
 */

// Implementation of a bounded buffer for producer-consumer synchronization

#include "buffer.h"
#include <iostream>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

/**
 * @brief Constructor: initializes buffer with given size
 * Initializes internal pointers and count variables
 * @param size The desired capacity of the buffer
 */
Buffer::Buffer(int size) : count(0), in(0), out(0) {
    buffer.resize(size);  // Resize vector to hold 'size' number of items
}

/**
 * @brief Destructor
 * Nothing to explicitly clean up in this implementation
 */
Buffer::~Buffer() {}

/**
 * @brief Insert an item into the buffer
 * Adds an item at the 'in' index and updates counters
 * @param item The item to be inserted
 * @return true if insertion is successful, false if buffer is full
 */
bool Buffer::insert_item(buffer_item item) {
    if (count < this->get_size()) {                        // Check if buffer has space
        buffer[in] = item;                                 // Insert item at current 'in' index
        in = (in + 1) % this->get_size();                  // Move 'in' index forward (circular)
        count++;                                           // Increment item count
        return true;
    }
    return false;                                          // Buffer is full, insertion failed
}

/**
 * @brief Remove an item from the buffer
 * Retrieves item from the 'out' index and updates counters
 * @param item Pointer to a variable to store the removed item
 * @return true if removal is successful, false if buffer is empty
 */
bool Buffer::remove_item(buffer_item *item) {
    if (count > 0) {                                       // Check if buffer is not empty
        *item = buffer[out];                               // Retrieve item from current 'out' index
        out = (out + 1) % this->get_size();                // Move 'out' index forward (circular)
        count--;                                           // Decrement item count
        return true;
    }
    return false;                                          // Buffer is empty, removal failed
}

/**
 * @brief Print the contents of the buffer
 * Displays items from 'out' to 'in' in a readable format
 */
void Buffer::print_buffer() {
    std::cout << "Buffer: [";
    if (this->is_empty()) {
        std::cout << "Empty";                              // Print "Empty" if buffer has no items
    } else {
        for (int i = 0; i < count; ++i) {
            std::cout << buffer[(out + i) % this->get_size()];  // Print each item in logical order
            if (i != count - 1) std::cout << " ";               // Separate items with a space
        }
    }
    std::cout << "]" << std::endl;
}

/**
 * @brief Get the total size of the buffer
 * @return Integer representing buffer capacity
 */
int Buffer::get_size() {
    return buffer.size();
}

/**
 * @brief Get the number of items currently stored in the buffer
 * @return Integer representing item count
 */
int Buffer::get_count() {
    return count;
}

/**
 * @brief Check if the buffer is empty
 * @return true if buffer contains no items, false otherwise
 */
bool Buffer::is_empty() {
    return count == 0;
}

/**
 * @brief Check if the buffer is full
 * @return true if buffer is at maximum capacity, false otherwise
 */
bool Buffer::is_full() {
    return count == buffer.size();
}
