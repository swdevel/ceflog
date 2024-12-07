/**
 * @file CEFEventStringSerializer.cpp
 * @author Alexander Borisov
 * @brief Файл содержит определение функций класса для сериализации CEFEvent в строковое представление
 * @version 0.1
 * @date 2024-12-07
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <sstream>

#include "CEFEventStringSerializer.h"

namespace ceflog::event
{

std::string CEFEventStringSerializer::Serialize(const CEFEvent& event) const
{
    std::ostringstream oss;
    oss << event;

    return oss.str();
}

} // namespace ceflog::event