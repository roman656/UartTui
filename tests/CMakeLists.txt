set(TESTS_EXECUTABLE_NAME "${PROJECT_NAME}Tests")
set(TESTS_EXECUTABLE_SOURCES "${TESTS_EXECUTABLE_NAME}_SOURCES")

file(GLOB_RECURSE TESTS_EXECUTABLE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.test.cpp")

add_executable(${TESTS_EXECUTABLE_NAME} ${TESTS_EXECUTABLE_SOURCES})

set_target_properties(${TESTS_EXECUTABLE_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO)

include(AddGoogleTest)
target_link_libraries(${TESTS_EXECUTABLE_NAME} PRIVATE
        ${PROJECT_NAME}::PacketLib
        ${PROJECT_NAME}::ProjectSettings
        GTest::gtest_main
        GTest::gmock)

include(GoogleTest)
gtest_discover_tests(${TESTS_EXECUTABLE_NAME})
