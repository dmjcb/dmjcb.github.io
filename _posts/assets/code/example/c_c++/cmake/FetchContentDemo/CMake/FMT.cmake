include(FetchContent)

set(FMT_LIB fmt)

FetchContent_Declare(${FMT_LIB}
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG        9.1.0
    SOURCE_DIR     ${CMAKE_SOURCE_DIR}/Extern/${FMT_LIB}
)

FetchContent_MakeAvailable(${FMT_LIB})