include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG 52eb8108c5bdec04579160ae17225d66034bd723 # v1.17.0
        GIT_SHALLOW ON
        FIND_PACKAGE_ARGS NAMES GTest)

# For Windows: prevent overriding the parent project's compiler/linker settings
option(gtest_force_shared_crt ON)
option(INSTALL_GTEST OFF)

FetchContent_MakeAvailable(googletest)
