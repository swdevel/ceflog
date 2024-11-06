#pragma once

#include <string>

#include "CEFLogMacro.h"

ENUM_CLASS_MACRO(Severity, Low, Medium, High, VeryHigh);

class CEFEvent
{
public:
    CEFEvent() = delete;

    CEFEvent(const std::string& deviceVendor,
             const std::string& deviceProduct,
             const std::string& deviceVersion,
             const std::string& deviceEventClassId,
             const std::string& name,
             Severity severity)
        : deviceVendor(deviceVendor),
          deviceProduct(deviceProduct),
          deviceVersion(deviceVersion),
          deviceEventClassId(deviceEventClassId),
          name(name),
          severity(severity)
    {
        // TODO: ...
    }

    ~CEFEvent() = default;

    void SetDeviceVendor(const std::string& value) noexcept;

    std::string GetDeviceVendor() const noexcept;

    void SetDeviceProduct(const std::string& value) noexcept;

    std::string GetDeviceProduct() const noexcept;

    void SetDeviceVersion(const std::string& value) noexcept;

    std::string GetDeviceVersion() const noexcept;

    void SetDeviceEventClassId(const std::string& value) noexcept;

    std::string GetDeviceEventClassId() const noexcept;

    void SetName(const std::string& value) noexcept;

    std::string GetName() const noexcept;

    void SetSeverity(const Severity& value) noexcept;

    Severity GetSeverity() const noexcept;

private:
    std::string deviceVendor;

    std::string deviceProduct;

    std::string deviceVersion;

    std::string deviceEventClassId;

    std::string name;

    Severity severity;
};