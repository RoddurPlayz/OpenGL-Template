cmake_minimum_required(VERSION 3.5)


project(Miniaudio)
add_library(miniaudio INTERFACE)

target_include_directories(miniaudio INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
