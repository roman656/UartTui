set(VIEW_LIB_NAME "ViewLib")
set(VIEW_LIB_HEADERS "${VIEW_LIB_NAME}_HEADERS")
set(VIEW_LIB_SOURCES "${VIEW_LIB_NAME}_SOURCES")

file(GLOB_RECURSE VIEW_LIB_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
file(GLOB_RECURSE VIEW_LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(${VIEW_LIB_NAME} ${VIEW_LIB_SOURCES} ${VIEW_LIB_HEADERS})
add_library(${PROJECT_NAME}::${VIEW_LIB_NAME} ALIAS ${VIEW_LIB_NAME})

set_target_properties(${VIEW_LIB_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO)

include(AddFTXUI)
target_link_libraries(${VIEW_LIB_NAME}
        PUBLIC
                ftxui::screen
                ftxui::component
                ftxui::dom
        PRIVATE
                ${PROJECT_NAME}::ProjectSettings)

target_include_directories(${VIEW_LIB_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
