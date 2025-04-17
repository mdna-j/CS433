/**
 * Assignment 4: Producer Consumer Problem
 * @file main.cpp
 * @author Jose Medina
 * @brief The main program for the producer-consumer problem.
 * @version 0.1
 */

#include <iostream>
#include "buffer.h"
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <vector>

using namespace std;

// Global buffer object
Buffer buffer;

// Semaphores for controlling access to the buffer
sem_t semEmpty;
sem_t semFull;

// Mutex for mutual exclusion
pthread_mutex_t mutexBuffer;

/**
 * @brief Producer thread function
 * Each producer inserts its own ID into the buffer
 */
void *producer(void *param) {
    buffer_item item = *((int *) param);  // Unique item = thread ID

    while (true) {
        usleep(rand() % 1000000); // Sleep for a random time up to 1 second

        sem_wait(&semEmpty); // Wait until there is space in the buffer
        pthread_mutex_lock(&mutexBuffer); // Lock the buffer

        if (buffer.insert_item(item)) {
            cout << "Producer " << item << ": Inserted item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Producer error condition" << endl;
        }

        pthread_mutex_unlock(&mutexBuffer); // Unlock the buffer
        sem_post(&semFull); // Signal that there is a new item in the buffer
    }

    return nullptr;
}

/**
 * @brief Consumer thread function
 * Continuously removes items from the buffer
 */
void *consumer(void *param) {
    buffer_item item;

    while (true) {
        usleep(rand() % 1000000); // Sleep for a random time up to 1 second

        sem_wait(&semFull); // Wait until the buffer has an item
        pthread_mutex_lock(&mutexBuffer); // Lock the buffer

        if (buffer.remove_item(&item)) {
            cout << "Consumer: Removed item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Consumer error condition" << endl;
        }

        pthread_mutex_unlock(&mutexBuffer); // Unlock the buffer
        sem_post(&semEmpty); // Signal that space is available in the buffer
    }

    return nullptr;
}

/**
 * @brief Main function to initialize and manage threads
 */
int main(int argc, char *argv[]) {
    // Check for proper command-line usage
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <sleep_time> <num_producers> <num_consumers>" << endl;
        return 1;
    }

    int sleep_time = atoi(argv[1]);     // Time main thread sleeps before ending
    int n_producers = atoi(argv[2]);    // Number of producers
    int n_consumers = atoi(argv[3]);    // Number of consumers

    // Show parsed arguments for debugging
    cout << "['" << argv[0] << "', '" << argv[1] << "', '" << argv[2] << "', '" << argv[3] << "']" << endl;

    // Initialize synchronization tools
    pthread_mutex_init(&mutexBuffer, nullptr);
    sem_init(&semEmpty, 0, buffer.get_size()); // Initially, all buffer slots are empty
    sem_init(&semFull, 0, 0);                  // No items in buffer initially

    // Create producer threads with unique IDs
    vector<pthread_t> producers(n_producers);
    vector<int> producer_ids(n_producers);

    for (int i = 0; i < n_producers; ++i) {
        producer_ids[i] = i + 1;
        if (pthread_create(&producers[i], nullptr, producer, &producer_ids[i]) != 0) {
            cerr << "Error creating producer thread " << i + 1 << endl;
            return 1;
        }
    }

    // Create consumer threads
    vector<pthread_t> consumers(n_consumers);
    for (int i = 0; i < n_consumers; ++i) {
        if (pthread_create(&consumers[i], nullptr, consumer, nullptr) != 0) {
            cerr << "Error creating consumer thread " << i + 1 << endl;
            return 1;
        }
    }

    // Sleep main thread for specified time before cleanup
    sleep(sleep_time);

    // Cleanup semaphores
    sem_destroy(&semEmpty);
    sem_destroy(&semFull);

    // Exit main (Note: threads are not joined or cancelled since they run infinitely)
    return 0;
}
