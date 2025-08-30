add_library(ProjectSettings INTERFACE)
add_library(${PROJECT_NAME}::ProjectSettings ALIAS ProjectSettings)

target_compile_options(ProjectSettings INTERFACE
        $<$<CXX_COMPILER_ID:GNU>:
                -Wall -Wextra -Wpedantic
                -Wconversion -Wsign-conversion -Wshadow -Wcast-align
                -Wold-style-cast -Wnon-virtual-dtor -Woverloaded-virtual
                -Wstrict-null-sentinel -Wduplicated-cond -Wduplicated-branches
                -Wlogical-op -Wnull-dereference -Wformat=2 -Wundef>
        $<$<CXX_COMPILER_ID:Clang>:
                -Wall -Wextra -Wpedantic
                -Wconversion -Wsign-conversion -Wshadow -Wcast-align
                -Wold-style-cast -Wnon-virtual-dtor -Woverloaded-virtual
                -Wstrict-null-sentinel -Wduplicated-cond -Wduplicated-branches
                -Wlogical-op -Wnull-dereference -Wformat=2 -Wundef>
        $<$<CXX_COMPILER_ID:MSVC>:
                /W4 /WX>)
