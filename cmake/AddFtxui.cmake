include(FetchContent)

FetchContent_Declare(
        ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
        GIT_TAG 5cfed50702f52d51c1b189b5f97f8beaf5eaa2a6 # v6.1.9
        GIT_SHALLOW ON
        FIND_PACKAGE_ARGS NAMES ftxui)

option(FTXUI_ENABLE_INSTALL OFF)

FetchContent_MakeAvailable(ftxui)
