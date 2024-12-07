/**
 * @file CEFEventFactory.h
 * @author Alexander Borisov
 * @brief Файл содержит объявление класса для создания объектов с описанием событий в формате "CEF (Common Event Format)"
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

/**
 * @brief Класс для создания объектов с описанием событий в формате "CEF (Common Event Format)"
 *
 */
class CEFEventFactory
{
public:
    /**
     * @brief Конструктор класса
     *
     * @param formatVersion Версия формата "CEF (Common Event Format)"
     * @param deviceVendor Идентификатор производителя
     * @param deviceProduct Идентификатор продукта
     * @param deviceVersion Идентификатор версии продукта
     */
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

    /**
     * @brief Метод для создания объекта c описанием события в формате "CEF (Common Event Format)"
     *
     * @param deviceEventClassId Уникальный идентификатор типа события
     * @param name Понятное человеку описание события
     * @param severity Важность события
     * @param extensions Набор пар "ключ-значение" для расширения базового формата события
     *
     * @return CEFEvent объект с описанием события в формате "CEF (Common Event Format)"
     */
    CEFEvent CreateEvent(const std::string& deviceEventClassId,
                         const std::string& name,
                         const CEFSeverity severity,
                         const std::vector<CEFEventExtension>& extensions = {}) const noexcept;

private:
    /**
     * @brief Версия формата "CEF (Common Event Format)"
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
};

} // namespace ceflog::event