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

class SyslogAsyncClient
{
public:
    SyslogAsyncClient() = delete;

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

    void SetMaxTransmittedMessagesPerSecond(const uint32_t value);

    uint32_t GetMaxTransmittedMessagesPerSecond() const noexcept;

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