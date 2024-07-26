cmake_minimum_required(VERSION 3.5)


project(OpenGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(
    ${CMAKE_PROJECT_NAME} PRIVATE
    enet glad libglew_static glm imgui miniaudio stb_image stb_truetype
)

target_compile_definitions(
    ${CMAKE_PROJECT_NAME}
    PRIVATE GLEW_STATIC
)

option(IS_PRODUCTION "The project is in production or not" OFF)
if(IS_PRODUCTION)
    message(STATUS "${CMAKE_PROJECT_NAME} is in production. The RESOURCE_PATH macro is set to ./resources/")
    target_compile_definitions(
        ${CMAKE_PROJECT_NAME}
        PRIVATE ON_PRODUCTION
        PRIVATE RESOURCE_PATH="./resources/"
    )

    if(MSVC)
    foreach(config DEBUG RELEASE MINSIZEREL RELWITHDEBINFO)
        string(TOUPPER ${config} config_upper)
        set(CMAKE_CXX_FLAGS_${config_upper} "${CMAKE_CXX_FLAGS_${config_upper}} /MT")
    endforeach()
    endif()

    # Determine the runtime library directories based on the compiler
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        # Logic for GCC
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
        # Logic for Clang
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

    if(WIN32)
    set_target_properties(
        ${CMAKE_PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE YES
    )
    elseif(APPLE)
        set_target_properties(
            ${CMAKE_PROJECT_NAME} PROPERTIES
            MACOSX_BUNDLE YES
        )
    elseif(UNIX)
        set_target_properties(
            ${CMAKE_PROJECT_NAME} PROPERTIES
            LINK_FLAGS "-mwindows"
        )
    endif()
else()
    message(STATUS "${CMAKE_PROJECT_NAME} is not in production. The RESOURCE_PATH macro is set to ${CMAKE_CURRENT_SOURCE_DIR}/resources/")
    target_compile_definitions(
        ${CMAKE_PROJECT_NAME}
        PRIVATE RESOURCE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/"
    )
endif()
