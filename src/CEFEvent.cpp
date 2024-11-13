/**
 * @file CEFEvent.cpp
 * @author Alexander Borisov
 * @brief Файл содержит реализацию класса для работы с событиями в формате "Common Event Format (CEF)"
 * @version 0.1
 * @date 2024-11-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <boost/algorithm/string.hpp>

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
    std::swap(extensions, temp.extensions);

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
    std::swap(extensions, temp.extensions);

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

std::string CEFEvent::GetDeviceVendor(const bool formatString) const noexcept
{
    return formatString ? EscapeCharactersIfPresent(deviceVendor, Location::Header) : deviceVendor;
}

void CEFEvent::SetDeviceProduct(const std::string& value) noexcept
{
    deviceProduct = value;
}

std::string CEFEvent::GetDeviceProduct(const bool formatString) const noexcept
{
    return formatString ? EscapeCharactersIfPresent(deviceProduct, Location::Header) : deviceProduct;
}

void CEFEvent::SetDeviceVersion(const std::string& value) noexcept
{
    deviceVersion = value;
}

std::string CEFEvent::GetDeviceVersion(const bool formatString) const noexcept
{
    return formatString ? EscapeCharactersIfPresent(deviceVersion, Location::Header) : deviceVersion;
}

void CEFEvent::SetDeviceEventClassId(const std::string& value) noexcept
{
    deviceEventClassId = value;
}

std::string CEFEvent::GetDeviceEventClassId(const bool formatString) const noexcept
{
    return formatString ? EscapeCharactersIfPresent(deviceEventClassId, Location::Header) : deviceEventClassId;
}

void CEFEvent::SetName(const std::string& value) noexcept
{
    name = value;
}

std::string CEFEvent::GetName(const bool formatString) const noexcept
{
    return formatString ? EscapeCharactersIfPresent(name, Location::Header) : name;
}

void CEFEvent::SetSeverity(const Severity& value) noexcept
{
    severity = value;
}

Severity CEFEvent::GetSeverity() const noexcept
{
    return severity;
}

void CEFEvent::PushExtension(const CEFEventExtension& extension) noexcept
{
    extensions.push_back(extension);
}

std::vector<CEFEventExtension> CEFEvent::GetExtensions() const noexcept
{
    return extensions;
}

std::string CEFEvent::GetExtensionsAsString(const bool formatString) const noexcept
{
    const char delimiter = ' ';
    std::string result;

    /*
        В документации сказано:

        An event can contain any number of key-value pairs in any order, separated by spaces (" ").
        If a field contains a space, such as a file name, this is valid and can be logged in exactly
        that manner, as shown in the following example:

        filePath=/user/username/dir/my file name.txt
    */

    for (const auto& entry : extensions) {

        const auto key = formatString ? EscapeCharactersIfPresent(entry.key, Location::Extension) : entry.key;
        const auto value = formatString ? EscapeCharactersIfPresent(entry.value, Location::Extension) : entry.value;

        if (!result.empty()) {
            result += delimiter;
        }

        result += key + "=" + value;
    }

    return result;
}

std::string CEFEvent::EscapeCharactersIfPresent(const std::string& string, const Location location) const noexcept
{
    if (string.empty()) {
        return string;
    }

    /*
        В документации сказано:

        If a backslash (\) is used in the header or the extension, it must be escaped with
        another backslash (\).

        If a pipe (|) is used in the header, it must be escaped with a backslash (\). But note
        that the pipes in the extension do not need escaping.

        If an equal sign (=) is used in the extensions, it has to be escaped with a backslash (\).
        Equal signs in the header need no escaping.
    */

    std::vector<char> charactersToEscape = {'\\'};
    location == Location::Header ? charactersToEscape.push_back('|') : charactersToEscape.push_back('=');

    std::string result(string);

    for (const auto& entry : charactersToEscape) {

        const auto search = std::string(1, entry);
        const auto replace = '\\' + search;

        boost::replace_all(result, search, replace);
    }

    return result;
}

static bool ExtensionsAreEqual(const std::vector<CEFEventExtension>& left,
                               const std::vector<CEFEventExtension>& right)
{
    return std::equal(left.begin(), left.end(),
                      right.begin(), right.end(),
                      [](auto const& l, auto const& r) {
                          return (l.key == r.key) && (l.value == r.value);
                      });
}

bool operator==(const CEFEvent& left, const CEFEvent& right)
{
    return (left.GetFormatVersion() == right.GetFormatVersion() &&
            left.GetDeviceVendor() == right.GetDeviceVendor() &&
            left.GetDeviceProduct() == right.GetDeviceProduct() &&
            left.GetDeviceVersion() == right.GetDeviceVersion() &&
            left.GetDeviceEventClassId() == right.GetDeviceEventClassId() &&
            left.GetName() == right.GetName() &&
            left.GetSeverity() == right.GetSeverity() &&
            ExtensionsAreEqual(left.GetExtensions(), right.GetExtensions()) == true);
}

bool operator!=(const CEFEvent& left, const CEFEvent& right)
{
    return (left.GetFormatVersion() != right.GetFormatVersion() ||
            left.GetDeviceVendor() != right.GetDeviceVendor() ||
            left.GetDeviceProduct() != right.GetDeviceProduct() ||
            left.GetDeviceVersion() != right.GetDeviceVersion() ||
            left.GetDeviceEventClassId() != right.GetDeviceEventClassId() ||
            left.GetName() != right.GetName() ||
            left.GetSeverity() != right.GetSeverity() ||
            ExtensionsAreEqual(left.GetExtensions(), right.GetExtensions()) == false);
}

std::ostream& operator<<(std::ostream& os, const CEFEvent& event)
{
    const auto prefix = std::string("CEF:") + std::to_string(event.GetFormatVersion());
    const auto severity = std::string(SeverityToString(event.GetSeverity()));
    const char delimiter = '|';

    os << prefix + delimiter;
    os << event.GetDeviceVendor(true) + delimiter;
    os << event.GetDeviceProduct(true) + delimiter;
    os << event.GetDeviceVersion(true) + delimiter;
    os << event.GetDeviceEventClassId(true) + delimiter;
    os << event.GetName(true) + delimiter;
    os << severity + delimiter;

    if (!event.GetExtensions().empty()) {
        os << event.GetExtensionsAsString(true);
    }

    return os;
}