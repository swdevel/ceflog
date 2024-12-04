#pragma once

#include <string>
#include <stdexcept>

#include "SyslogSeverity.h"

class SyslogAbstractClientBackend
{
public:
    SyslogAbstractClientBackend(const std::string& syslogServerAddress, const std::string& applicationName)
    {
        if (syslogServerAddress.empty()) {
            throw std::runtime_error("syslog server address is empty");
        }

        if (applicationName.empty()) {
            throw std::runtime_error("application name is empty");
        }

        this->syslogServerAddress = syslogServerAddress;
        this->applicationName = applicationName;
    }

    virtual void LogMessage(const SyslogSeverity severity, const std::string& message) = 0;

    virtual ~SyslogAbstractClientBackend() = default;

protected:
    std::string syslogServerAddress;

    std::string applicationName;
};