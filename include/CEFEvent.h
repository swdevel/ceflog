#pragma once

#include <cstdint>
#include <string>
#include <utility>

#include "CEFLogMacro.h"

ENUM_CLASS_MACRO(Severity, Undefined, Low, Medium, High, VeryHigh);

#define CEF_EVENT_DEFAULT_FORMAT_VERSION 0

struct CEFEventExtension
{
    std::string key;
    std::string value;
};

class CEFEvent
{
public:
    ~CEFEvent() = default;

    CEFEvent(const uint8_t formatVersion = CEF_EVENT_DEFAULT_FORMAT_VERSION,
             const std::string& deviceVendor = "",
             const std::string& deviceProduct = "",
             const std::string& deviceVersion = "",
             const std::string& deviceEventClassId = "",
             const std::string& name = "",
             Severity severity = Severity::Undefined,
             const std::vector<CEFEventExtension>& extensions = {})
        : formatVersion(formatVersion),
          deviceVendor(deviceVendor),
          deviceProduct(deviceProduct),
          deviceVersion(deviceVersion),
          deviceEventClassId(deviceEventClassId),
          name(name),
          severity(severity),
          extensions(extensions)
    {
    }

    // Copy constructor
    CEFEvent(const CEFEvent& other)
        : CEFEvent(other.formatVersion,
                   other.deviceVendor,
                   other.deviceProduct,
                   other.deviceVersion,
                   other.deviceEventClassId,
                   other.name,
                   other.severity,
                   other.extensions)
    {
    }

    // Copy assignment
    CEFEvent& operator=(const CEFEvent& other);

    // Move constructor
    CEFEvent(CEFEvent&& other) noexcept
        : formatVersion(std::exchange(other.formatVersion, CEF_EVENT_DEFAULT_FORMAT_VERSION)),
          deviceVendor(std::exchange(other.deviceVendor, "")),
          deviceProduct(std::exchange(other.deviceProduct, "")),
          deviceVersion(std::exchange(other.deviceVersion, "")),
          deviceEventClassId(std::exchange(other.deviceEventClassId, "")),
          name(std::exchange(other.name, "")),
          severity(std::exchange(other.severity, Severity::Undefined)),
          extensions(std::exchange(other.extensions, {}))
    {
    }

    // Move assignment
    CEFEvent& operator=(CEFEvent&& other) noexcept;

    void SetFormatVersion(const uint8_t version) noexcept;

    uint8_t GetFormatVersion() const noexcept;

    void SetDeviceVendor(const std::string& value) noexcept;

    std::string GetDeviceVendor(const bool formatString = false) const noexcept;

    void SetDeviceProduct(const std::string& value) noexcept;

    std::string GetDeviceProduct(const bool formatString = false) const noexcept;

    void SetDeviceVersion(const std::string& value) noexcept;

    std::string GetDeviceVersion(const bool formatString = false) const noexcept;

    void SetDeviceEventClassId(const std::string& value) noexcept;

    std::string GetDeviceEventClassId(const bool formatString = false) const noexcept;

    void SetName(const std::string& value) noexcept;

    std::string GetName(const bool formatString = false) const noexcept;

    void SetSeverity(const Severity& value) noexcept;

    Severity GetSeverity() const noexcept;

    void PushExtension(const CEFEventExtension& extension) noexcept;

    std::vector<CEFEventExtension> GetExtensions() const noexcept;

    std::string GetExtensionsAsString(const bool formatString = false) const noexcept;

private:
    enum class Location
    {
        Header,
        Extension
    };

    std::string EscapeCharactersIfPresent(const std::string& string, const Location location) const noexcept;

private:
    uint8_t formatVersion;

    std::string deviceVendor;

    std::string deviceProduct;

    std::string deviceVersion;

    std::string deviceEventClassId;

    std::string name;

    Severity severity;

    std::vector<CEFEventExtension> extensions;
};

bool operator==(const CEFEvent& left, const CEFEvent& right);

bool operator!=(const CEFEvent& left, const CEFEvent& right);

std::ostream& operator<<(std::ostream& os, const CEFEvent& event);