#include <stdexcept>

#include <boost/asio.hpp>

#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>

#include "SyslogAsyncClient.h"

using namespace boost::asio;
using namespace boost::log;

SyslogAsyncClient::SyslogAsyncClient(const std::string& address,
                                     const std::string& applicationName,
                                     const uint32_t maxTransmittedMessagesPerSecond)
{
    if (ip::address::from_string(address).is_v4() == false) {
        throw std::runtime_error("failed to create syslog client, cause invalid ipv4 address");
    }

    if (applicationName.empty()) {
        throw std::runtime_error("failed to create syslog client, cause application name is empty");
    }

    if (maxTransmittedMessagesPerSecond == 0) {
        throw std::runtime_error("failed to create syslog client, cause max transmitted messages per second is equal to zero");
    }

    CreateSyslogSink();

    SetFormatter(applicationName);

    SetSeverityMapper();

    SetRemoteAddress(address);

    AddSyslogSink();
}

SyslogAsyncClient::~SyslogAsyncClient()
{
    RemoveSyslogSink();
}

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
    if (sink == nullptr) {
        throw std::runtime_error("syslog sink hasn't been created");
    }

    BOOST_LOG_SEV(logger, level) << message;
}

void SyslogAsyncClient::CreateSyslogSink()
{
    if (sink == nullptr) {
        sink = boost::make_shared<sink_t>();
    }
}

void SyslogAsyncClient::SetFormatter(const std::string& applicationName)
{
    if (sink == nullptr) {
        throw std::runtime_error("syslog sink hasn't been created");
    }

    const std::string attribute("name");

    sink->set_formatter(
        expressions::format("%1%: %2%") % expressions::attr<std::string>(attribute) % expressions::message);

    core::get()->add_global_attribute(attribute, attributes::constant<std::string>(applicationName));
}

void SyslogAsyncClient::SetSeverityMapper()
{
    if (sink == nullptr) {
        throw std::runtime_error("syslog sink hasn't been created");
    }

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

void SyslogAsyncClient::SetRemoteAddress(const std::string& address)
{
    if (sink == nullptr) {
        throw std::runtime_error("syslog sink hasn't been created");
    }

    sink->locked_backend()->set_target_address(address);
}

void SyslogAsyncClient::AddSyslogSink()
{
    if (sink == nullptr) {
        throw std::runtime_error("syslog sink hasn't been created");
    }

    core::get()->add_sink(sink);
}

void SyslogAsyncClient::RemoveSyslogSink()
{
    if (sink == nullptr) {
        throw std::runtime_error("syslog sink hasn't been created");
    }

    core::get()->remove_sink(sink);
}