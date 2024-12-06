cmake_minimum_required(VERSION 3.17)
project(main)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH  ${CMAKE_SOURCE_DIR}/cmake)

# 导入FMT.cmake模块
include(FMT)

add_executable(${PROJECT_NAME} "")

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/extern/fmt/include
)

target_sources(${PROJECT_NAME} PUBLIC
    main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    ${FMT_LIB}::${FMT_LIB}
)