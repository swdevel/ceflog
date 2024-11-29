#include "SyslogAsyncClient.h"

void SyslogAsyncClient::SetMaxTransmittedMessagesPerSecond(const uint32_t value)
{
    if (value == 0) {
        throw std::runtime_error("failed to set new value, cause param is equal to zero");
    }

    maxTransmittedMessagesPerSecond = value;
}

uint32_t SyslogAsyncClient::GetMaxTransmittedMessagesPerSecond() const noexcept
{
    return maxTransmittedMessagesPerSecond;
}

void SyslogAsyncClient::PushMessage(const SyslogSeverity level, const std::string& message)
{
    backend->LogMessage(level, message);
}