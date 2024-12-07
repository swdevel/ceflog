/**
 * @file SyslogSeverity.h
 * @author Alexander Borisov
 * @brief Файл содержит перечисление значений параметра Severity Level протокола Syslog
 * @version 0.1
 * @date 2024-12-07
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include "EnumClassMacro.h"

namespace ceflog::syslog
{

ENUM_CLASS_MACRO(SyslogSeverity,
                 Emergency,
                 Alert,
                 Critical,
                 Error,
                 Warning,
                 Notice,
                 Info,
                 Debug);

} // namespace ceflog::syslog