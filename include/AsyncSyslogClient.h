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

class AsyncSyslogClient
{
public:
    AsyncSyslogClient(const std::string& address,
                      const std::string& applicationName,
                      const uint32_t maxTransmittedMessagesPerSecond = DEFAULT_MAX_TRANSMITTED_MESSAGES_PER_SECOND);

    ~AsyncSyslogClient();

    void SetMaxTransmittedMessagesPerSecond(const uint32_t value);

    uint32_t GetMaxTransmittedMessagesPerSecond() const noexcept;

    void PushMessage(const SyslogSeverity level, const std::string& message);

private:
    void CreateSyslogSink();

    void SetFormatter(const std::string& applicationName);

    void SetSeverityMapper();

    void SetRemoteAddress(const std::string& address);

    void AddSyslogSink();

private:
    using sink_t = boost::log::sinks::synchronous_sink<boost::log::sinks::syslog_backend>;

    using logger_t = boost::log::sources::severity_logger<SyslogSeverity>;

private:
    boost::shared_ptr<sink_t> sink;

    logger_t logger;

    uint32_t maxTransmittedMessagesPerSecond;
};