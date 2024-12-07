cmake_minimum_required(VERSION 3.16)
project(class_api)

add_library(${PROJECT_NAME} SHARED "")
target_sources(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/class_api.cpp)

add_executable(main main.cpp)
target_link_libraries(main ${PROJECT_NAME})