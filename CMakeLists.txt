cmake_minimum_required(VERSION 3.0...3.28)

project(ceflog)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

#
# Boost::log required boost version >= 1.54.0
#
set(Boost_USE_STATIC_LIBS on)

find_package(Boost 1.54.0 REQUIRED COMPONENTS log)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif()

add_library(ceflog STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CEFEvent.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CEFEventFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CEFEventStringSerializer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SyslogBoostClientBackend.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SyslogAsyncClient.cpp
)

if (BUILD_TESTS)
    message("Build unit tests: on")

    add_executable(unit-tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/unit/CEFEventTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/unit/CEFEventFactoryTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/unit/CEFEventStringSerializerTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/unit/SyslogBoostClientBackendTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/unit/main.cpp
    )

    target_link_libraries(unit-tests ceflog Boost::log gtest pthread)

    add_executable(integration-tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/integration/SyslogAsyncClientTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/integration/main.cpp
    )

    target_link_libraries(integration-tests ceflog Boost::log gtest pthread)

else()
    message("Build unit tests: off")
endif()

if (BUILD_EXAMPLES)
    message("Build examples: on")

    add_executable(generator
        ${CMAKE_CURRENT_SOURCE_DIR}/examples/generator/main.cpp
    )
    target_link_libraries(generator ceflog)

    add_executable(local_syslogger
        ${CMAKE_CURRENT_SOURCE_DIR}/examples/local_syslogger/main.cpp
    )
    target_link_libraries(local_syslogger ceflog Boost::log)

else()
    message("Build examples: off")
endif()