#pragma once

#include "CEFEvent.h"

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