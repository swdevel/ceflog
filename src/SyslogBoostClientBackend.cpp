/**
 * @file SyslogBoostClientBackend.cpp
 * @author Alexander Borisov
 * @brief Файл содержит определение функций класса бэкенда для передачи сообщений по протоколу Syslog с использованием библиотеки boost::log
 * @version 0.1
 * @date 2024-12-07
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>

#include "SyslogBoostClientBackend.h"

namespace ceflog::syslog
{

using namespace boost::log;

void SyslogBoostClientBackend::LogMessage(const SyslogSeverity severity, const std::string& message)
{
    BOOST_LOG_SEV(logger, severity) << message;
}

void SyslogBoostClientBackend::Init()
{
    sink = boost::make_shared<sink_t>();

    SetFormatter();
    SetSeverityMapper();
    SetSyslogServerAddress();

    core::get()->add_sink(sink);
}

void SyslogBoostClientBackend::Release()
{
    core::get()->remove_sink(sink);
}

void SyslogBoostClientBackend::SetFormatter()
{
    const std::string attribute("name");

    sink->set_formatter(
        expressions::format("%1%: %2%") % expressions::attr<std::string>(attribute) % expressions::message);

    core::get()->add_global_attribute(attribute, attributes::constant<std::string>(applicationName));
}

void SyslogBoostClientBackend::SetSeverityMapper()
{
    sinks::syslog::custom_severity_mapping<SyslogSeverity> mapper("Severity");

    mapper[SyslogSeverity::Emergency] = sinks::syslog::emergency;
    mapper[SyslogSeverity::Alert] = sinks::syslog::alert;
    mapper[SyslogSeverity::Critical] = sinks::syslog::critical;
    mapper[SyslogSeverity::Error] = sinks::syslog::error;
    mapper[SyslogSeverity::Warning] = sinks::syslog::warning;
    mapper[SyslogSeverity::Notice] = sinks::syslog::notice;
    mapper[SyslogSeverity::Info] = sinks::syslog::info;
    mapper[SyslogSeverity::Debug] = sinks::syslog::debug;

    sink->locked_backend()->set_severity_mapper(mapper);
}

void SyslogBoostClientBackend::SetSyslogServerAddress()
{
    sink->locked_backend()->set_target_address(syslogServerAddress);
}

} // namespace ceflog::syslog