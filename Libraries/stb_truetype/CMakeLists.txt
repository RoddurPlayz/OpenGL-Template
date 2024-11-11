cmake_minimum_required(VERSION 3.5)

project(stb_truetype)

add_library(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE "src/stb_truetype")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
