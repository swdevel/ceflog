#pragma once

#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

template <typename T>
class SelfConsumingQueue
{
public:
    SelfConsumingQueue(const std::function<void(T&)>& callback)
        : callback(callback),
          running(true)
    {
        thread = std::thread(&SelfConsumingQueue::Worker, this);
    }

    ~SelfConsumingQueue()
    {
        {
            std::unique_lock<std::mutex> lock(mutex);
            running = false;
        }

        available.notify_one();

        if (thread.joinable()) {
            thread.join();
        }
    }

    void Push(const T& element)
    {
        {
            std::unique_lock<std::mutex> lock(mutex);
            input.push(element);
        }

        available.notify_one();
    }

    SelfConsumingQueue(const SelfConsumingQueue& copy) = delete;
    SelfConsumingQueue& operator=(const SelfConsumingQueue& copy) = delete;
    SelfConsumingQueue(SelfConsumingQueue&& move) noexcept = delete;
    SelfConsumingQueue& operator=(SelfConsumingQueue&& move) noexcept = delete;

    void Worker()
    {
        while (running) {

            {
                std::unique_lock<std::mutex> lock(mutex);
                if (input.empty()) {
                    available.wait(lock, [&]() { return !input.empty() || !running; });
                }

                output.swap(input);
            }

            while (!output.empty()) {
                callback(output.front());
                output.pop();
            }
        }
    }

private:
    std::function<void(T&)> callback;

    std::queue<T> input;
    std::queue<T> output;

    std::condition_variable available;
    std::atomic_bool running;
    std::thread thread;
    std::mutex mutex;
};