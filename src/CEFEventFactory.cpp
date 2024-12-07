/**
 * @file CEFEventFactory.cpp
 * @author Alexander Borisov
 * @brief Файл содержит определение функций класса для создания событий в формате "CEF (Common Event Format)"
 * @version 0.1
 * @date 2024-12-07
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "CEFEventFactory.h"

namespace ceflog::event
{

CEFEvent CEFEventFactory::CreateEvent(const std::string& deviceEventClassId,
                                      const std::string& name,
                                      const CEFSeverity severity,
                                      const std::vector<CEFEventExtension>& extensions) const noexcept
{
    return CEFEvent(formatVersion,
                    deviceVendor,
                    deviceProduct,
                    deviceVersion,
                    deviceEventClassId,
                    name,
                    severity,
                    extensions);
}

} // namespace ceflog::event