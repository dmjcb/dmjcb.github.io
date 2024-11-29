cmake_minimum_required(VERSION 3.16)
 
project(HelloAPI)

add_library(${PROJECT_NAME} SHARED "")

target_sources(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/HelloAPI.cpp)