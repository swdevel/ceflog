/**
 * @file SyslogAsyncClient.cpp
 * @author Alexander Borisov
 * @brief Файл содержит определение функций класса для передачи сообщений по протоколу Syslog
 * @version 0.1
 * @date 2024-12-07
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "SyslogAsyncClient.h"

namespace ceflog::syslog
{

void SyslogAsyncClient::SetMaxTransmittedMessagesPerSecond(const uint32_t value)
{
    if (value == 0) {
        throw std::runtime_error("failed to set new value, cause param is equal to zero");
    }

    queue->SetProcessingLimitPerSecond(value);
}

uint32_t SyslogAsyncClient::GetMaxTransmittedMessagesPerSecond() const noexcept
{
    return queue->GetProcessingLimitPerSecond();
}

void SyslogAsyncClient::PushMessage(const SyslogSeverity severity, const std::string& message)
{
    queue->Push({severity, message});
}

} // namespace ceflog::syslog