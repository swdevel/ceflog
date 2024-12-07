/**
 * @file EnumClassMacro.h
 * @author Alexander Borisov
 * @brief Файл содержит макрос для определения enum class с функций преобразования значений в текстовое представление
 * @version 0.1
 * @date 2024-12-07
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include <boost/preprocessor.hpp>

namespace ceflog::common
{

#define PROCESS_ONE_ELEMENT(r, unused, idx, elem) \
    BOOST_PP_COMMA_IF(idx)                        \
    BOOST_PP_STRINGIZE(elem)

#define ENUM_CLASS_MACRO(name, ...)                                        \
    enum class name {                                                      \
        __VA_ARGS__                                                        \
    };                                                                     \
    static const char *name##Strings[] = {BOOST_PP_SEQ_FOR_EACH_I(         \
        PROCESS_ONE_ELEMENT, % %, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))}; \
    template <typename T>                                                  \
    constexpr const char *name##ToString(T value)                          \
    {                                                                      \
        return name##Strings[static_cast<int>(value)];                     \
    }

} // namespace ceflog::common