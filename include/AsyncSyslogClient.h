#pragma once

#include <string>

enum class SyslogSeverity
{
    Emergency,
    Alert,
    Critical,
    Error,
    Warning,
    Notice,
    Info,
    Debug,
};

class AsyncSyslogClient
{
public:
    AsyncSyslogClient(const std::string& address, const std::string& applicationName);
};