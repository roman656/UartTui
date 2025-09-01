set(PORT_LIB_NAME "PortLib")
set(PORT_LIB_HEADERS "${PORT_LIB_NAME}_HEADERS")
set(PORT_LIB_SOURCES "${PORT_LIB_NAME}_SOURCES")

file(GLOB_RECURSE PORT_LIB_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
file(GLOB_RECURSE PORT_LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(${PORT_LIB_NAME} ${PORT_LIB_SOURCES} ${PORT_LIB_HEADERS})
add_library(${PROJECT_NAME}::${PORT_LIB_NAME} ALIAS ${PORT_LIB_NAME})

set_target_properties(${PORT_LIB_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO)

include(AddAsio)
target_link_libraries(${PORT_LIB_NAME}
        PUBLIC
                asio::asio
        PRIVATE
                ${PROJECT_NAME}::ProjectSettings)

target_include_directories(${PORT_LIB_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
