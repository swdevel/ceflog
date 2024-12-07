/**
 * @file SyslogBoostClientBackend.h
 * @author Alexander Borisov
 * @brief Файл содержит объявление класса для реализации механизма передачи сообщений по протоколу Syslog с использованием библиотеки boost::log
 * @version 0.1
 * @date 2024-12-07
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include <boost/asio.hpp>

#include <boost/log/common.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/syslog_backend.hpp>

#include <boost/shared_ptr.hpp>

#include "SyslogAbstractClientBackend.h"

namespace ceflog::syslog
{

/**
 * @brief Класс для реализации механизма передачи сообщений по протоколу Syslog с использованием библиотеки boost::log
 *
 */
class SyslogBoostClientBackend : public SyslogAbstractClientBackend
{
public:
    /**
     * @brief Конструктор класса
     *
     * @param[in] syslogServerAddress IP-адрес сервера Syslog
     * @param[in] applicationName Имя приложения для отображения в логах
     */
    SyslogBoostClientBackend(const std::string& syslogServerAddress, const std::string& applicationName)
        : SyslogAbstractClientBackend(syslogServerAddress, applicationName)
    {
        if (boost::asio::ip::address::from_string(syslogServerAddress).is_v4() == false) {
            throw std::runtime_error("invalid ipv4 address");
        }

        Init();
    }

    ~SyslogBoostClientBackend()
    {
        Release();
    }

    /**
     * @brief Метод для отправки сообщения по протоколу Syslog
     *
     * @param[in] severity Идентификатор значения Severity Level протокола Syslog
     * @param[in] message Сообщение
     */
    virtual void LogMessage(const SyslogSeverity severity, const std::string& message) override;

private:
    void Init();

    void Release();

    void SetFormatter();

    void SetSeverityMapper();

    void SetSyslogServerAddress();

private:
    using sink_t = boost::log::sinks::synchronous_sink<boost::log::sinks::syslog_backend>;

    using logger_t = boost::log::sources::severity_logger<SyslogSeverity>;

private:
    boost::shared_ptr<sink_t> sink;

    logger_t logger;
};

} // namespace ceflog::syslog