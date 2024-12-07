/**
 * @file CEFEventFactory.h
 * @author Alexander Borisov
 * @brief Файл содержит объявление класса для создания событий в формате "CEF (Common Event Format)"
 * @version 0.1
 * @date 2024-12-07
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include "CEFEvent.h"

namespace ceflog::event
{

class CEFEventFactory
{
public:
    CEFEventFactory(const uint8_t formatVersion,
                    const std::string& deviceVendor,
                    const std::string& deviceProduct,
                    const std::string& deviceVersion)
        : formatVersion(formatVersion),
          deviceVendor(deviceVendor),
          deviceProduct(deviceProduct),
          deviceVersion(deviceVersion)
    {
    }

    CEFEvent CreateEvent(const std::string& deviceEventClassId,
                         const std::string& name,
                         const CEFSeverity severity,
                         const std::vector<CEFEventExtension>& extensions = {}) const noexcept;

private:
    uint8_t formatVersion;

    std::string deviceVendor;

    std::string deviceProduct;

    std::string deviceVersion;
};

} // namespace ceflog::event