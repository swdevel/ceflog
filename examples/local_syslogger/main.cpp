/**
 * @file main.cpp
 * @author Alexander Borisov
 * @brief Файл содержит исходный код демонстрационного примера отправки сообщений по протоколу syslog на локальный сервер.
 * Для корректной работы примера необходимо предварительно выполнить установку и настройку локального rsyslog server.
 * Инструкция по установке и настройке описана в файле README.md.
 * Результат работы демонстрационного примера можно увидеть в файле "/var/log/syslog" при помощи команды:
 * $> tail -n 100 /var/log/syslog
 * 
 * @version 0.1
 * @date 2024-12-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "SyslogAsyncClient.h"
#include "SyslogBoostClientBackend.h"

std::string timestamp()
{
    using namespace std::chrono;

    const auto time = system_clock::to_time_t(system_clock::now());
    std::string string = std::ctime(&time);

    return string.substr(0, string.size() - 1);
}

int main()
{
    auto sysloggerBackend = std::make_shared<SyslogBoostClientBackend>("127.0.0.1",
                                                                       "syslogger");
    SyslogAsyncClient sysloggerClient(sysloggerBackend);

    const auto message = timestamp() + " ping from syslog async client";
    sysloggerClient.PushMessage(SyslogSeverity::Info, message);

    return 0;
}