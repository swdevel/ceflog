#include <stdexcept>

#include <boost/asio.hpp>

#include "AsyncSyslogClient.h"

using namespace boost::asio;

AsyncSyslogClient::AsyncSyslogClient(const std::string& address,
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

    // TODO: ...
}

void AsyncSyslogClient::SetMaxTransmittedMessagesPerSecond(const uint32_t value)
{
    if (value == 0) {
        throw std::runtime_error("failed to set new value, cause param is equal to zero");
    }

    maxTransmittedMessagesPerSecond = value;
}

uint32_t AsyncSyslogClient::GetMaxTransmittedMessagesPerSecond() const noexcept
{
    return maxTransmittedMessagesPerSecond;
}