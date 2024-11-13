#include "CEFEvent.h"

// Copy assignment
CEFEvent& CEFEvent::operator=(const CEFEvent& other)
{
    if (this == &other) {
        return *this;
    }

    CEFEvent temp(other); // Use the copy constructor

    std::swap(formatVersion, temp.formatVersion);
    std::swap(deviceVendor, temp.deviceVendor);
    std::swap(deviceProduct, temp.deviceProduct);
    std::swap(deviceVersion, temp.deviceVersion);
    std::swap(deviceEventClassId, temp.deviceEventClassId);
    std::swap(name, temp.name);
    std::swap(severity, temp.severity);

    return *this;
}

// Move assignment
CEFEvent& CEFEvent::operator=(CEFEvent&& other) noexcept
{
    CEFEvent temp(std::move(other));

    std::swap(formatVersion, temp.formatVersion);
    std::swap(deviceVendor, temp.deviceVendor);
    std::swap(deviceProduct, temp.deviceProduct);
    std::swap(deviceVersion, temp.deviceVersion);
    std::swap(deviceEventClassId, temp.deviceEventClassId);
    std::swap(name, temp.name);
    std::swap(severity, temp.severity);

    return *this;
}

void CEFEvent::SetFormatVersion(const uint8_t version) noexcept
{
    formatVersion = version;
}

uint8_t CEFEvent::GetFormatVersion() const noexcept
{
    return formatVersion;
}

void CEFEvent::SetDeviceVendor(const std::string& value) noexcept
{
    deviceVendor = value;
}

std::string CEFEvent::GetDeviceVendor() const noexcept
{
    return deviceVendor;
}

void CEFEvent::SetDeviceProduct(const std::string& value) noexcept
{
    deviceProduct = value;
}

std::string CEFEvent::GetDeviceProduct() const noexcept
{
    return deviceProduct;
}

void CEFEvent::SetDeviceVersion(const std::string& value) noexcept
{
    deviceVersion = value;
}

std::string CEFEvent::GetDeviceVersion() const noexcept
{
    return deviceVersion;
}

void CEFEvent::SetDeviceEventClassId(const std::string& value) noexcept
{
    deviceEventClassId = value;
}

std::string CEFEvent::GetDeviceEventClassId() const noexcept
{
    return deviceEventClassId;
}

void CEFEvent::SetName(const std::string& value) noexcept
{
    name = value;
}

std::string CEFEvent::GetName() const noexcept
{
    return name;
}

void CEFEvent::SetSeverity(const Severity& value) noexcept
{
    severity = value;
}

Severity CEFEvent::GetSeverity() const noexcept
{
    return severity;
}

bool operator==(const CEFEvent& left, const CEFEvent& right)
{
    return (left.GetFormatVersion() == right.GetFormatVersion() &&
            left.GetDeviceVendor() == right.GetDeviceVendor() &&
            left.GetDeviceProduct() == right.GetDeviceProduct() &&
            left.GetDeviceVersion() == right.GetDeviceVersion() &&
            left.GetDeviceEventClassId() == right.GetDeviceEventClassId() &&
            left.GetName() == right.GetName() &&
            left.GetSeverity() == right.GetSeverity());
}

bool operator!=(const CEFEvent& left, const CEFEvent& right)
{
    return (left.GetFormatVersion() != right.GetFormatVersion() ||
            left.GetDeviceVendor() != right.GetDeviceVendor() ||
            left.GetDeviceProduct() != right.GetDeviceProduct() ||
            left.GetDeviceVersion() != right.GetDeviceVersion() ||
            left.GetDeviceEventClassId() != right.GetDeviceEventClassId() ||
            left.GetName() != right.GetName() ||
            left.GetSeverity() != right.GetSeverity());
}

std::ostream& operator<<(std::ostream& os, const CEFEvent& event)
{
    const auto prefix = std::string("CEF:") + std::to_string(event.GetFormatVersion());
    const auto severity = std::string(SeverityToString(event.GetSeverity()));
    const char delimiter = '|';

    os << prefix + delimiter;
    os << event.GetDeviceVendor() + delimiter;
    os << event.GetDeviceProduct() + delimiter;
    os << event.GetDeviceVersion() + delimiter;
    os << event.GetDeviceEventClassId() + delimiter;
    os << event.GetName() + delimiter;
    os << severity + delimiter;

    return os;
}