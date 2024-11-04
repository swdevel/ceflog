cmake_minimum_required(VERSION 3.0...3.28)

project(ceflog)
set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(ceflog STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ceflog.cpp
)

if (BUILD_TESTS)
    message("Build unit tests: on")

    add_executable(tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/main.cpp
    )

    target_link_libraries(tests ceflog gtest pthread)
else()
    message("Build unit tests: off")
endif()

if (BUILD_EXAMPLES)
    message("Build examples: on")

    # TODO: ...

else()
    message("Build examples: off")
endif()