#pragma once

#include <string>

enum class SyslogSeverity {
    Emergency,
    Alert,
    Critical,
    Error,
    Warning,
    Notice,
    Info,
    Debug,
};

/**
 * @brief Значение по умолчанию для максимального количества передаваемых в секунду сообщений
 *
 */
const uint32_t DEFAULT_MAX_TRANSMITTED_MESSAGES_PER_SECOND = 100;

class AsyncSyslogClient
{
public:
    AsyncSyslogClient(const std::string& address,
                      const std::string& applicationName,
                      const uint32_t maxTransmittedMessagesPerSecond = DEFAULT_MAX_TRANSMITTED_MESSAGES_PER_SECOND);

    void SetMaxTransmittedMessagesPerSecond(const uint32_t value);

    uint32_t GetMaxTransmittedMessagesPerSecond() const noexcept;

private:
    uint32_t maxTransmittedMessagesPerSecond;
};