#pragma once

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

template <typename T>
class SelfConsumingQueue
{
public:
    SelfConsumingQueue() = delete;

    SelfConsumingQueue(const std::function<void(T&)>& callback,
                       const uint32_t processingLimitPerSecond)
        : callback(callback),
          limit(processingLimitPerSecond),
          running(true)
    {
        thread = std::thread(&SelfConsumingQueue::Worker, this);
    }

    ~SelfConsumingQueue()
    {
        {
            std::unique_lock<std::mutex> lock(mutex);
            Flush();
            running = false;
        }

        available.notify_one();

        if (thread.joinable()) {
            thread.join();
        }
    }

    SelfConsumingQueue(const SelfConsumingQueue& copy) = delete;
    SelfConsumingQueue& operator=(const SelfConsumingQueue& copy) = delete;
    SelfConsumingQueue(SelfConsumingQueue&& move) noexcept = delete;
    SelfConsumingQueue& operator=(SelfConsumingQueue&& move) noexcept = delete;

    void SetProcessingLimitPerSecond(const uint32_t value) noexcept
    {
        limit = value;
    }

    uint32_t GetProcessingLimitPerSecond() const noexcept
    {
        return limit;
    }

    void Push(const T& element)
    {
        input.push(element);
        available.notify_one();
    }

    void Worker()
    {
        while (running) {

            std::unique_lock<std::mutex> lock(mutex);
            if (input.empty()) {
                available.wait(lock, [&]() { return !input.empty() || !running; });
            }

            Flush();
        }
    }

private:
    void Flush()
    {
        output.swap(input);

        auto timeoutBarrier = ProcessTimeoutBarrier();
        uint32_t counter = 0;

        while (!output.empty()) {
            callback(output.front());
            output.pop();

            counter++;

            if (counter == limit) {
                std::this_thread::sleep_until(timeoutBarrier);
                timeoutBarrier = ProcessTimeoutBarrier();
                counter = 0;
            }
        }
    }

    inline std::chrono::time_point<std::chrono::system_clock> ProcessTimeoutBarrier() const noexcept
    {
        return std::chrono::system_clock::now() + std::chrono::seconds(1);
    }

private:
    std::function<void(T&)> callback;

    std::queue<T> input;
    std::queue<T> output;

    std::condition_variable available;
    std::atomic_bool running;
    std::thread thread;
    std::mutex mutex;

    uint32_t limit;
};