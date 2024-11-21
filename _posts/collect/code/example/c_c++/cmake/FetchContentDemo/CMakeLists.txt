cmake_minimum_required(VERSION 3.17)
project(Main)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH  ${CMAKE_SOURCE_DIR}/CMake)

# 导入FMT.cmake模块
include(FMT)

add_executable(${PROJECT_NAME} "")

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/Extern/fmt/include
)

target_sources(${PROJECT_NAME} PUBLIC
    Main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    ${FMT_LIB}::${FMT_LIB}
)