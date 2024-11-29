# Set the minimum version which is required to run this cmake project
cmake_minimum_required(VERSION 3.5)

# Create a project
project(OpenGL-Template VERSION 0.0.0)
set(PROJECT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Main")

# Generate Compile Commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ Standard and make C++ Standard a Requirement
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add all directories with CMakeLists.txt files
# Set some Assimp flags
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
add_subdirectory(Libraries/assimp)
add_subdirectory(Libraries/enet)
add_subdirectory(Libraries/entt)
add_subdirectory(Libraries/glad)
# Set some GLFW flags
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(Libraries/glfw)
add_subdirectory(Libraries/glm)
add_subdirectory(Libraries/imgui)
add_subdirectory(Libraries/miniaudio)
add_subdirectory(Libraries/nlohmann_json)
# Set some OpenAL flags
set(LIBTYPE STATIC)
set(ALSOFT_UTILS OFF CACHE BOOL "" FORCE)
set(ALSOFT_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(Libraries/openal)
add_subdirectory(Libraries/stb_image)
add_subdirectory(Libraries/stb_truetype)
add_subdirectory(Libraries/yaml-cpp)

# Add the MSVC static runtime if using the MSVC compiler
if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
endif()


# Collect all Project Source Files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${PROJECT_DIRECTORY}/src/*.cpp")
message(STATUS "ALL PROJECT FILES: ${PROJECT_SOURCES}")

# Create an Executable
add_executable("${CMAKE_PROJECT_NAME}" ${PROJECT_SOURCES})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE "${PROJECT_DIRECTORY}/include")

# Link all Libraries
target_link_libraries(
    ${CMAKE_PROJECT_NAME} PRIVATE
    assimp enet entt glad glm imgui miniaudio nlohmann_json OpenAL stb_image stb_truetype yaml-cpp
)

# Add a macro for this project (This is required for GLM to allow experimental features)
target_compile_definitions(
    ${CMAKE_PROJECT_NAME}
    PRIVATE GLM_ENABLE_EXPERIMENTAL
    PRIVATE PROJECT_NAME="${CMAKE_PROJECT_NAME}"
    PRIVATE PROJECT_VERSION="${CMAKE_PROJECT_VERSION}"
)

set(ON_PRODUCTION OFF CACHE BOOL "The project is on production or not" FORCE)

# Notify about the Operating System
if(WIN32)
    message(STATUS "Operating System: Windows")
elseif(APPLE)
    message(STATUS "Operating System: MacOS")
elseif(LINUX)
    message(STATUS "Operating System: Linux")
endif()

# Notify about the Compiler
if (MSVC)
    message(STATUS "Compiler: MSVC")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS "Compiler: Clang++")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Compiler: G++")
endif()

# Notify if the Project's Production Status
message(STATUS "Production Status: ${ON_PRODUCTION}")

if (ON_PRODUCTION)
    # Notify all modifications status
    message(STATUS "Warning Status: OFF")
    message(STATUS "Terminal Visibility Status (WINDOWS ONLY): OFF")
    message(STATUS "Runtime Library Linked Statically (MSVC ONLY): ON")

    # Disable warnings
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)

    if (WIN32)
        # Remove console
        set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
    endif()

    if (MSVC)
        # Link the Runtime Library statically
        set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDebug<$<CONFIG:Debug>:Debug>")
        set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
    endif()

    # Set the resource path to be relative with the current CMakeLists.txt
    message(STATUS "${CMAKE_PROJECT_NAME} is in production. The RESOURCE_PATH macro is set to ./resources/")
    target_compile_definitions(
        ${CMAKE_PROJECT_NAME}
        PRIVATE ON_PRODUCTION
        PRIVATE RESOURCE_PATH="./resources/"
    )
elseif (NOT ON_PRODUCTION)
    # Notify all modification status
    message(STATUS "Warning Status: ON")
    message(STATUS "Terminal Visibility Status (WINDOWS ONLY): ON")
    message(STATUS "Runtime Library Linked Statically (MSVC ONLY): OFF")

    # Set the resource path to be relative to the executable
    message(STATUS "${CMAKE_PROJECT_NAME} is not in production. The RESOURCE_PATH macro is set to ${CMAKE_CURRENT_SOURCE_DIR}/resources/")
    target_compile_definitions(
        ${CMAKE_PROJECT_NAME}
        PRIVATE RESOURCE_PATH="${PROJECT_DIRECTORY}/resources/"
    )
endif()
