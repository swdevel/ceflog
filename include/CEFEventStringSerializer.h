/**
 * @file CEFEventStringSerializer.h
 * @author Alexander Borisov
 * @brief Файл содержит объявление класса для сериализации CEFEvent в std::string
 * @version 0.1
 * @date 2024-12-07
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include "CEFEventAbstractSerializer.h"

namespace ceflog::event
{

/**
 * @brief Класс для сериализации CEFEvent в std::string
 *
 */
class CEFEventStringSerializer : protected CEFEventAbstractSerializer<std::string>
{
public:
    /**
     * @brief Метод для сериализации CEFEvent в std::string
     *
     * @param[in] event Константная ссылка на объект CEFEvent
     *
     * @return std::string Представление объекта CEFEvent в виде std::string
     */
    virtual std::string Serialize(const CEFEvent& event) const override;
};

} // namespace ceflog::event