/**
 * @file SyslogAbstractClientBackend.h
 * @author Alexander Borisov
 * @brief Файл содержит объявление базового класса механизма передачи сообщений по протоколу Syslog
 * @version 0.1
 * @date 2024-12-07
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include <stdexcept>
#include <string>

#include "SyslogSeverity.h"

namespace ceflog::syslog
{

/**
 * @brief Базовый класс механизма передачи сообщений по протоколу Syslog
 *
 */
class SyslogAbstractClientBackend
{
public:
    /**
     * @brief Конструктор класса
     *
     * @param[in] syslogServerAddress IP-адрес сервера Syslog
     * @param[in] applicationName Имя приложения для отображения в логах
     */
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
    /**
     * @brief IP-адрес сервера Syslog
     *
     */
    std::string syslogServerAddress;

    /**
     * @brief Имя приложения для отображения в логах
     *
     */
    std::string applicationName;
};

} // namespace ceflog::syslog