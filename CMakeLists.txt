# Set the minimum version which is required to run this cmake project
cmake_minimum_required(VERSION 3.5)


# Create a project
project(OpenGL-Template)

# Notify about the compiler
if(MSVC)
    message(STATUS "Compiler: MSVC")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Compiler: g++")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS "Compiler: clang++")
endif()

if(NOT MSVC)
    # Choose a Build Type
    set(BUILD_TYPE "Debug")
    if(BUILD_TYPE STREQUAL "Debug")
        message(STATUS "Build Type: Debug")
        add_compile_options(-g)
    elseif(BUILD_TYPE STREQUAL "Release")
        message(STATUS "Build Type: Release")
        add_compile_options(-O3)
    elseif(BUILD_TYPE STREQUAL "RelWithDebInfo")
        message(STATUS "Build Type: Release with Debug Info")
        add_compile_options(-O2 -g)
    elseif(BUILD_TYPE STREQUAL "MinSizeRel")
        message(STATUS "Build Type: Min Size Release")
        add_compile_options(-Os)
    else()
        message(FATAL_ERROR "Unknown Build Type: ${BUILD_TYPE}")
    endif()

    # Choose a Build Architecture
    set(BUILD_ARCHITECTURE "x64")
    if(BUILD_ARCHITECTURE STREQUAL "x64")
        message(STATUS "Build Architecture: x64")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
        add_definitions(-DARCH_X64)
    elseif(BUILD_ARCHITECTURE STREQUAL "x86")
        message(STATUS "Build Architecture: x86")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
        add_definitions(-DARCH_X86)
    else()
        message(FATAL_ERROR "Unknown Build Architecture: ${BUILD_ARCHITECTURE}")
    endif()
endif()


# Add all directories with CMakeLists.txt files
add_subdirectory(Main)
add_subdirectory(Libraries/enet)
add_subdirectory(Libraries/glad)
# Set some GLFW flags
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(Libraries/glew)
add_subdirectory(Libraries/glfw)
add_subdirectory(Libraries/glm)
add_subdirectory(Libraries/imgui)
add_subdirectory(Libraries/miniaudio)
add_subdirectory(Libraries/stb_image)
add_subdirectory(Libraries/stb_truetype)
