# Set the minimum version which is required to run this cmake project
cmake_minimum_required(VERSION 3.5)


# Create a project
project(OpenGL-Playground)

# Set C++ Standard Library to 17 and made C++ Standard Library to be required dependency
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create an executable
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

# Link all libraries
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    enet glad libglew_static glm imgui miniaudio stb_image stb_truetype
)

# Add a macro for this project (This is required for GLEW to be linked statically)
target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE GLEW_STATIC
)

#Choose if this project should be built for production
option(IS_PRODUCTION "The project is in production or not" OFF)
if(IS_PRODUCTION)
    # Link with the Runtime Library statically
    if(MSVC)
    foreach(config DEBUG RELEASE MINSIZEREL RELWITHDEBINFO)
        string(TOUPPER ${config} config_upper)
        set(CMAKE_CXX_FLAGS_${config_upper} "${CMAKE_CXX_FLAGS_${config_upper}} /MT")
    endforeach()
    endif()

    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        find_library(STDCXX_LIBRARY stdc++)
        find_library(GCC_LIBRARY gcc)
        get_filename_component(STDCXX_LIBRARY_PATH ${STDCXX_LIBRARY} DIRECTORY)
        get_filename_component(GCC_LIBRARY_PATH ${GCC_LIBRARY} DIRECTORY)

        set(
            runtime_libraries
            ${STDCXX_LIBRARY_PATH}/libstdc++.so.6
            ${GCC_LIBRARY_PATH}/libgcc_s.so.1
        )
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        find_library(CLANG_CXX_LIBRARY c++)
        find_library(CLANG_GCC_LIBRARY gcc_s)
        get_filename_component(CLANG_CXX_LIBRARY_PATH ${CLANG_CXX_LIBRARY} DIRECTORY)
        get_filename_component(CLANG_GCC_LIBRARY_PATH ${CLANG_GCC_LIBRARY} DIRECTORY)

        set(
            runtime_libraries
            ${CLANG_CXX_LIBRARY_PATH}/libc++.so.1
            ${CLANG_GCC_LIBRARY_PATH}/libgcc_s.so.1
        )
    endif()

    # Notifiy about the operating system and terminal status
    if(WIN32)
        message(STATUS "Operating System: Windows")
        message(STATUS "Terminal Status: Hidden")
        set_target_properties(
            ${PROJECT_NAME} PROPERTIES
            WIN32_EXECUTABLE YES
        )
    elseif(APPLE)
        message(STATUS "Operating System: MacOS")
        message(STATUS "Terminal Status: Hidden")
        set_target_properties(
            ${PROJECT_NAME} PROPERTIES
            MACOSX_BUNDLE YES
        )
    elseif(UNIX)
        message(STATUS "Operating System: Linux")
        message(STATUS "Terminal Status: Doesn't Matter")
    endif()

    # Set the resource path to be relative with the current CMakeLists.txt
    message(STATUS "${PROJECT_NAME} is in production. The RESOURCE_PATH macro is set to ./resources/")
    target_compile_definitions(
        ${PROJECT_NAME}
        PRIVATE ON_PRODUCTION
        PRIVATE RESOURCE_PATH="./resources/"
    )
else()

    # Notify about the operating system and terminal status
    if(WIN32)
        message(STATUS "Operating System: Windows")
        message(STATUS "Terminal Status: Not Hidden")
        set_target_properties(
            ${PROJECT_NAME} PROPERTIES
            WIN32_EXECUTABLE YES
        )
    elseif(APPLE)
        message(STATUS "Operating System: MacOS")
        message(STATUS "Terminal Status: Not Hidden")
        set_target_properties(
            ${PROJECT_NAME} PROPERTIES
            MACOSX_BUNDLE YES
        )
    elseif(UNIX)
        message(STATUS "Operating System: Linux")
        message(STATUS "Terminal Status: Doesn't Matter")
    endif()

    # Set the resource path to be relative to the executable
    message(STATUS "${PROJECT_NAME} is not in production. The RESOURCE_PATH macro is set to ${CMAKE_CURRENT_SOURCE_DIR}/resources/")
    target_compile_definitions(
        ${PROJECT_NAME}
        PRIVATE RESOURCE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/"
    )
endif()
