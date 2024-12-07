/**
 * @file SyslogAsyncClient.h
 * @author Alexander Borisov
 * @brief Файл содержит объявление класса для передачи сообщений по протоколу Syslog
 * @version 0.1
 * @date 2024-12-07
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include <stdexcept>
#include <string>

#include "SelfConsumingQueue.h"
#include "SyslogBoostClientBackend.h"

namespace ceflog::syslog
{

/**
 * @brief Значение по умолчанию для максимального количества передаваемых в секунду сообщений
 *
 */
const uint32_t DEFAULT_MAX_TRANSMITTED_MESSAGES_PER_SECOND = 100;

/**
 * @brief Класс для передачи сообщений по протоколу Syslog
 *
 */
class SyslogAsyncClient
{
public:
    SyslogAsyncClient() = delete;

    /**
     * @brief Конструктор класса
     *
     * @param[in] backend Указатель на экземпляр класса с реализацией механизма передачи сообщений по протоколу Syslog
     * @param[in] maxTransmittedMessagesPerSecond Максимальное количество передаваемых в секунду сообщений
     */
    SyslogAsyncClient(const std::shared_ptr<SyslogAbstractClientBackend>& backend,
                      const uint32_t maxTransmittedMessagesPerSecond = DEFAULT_MAX_TRANSMITTED_MESSAGES_PER_SECOND)
        : backend(backend)
    {
        if (maxTransmittedMessagesPerSecond == 0) {
            throw std::runtime_error("max transmitted messages per second is equal to zero");
        }

        auto callback = [=](syslog_message_t& message) -> void {
            backend->LogMessage(message.severity, message.message);
        };

        queue = std::make_shared<SelfConsumingQueue<syslog_message_t>>(callback, maxTransmittedMessagesPerSecond);
    }

    SyslogAsyncClient(const SyslogAsyncClient& copy) = delete;
    SyslogAsyncClient& operator=(const SyslogAsyncClient& copy) = delete;
    SyslogAsyncClient(SyslogAsyncClient&& move) noexcept = delete;
    SyslogAsyncClient& operator=(SyslogAsyncClient&& move) noexcept = delete;

    /**
     * @brief Метод для установки максимального количества передаваемых в секунду сообщений
     *
     * @param[in] value Максимальное количество передаваемых в секунду сообщений
     */
    void SetMaxTransmittedMessagesPerSecond(const uint32_t value);

    /**
     * @brief Метод для получения максимального количества передаваемых в секунду сообщений
     *
     * @return uint32_t Максимальное количество передаваемых в секунду сообщений
     */
    uint32_t GetMaxTransmittedMessagesPerSecond() const noexcept;

    /**
     * @brief Метод для отправки сообщения
     *
     * @param[in] severity Идентификатор значения Severity Level протокола Syslog
     * @param[in] message Сообщение
     */
    void PushMessage(const SyslogSeverity severity, const std::string& message);

private:
    struct syslog_message_t {
        SyslogSeverity severity;
        std::string message;
    };

private:
    std::shared_ptr<SyslogAbstractClientBackend> backend;

    std::shared_ptr<SelfConsumingQueue<syslog_message_t>> queue;
};

} // namespace ceflog::syslog