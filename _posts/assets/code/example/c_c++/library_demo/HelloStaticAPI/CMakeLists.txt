cmake_minimum_required(VERSION 3.16)
 
project(HelloStaticAPI)

add_library(${PROJECT_NAME} STATIC "")

target_sources(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/HelloStaticAPI.cpp)