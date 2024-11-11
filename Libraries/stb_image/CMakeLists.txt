cmake_minimum_required(VERSION 3.5)

project(stb_image)

add_library(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE "src/stb_image")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
