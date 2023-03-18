#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <csignal>

std::mutex gDataMutex;
std::condition_variable gDataCondition;
std::queue<int> gDataQueue;
bool gStopThreads = false;

void signalHandler(int signal) {
    std::cout << "Received signal " << "CTRL+C" << ", stopping threads..." << std::endl;
    gStopThreads = true;
    gDataCondition.notify_all();
}

void ProducerThread(int id, int queue_size) {
    while (!gStopThreads) {
        std::unique_lock<std::mutex> lock(gDataMutex);
        while (gDataQueue.size() >= queue_size && !gStopThreads) {
            gDataCondition.wait(lock);
        }
        if (gStopThreads) {
            break;
        }
        int data = rand() % 100;
        gDataQueue.push(data);
        std::cout << "Producer " << id << " produced data: " << data << std::endl;
        gDataCondition.notify_all();
        // Wait for some time before generating more data
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void ConsumerThread(int id, int queue_size) {
    while (!gStopThreads) {
        std::unique_lock<std::mutex> lock(gDataMutex);
        while (gDataQueue.empty() && !gStopThreads) {
            gDataCondition.wait(lock);
        }
        if (gStopThreads) {
            break;
        }
        int data = gDataQueue.front();
        gDataQueue.pop();
        std::cout << "Consumer " << id << " consumed data: " << data << std::endl;
        gDataCondition.notify_all();
    }
}

int main(int argc, char* argv[]) {
    int num_producers, num_consumers, queue_size;

    std::cout << "Enter the number of producers: ";
    std::cin >> num_producers;

    std::cout << "Enter the number of consumers: ";
    std::cin >> num_consumers;

    std::cout << "Enter the queue size: ";
    std::cin >> queue_size;
    std::cin.ignore();

    // Register signal handler for SIGINT signal
    std::signal(SIGINT, signalHandler);

    std::cout << "Starting " << num_producers << " producer threads and " << num_consumers << " consumer threads..." << std::endl;

    // Start the producer threads
    std::vector<std::thread> producer_threads;
    for (int i = 0; i < num_producers; ++i) {
        producer_threads.emplace_back(ProducerThread, i + 1, queue_size);
    }

    // Start the consumer threads
    std::vector<std::thread> consumer_threads;
    for (int i = 0; i < num_consumers; ++i) {
        consumer_threads.emplace_back(ConsumerThread, i + 1, queue_size);
    }

    // Wait for the user to press enter
    std::cout << "Press enter to stop the threads..." << std::endl;
    std::cin.get();

    // Set the flag to stop the threads
    gStopThreads = true;

    // Notify all the threads waiting on the condition variable
    gDataCondition.notify_all();

    // Join all the threads
    for (auto& t : producer_threads) {
        t.join();
    }
    for (auto& t : consumer_threads) {
        t.join();
    }

    return 0;
}
