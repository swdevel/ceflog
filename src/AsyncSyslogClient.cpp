#include <stdexcept>

#include <boost/asio.hpp>

#include "AsyncSyslogClient.h"

using namespace boost::asio;

AsyncSyslogClient::AsyncSyslogClient(const std::string& address, const std::string& applicationName)
{
    if (ip::address::from_string(address).is_v4() == false) {
        throw std::runtime_error("failed to create syslog client, cause invalid ipv4 address");
    }

    if (applicationName.empty()) {
        throw std::runtime_error("failed to create syslog client, cause application name is empty");
    }

    // TODO: ...
}