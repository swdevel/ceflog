/**
 * @file CEFEventStringSerializer.h
 * @author Alexander Borisov
 * @brief Файл содержит объявление класса для сериализации CEFEvent в строковое представление
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

class CEFEventStringSerializer : protected CEFEventAbstractSerializer<std::string>
{
public:
    virtual std::string Serialize(const CEFEvent& event) const override;
};

} // namespace ceflog::event