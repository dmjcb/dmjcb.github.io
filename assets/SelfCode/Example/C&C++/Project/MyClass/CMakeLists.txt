cmake_minimum_required(VERSION 3.16)

project(TemplateClassDemo)

set(LIB_NAME               MyClassDLL)
set(LIBRARY_OUTPUT_PATH    ${CMAKE_BINARY_DIR}/Lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/Bin)

add_library(${LIB_NAME} SHARED "")

target_include_directories(${LIB_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/Include
)

target_sources(${LIB_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/Source/MyClass.cpp
    ${CMAKE_SOURCE_DIR}/Source/MyClassDLL.cpp
)


add_executable(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/Include
)

target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/Main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${LIB_NAME}
)
