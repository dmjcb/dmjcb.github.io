cmake_minimum_required(VERSION 3.16)
project(static_api)

add_library(${PROJECT_NAME} STATIC "")
target_sources(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/static_api.cpp)