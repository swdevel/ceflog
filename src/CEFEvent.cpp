#include "CEFEvent.h"

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