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

    # Most compilers do not issue warnings for system code.
    # You can mark directory as SYSTEM to disable warnings that you can't influence
    target_include_directories(asio INTERFACE SYSTEM "${asio_SOURCE_DIR}/asio/include")
    target_compile_definitions(asio INTERFACE ASIO_STANDALONE ASIO_NO_DEPRECATED)
    target_compile_features(asio INTERFACE cxx_std_11)

    find_package(Threads REQUIRED)
    target_link_libraries(asio INTERFACE Threads::Threads)

    # When compiling for Windows using Microsoft Visual C++ or Borland C++,
    # asio will automatically link in the necessary Windows SDK libraries for sockets support
    # (i.e. ws2_32.lib and mswsock.lib, or ws2.lib when building for Windows CE).
    # But for other toolchains (e.g. MSYS2 MinGW/clang) this auto-linking is not provided,
    # which can lead to undefined reference to '__imp_WSAStartup'.
    # Therefore link ws2_32 explicitly
    if(WIN32)
        target_link_libraries(asio INTERFACE ws2_32)
    endif()
endif()
