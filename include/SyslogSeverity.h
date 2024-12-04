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