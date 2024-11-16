cmake_minimum_required(VERSION 3.0...3.28)

project(ceflog)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(ceflog STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CEFEvent.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CEFEventFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CEFEventStringSerializer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CEFLog.cpp

)

if (BUILD_TESTS)
    message("Build unit tests: on")

    add_executable(unit-tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/unit/CEFEventTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/unit/CEFEventFactoryTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/unit/CEFEventStringSerializerTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/unit/main.cpp
    )

    target_link_libraries(unit-tests ceflog gtest pthread)

    add_executable(integration-tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/integration/main.cpp
    )

    target_link_libraries(integration-tests ceflog gtest pthread)

else()
    message("Build unit tests: off")
endif()

if (BUILD_EXAMPLES)
    message("Build examples: on")

    add_executable(generator
        ${CMAKE_CURRENT_SOURCE_DIR}/examples/generator/main.cpp
    )
    target_link_libraries(generator ceflog)

else()
    message("Build examples: off")
endif()