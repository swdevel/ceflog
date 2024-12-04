/**
 * @file CEFEvent.h
 * @author Alexander Borisov
 * @brief Файл содержит описание класса для работы с событиями в формате "Common Event Format (CEF)"
 * @version 0.1
 * @date 2024-11-14
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace ceflog::event
{

#include "EnumClassMacro.h"

ENUM_CLASS_MACRO(CEFSeverity, Undefined, Low, Medium, High, VeryHigh);

/**
 * @brief Версия формата CEF (Common Event Format) по умолчанию
 *
 */
const uint8_t CEF_DEFAULT_FORMAT_VERSION = 0;

/**
 * @brief Структура для описания пары "ключ-значение"
 *
 */
struct CEFEventExtension {
    std::string key;
    std::string value;
};

/**
 * @brief Класс для работы с событиями в формате CEF (Common Event Format)
 *
 */
class CEFEvent
{
public:
    ~CEFEvent() = default;

    CEFEvent(const uint8_t formatVersion = CEF_DEFAULT_FORMAT_VERSION,
             const std::string& deviceVendor = "",
             const std::string& deviceProduct = "",
             const std::string& deviceVersion = "",
             const std::string& deviceEventClassId = "",
             const std::string& name = "",
             CEFSeverity severity = CEFSeverity::Undefined,
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
        : formatVersion(std::exchange(other.formatVersion, CEF_DEFAULT_FORMAT_VERSION)),
          deviceVendor(std::exchange(other.deviceVendor, "")),
          deviceProduct(std::exchange(other.deviceProduct, "")),
          deviceVersion(std::exchange(other.deviceVersion, "")),
          deviceEventClassId(std::exchange(other.deviceEventClassId, "")),
          name(std::exchange(other.name, "")),
          severity(std::exchange(other.severity, CEFSeverity::Undefined)),
          extensions(std::exchange(other.extensions, {}))
    {
    }

    // Move assignment
    CEFEvent& operator=(CEFEvent&& other) noexcept;

    /**
     * @brief Метод для присвоения значения версии формата CEF
     *
     * @param[in] version Идентификатор версии формата CEF
     * Например, для версии спецификации "1.2", значение будет равно "1"
     */
    void SetFormatVersion(const uint8_t version) noexcept;

    /**
     * @brief Метод для получения версии формата CEF
     *
     * @return uint8_t Целочисленный идентификатор версии формата CEF
     */
    uint8_t GetFormatVersion() const noexcept;

    /**
     * @brief Метод для присвоения значения идентификатора производителя
     *
     * @param value Строка-идентификатор производителя
     */
    void SetDeviceVendor(const std::string& value) noexcept;

    /**
     * @brief Метод для получения идентификатора производителя
     *
     * @param[in] formatString Признак того, что в возвращаемой строке символы должны быть экранированы согласно спецификации формата
     *
     * @return std::string Строка-идентификатор производителя
     */
    std::string GetDeviceVendor(const bool formatString = false) const noexcept;

    /**
     * @brief Метод для присвоения значения идентификатора продукта
     *
     * @param value Строка-идентификатор продукта
     */
    void SetDeviceProduct(const std::string& value) noexcept;

    /**
     * @brief Метод для получения идентификатора продукта
     *
     * @param[in] formatString Признак того, что в возвращаемой строке символы должны быть экранированы согласно спецификации формата
     *
     * @return std::string Строка-идентификатор продукта
     */
    std::string GetDeviceProduct(const bool formatString = false) const noexcept;

    /**
     * @brief Метод для присвоения значения идентификатора версии продукта
     *
     * @param value Строка-идентификатор версии продукта
     */
    void SetDeviceVersion(const std::string& value) noexcept;

    /**
     * @brief Метод для получения идентификатора версии продукта
     *
     * @param[in] formatString Признак того, что в возвращаемой строке символы должны быть экранированы согласно спецификации формата
     *
     * @return std::string Строка-идентификатор версии продукта
     */
    std::string GetDeviceVersion(const bool formatString = false) const noexcept;

    /**
     * @brief Метод для присвоения значения идентификатора типа события
     *
     * @param value Строка-идентификатор типа события
     */
    void SetDeviceEventClassId(const std::string& value) noexcept;

    /**
     * @brief Метод для получения идентификатора типа события
     *
     * @param[in] formatString Признак того, что в возвращаемой строке символы должны быть экранированы согласно спецификации формата
     *
     * @return std::string Строка-идентификатор типа события
     */
    std::string GetDeviceEventClassId(const bool formatString = false) const noexcept;

    /**
     * @brief Метод для присвоения значения описания события
     *
     * @param value Строка для описания события
     */
    void SetName(const std::string& value) noexcept;

    /**
     * @brief Метод для получения описания события
     *
     * @param[in] formatString Признак того, что в возвращаемой строке символы должны быть экранированы согласно спецификации формата
     *
     * @return std::string Строка с описанием события
     */
    std::string GetName(const bool formatString = false) const noexcept;

    /**
     * @brief Метод для присвоения идентификатора важности события
     *
     * @param value Идентификатор важности события, допустимые значения перечислены в ENUM_CLASS_MACRO(CEFSeverity, ...)
     */
    void SetSeverity(const CEFSeverity& value) noexcept;

    /**
     * @brief Метод для получения идентификатора важности события
     *
     * @return Severity Идентификатор важности события, допустимые значения перечислены в ENUM_CLASS_MACRO(Severity, ...)
     */
    CEFSeverity GetSeverity() const noexcept;

    /**
     * @brief Метод для добавления пары "ключ-значение", служащей для расширения базового формата события
     *
     * @param extension Пара "ключ-значение", описанная в структуре CEFEventExtension
     */
    void PushExtension(const CEFEventExtension& extension) noexcept;

    /**
     * @brief Метод для получения набора пар "ключ-значение", служащих для расширения базового формата события
     *
     * @return std::vector<CEFEventExtension> Контейнер для структур CEFEventExtension
     */
    std::vector<CEFEventExtension> GetExtensions() const noexcept;

    /**
     * @brief Метод для получения набора пар "ключ-значение" в строковом представлении
     *
     * @param[in] formatString Признак того, что в возвращаемой строке символы должны быть экранированы согласно спецификации формата
     * @return std::string Строка с парами "ключ-значение"
     */
    std::string GetExtensionsAsString(const bool formatString = false) const noexcept;

private:
    enum class Location {
        Header,
        Extension
    };

    std::string EscapeCharactersIfPresent(const std::string& string, const Location location) const noexcept;

private:
    /**
     * @brief Версия формата CEF
     *
     */
    uint8_t formatVersion;

    /**
     * @brief Идентификатор производителя
     *
     */
    std::string deviceVendor;

    /**
     * @brief Идентификатор продукта
     *
     */
    std::string deviceProduct;

    /**
     * @brief Идентификатор версии продукта
     *
     */
    std::string deviceVersion;

    /**
     * @brief Уникальный идентификатор типа события
     *
     */
    std::string deviceEventClassId;

    /**
     * @brief Понятное человеку описание события
     *
     */
    std::string name;

    /**
     * @brief Важность события
     *
     */
    CEFSeverity severity;

    /**
     * @brief Набор пар "ключ-значение" для расширения базового формата события
     *
     */
    std::vector<CEFEventExtension> extensions;
};

bool operator==(const CEFEvent& left, const CEFEvent& right);

bool operator!=(const CEFEvent& left, const CEFEvent& right);

std::ostream& operator<<(std::ostream& os, const CEFEvent& event);

} // namespace ceflog::event