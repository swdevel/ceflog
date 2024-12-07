/**
 * @file CEFEventAbstractSerializer.h
 * @author Alexander Borisov
 * @brief Файл содержит объявление виртуального класса для определения интерфейса сериализации CEFEvent
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

template <typename T>
class CEFEventAbstractSerializer
{
protected:
    virtual T Serialize(const CEFEvent& event) const = 0;

    virtual ~CEFEventAbstractSerializer() = default;
};

} // namespace ceflog::event