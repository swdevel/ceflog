#pragma once

#include <string>

#include <boost/log/common.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/syslog_backend.hpp>

#include <boost/shared_ptr.hpp>

#include "CEFLogMacro.h"

ENUM_CLASS_MACRO(SyslogSeverity,
                 Emergency,
                 Alert,
                 Critical,
                 Error,
                 Warning,
                 Notice,
                 Info,
                 Debug, );

/**
 * @brief Значение по умолчанию для максимального количества передаваемых в секунду сообщений
 *
 */
const uint32_t DEFAULT_MAX_TRANSMITTED_MESSAGES_PER_SECOND = 100;

class SyslogAsyncClient
{
public:
    // Constructor
    SyslogAsyncClient() = delete;

    // Constructor
    SyslogAsyncClient(const std::string& address,
                      const std::string& applicationName,
                      const uint32_t maxTransmittedMessagesPerSecond = DEFAULT_MAX_TRANSMITTED_MESSAGES_PER_SECOND);

    // Copy constructor
    SyslogAsyncClient(const SyslogAsyncClient& other) = delete;

    // Copy assignment
    SyslogAsyncClient& operator=(const SyslogAsyncClient& other) = delete;

    // Move constructor
    SyslogAsyncClient(SyslogAsyncClient&& other) noexcept = delete;

    // Move assignment
    SyslogAsyncClient& operator=(SyslogAsyncClient&& other) noexcept = delete;

    // Destructor
    ~SyslogAsyncClient();

    void SetMaxTransmittedMessagesPerSecond(const uint32_t value);

    uint32_t GetMaxTransmittedMessagesPerSecond() const noexcept;

    void PushMessage(const SyslogSeverity level, const std::string& message);

private:
    void CreateSyslogSink();

    void SetFormatter(const std::string& applicationName);

    void SetSeverityMapper();

    void SetRemoteAddress(const std::string& address);

    void AddSyslogSink();

    void RemoveSyslogSink();

private:
    using sink_t = boost::log::sinks::synchronous_sink<boost::log::sinks::syslog_backend>;

    using logger_t = boost::log::sources::severity_logger<SyslogSeverity>;

private:
    boost::shared_ptr<sink_t> sink;

    logger_t logger;

    uint32_t maxTransmittedMessagesPerSecond;
};