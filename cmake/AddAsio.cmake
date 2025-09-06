include(FetchContent)

FetchContent_Declare(
        asio
        GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
        GIT_TAG 231cb29bab30f82712fcd54faaea42424cc6e710 # 1.36.0
        GIT_SHALLOW ON
        FIND_PACKAGE_ARGS NAMES asio CONFIG)

FetchContent_MakeAvailable(asio)

if(NOT TARGET asio::asio AND NOT TARGET asio)
    add_library(asio INTERFACE)
    add_library(asio::asio ALIAS asio)

    # Most compilers do not issue warnings for system code
    # You can mark directory as SYSTEM to disable warnings that you can't influence
    target_include_directories(asio INTERFACE SYSTEM "${asio_SOURCE_DIR}/asio/include")
    target_compile_definitions(asio INTERFACE ASIO_STANDALONE ASIO_NO_DEPRECATED)
    target_compile_features(asio INTERFACE cxx_std_11)

    find_package(Threads REQUIRED)
    target_link_libraries(asio INTERFACE Threads::Threads)
endif()
