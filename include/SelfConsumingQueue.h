/**
 * @file SelfConsumingQueue.h
 * @author Alexander Borisov
 * @brief Файл содержит объявление класса очереди для автоматической асинхронной обработки элементов
 * @version 0.1
 * @date 2024-12-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

namespace ceflog::syslog
{

/**
 * @brief Класс очереди для автоматической асинхронной обработки элементов
 *
 * Функционал класса позволяет асинхронно выполнять операции добавления и обработки элементов очереди.
 * Для обработки каждого из элементов очереди будет вызвана callback функция, передаваемая в класс извне.
 * Присутствует возможность ограничивать скорость обработки элементов очереди за счёт ограничения на
 * максимально допустимое количество вызовов callback функции за одну секунду.
 *
 * @tparam T Тип элементов очереди
 */
template <typename T>
class SelfConsumingQueue
{
public:
    SelfConsumingQueue() = delete;

    /**
     * @brief Конструктор класса
     *
     * @param callback Константный указатель на callback функцию, которая будет вызвана для обработки каждого из элементов очереди
     * @param processingLimitPerSecond Максимально допустимое количество вызовов callback функции за одну секунду
     */
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

    /**
     * @brief Метод для установки максимально допустимого количества вызовов callback функции за одну секунду
     *
     * @param value Максимально допустимое количество вызовов callback функции за одну секунду
     */
    void SetProcessingLimitPerSecond(const uint32_t value) noexcept
    {
        limit = value;
    }

    /**
     * @brief Метод для получения максимально допустимого количества вызовов callback функции за одну секунду
     *
     * @return uint32_t Максимально допустимое количество вызовов callback функции за одну секунду
     */
    uint32_t GetProcessingLimitPerSecond() const noexcept
    {
        return limit;
    }

    /**
     * @brief Метод для добавления нового элемента в очередь
     *
     * @param element Константная ссылка на элемент
     */
    void Push(const T& element)
    {
        input.push(element);
        available.notify_one();
    }

private:
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

} // namespace ceflog::syslog