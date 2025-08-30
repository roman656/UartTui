cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

project(UartTui
        VERSION 0.0.1
        DESCRIPTION "Test application with terminal UI and UART"
        LANGUAGES CXX)

option(UART_TUI_BUILD_TESTS "Build tests. This requires Google Test to be available" OFF)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

include(NoInSourceBuilds)
include(ProjectSettings)

add_subdirectory(src)

if(PROJECT_IS_TOP_LEVEL)
    if(UART_TUI_BUILD_TESTS)
        include(CTest)
        add_subdirectory(tests)
    endif()
endif()
