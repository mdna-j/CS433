    /**
     * Assignment 4: Producer Consumer Problem
     * @file buffer.h
     * @author Jose Medina
     * @brief Header file for the Buffer class
     * @version 0.1
     */

    #ifndef ASSIGN4_BUFFER_H
    #define ASSIGN4_BUFFER_H

    #include <pthread.h>           // For using POSIX threads
    #include <semaphore.h>         // For semaphore operations (if used)
    #include <mutex>               // For using std::mutex (if needed)
    #include <condition_variable>  // For thread synchronization (if needed)
    #include <vector>              // For using std::vector to store buffer items

    using namespace std;

    // Define the data type of the buffer items (can change later if needed)
    typedef int buffer_item;

    /**
     * @brief The bounded buffer class.
     * This class models a circular queue with a fixed capacity.
     * The number of items in the buffer cannot exceed the size.
     */
    class Buffer {
    private:
        vector<buffer_item> buffer;  // Underlying data structure to store buffer items
        int count;                   // Current number of items in the buffer
        int in;                      // Index for the next insertion 
        int out;                     // Index for the next removal 

    public:
        /**
         * @brief Construct a new Buffer object
         * @param size The size/capacity of the buffer (default is 5)
         */
        Buffer(int size = 5);

        /**
         * @brief Destructor to clean up any allocated resources
         */
        ~Buffer();

        /**
         * @brief Insert an item into the buffer
         * @param item The item to insert
         * @return true if insertion was successful
         * @return false if the buffer is full and insertion failed
         */
        bool insert_item(buffer_item item);

        /**
         * @brief Remove an item from the buffer
         * @param item Pointer to a variable where the removed item will be stored
         * @return true if removal was successful
         * @return false if the buffer is empty and removal failed
         */
        bool remove_item(buffer_item *item);

        /**
         * @brief Get the total size/capacity of the buffer
         * @return Integer value representing buffer size
         */
        int get_size();

        /**
         * @brief Get the number of items currently in the buffer
         * @return Integer value of item count
         */
        int get_count();

        /**
         * @brief Check if the buffer is empty
         * @return true if buffer is empty, otherwise false
         */
        bool is_empty();

        /**
         * @brief Check if the buffer is full
         * @return true if buffer is full, otherwise false
         */
        bool is_full();

        /**
         * @brief Print the contents of the buffer (for debugging)
         */
        void print_buffer();
    };

    #endif // ASSIGN4_BUFFER_H
