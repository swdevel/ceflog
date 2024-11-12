#pragma once

#include <string>
#include <utility>

#include "CEFLogMacro.h"

ENUM_CLASS_MACRO(Severity, Undefined, Low, Medium, High, VeryHigh);

class CEFEvent
{
public:
    ~CEFEvent() = default;

    CEFEvent(const std::string& deviceVendor = "",
             const std::string& deviceProduct = "",
             const std::string& deviceVersion = "",
             const std::string& deviceEventClassId = "",
             const std::string& name = "",
             Severity severity = Severity::Undefined)
        : deviceVendor(deviceVendor),
          deviceProduct(deviceProduct),
          deviceVersion(deviceVersion),
          deviceEventClassId(deviceEventClassId),
          name(name),
          severity(severity)
    {
    }

    // Copy constructor
    CEFEvent(const CEFEvent& other)
        : CEFEvent(other.deviceVendor,
                   other.deviceProduct,
                   other.deviceVersion,
                   other.deviceEventClassId,
                   other.name,
                   other.severity)
    {
    }

    // Copy assignment
    CEFEvent& operator=(const CEFEvent& other);

    // Move constructor
    CEFEvent(CEFEvent&& other) noexcept
        : deviceVendor(std::exchange(other.deviceVendor, "")),
          deviceProduct(std::exchange(other.deviceProduct, "")),
          deviceVersion(std::exchange(other.deviceVersion, "")),
          deviceEventClassId(std::exchange(other.deviceEventClassId, "")),
          name(std::exchange(other.name, "")),
          severity(std::exchange(other.severity, Severity::Undefined))
    {
    }

    // Move assignment
    CEFEvent& operator=(CEFEvent&& other) noexcept;

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

bool operator==(const CEFEvent& left, const CEFEvent& right);

bool operator!=(const CEFEvent& left, const CEFEvent& right);