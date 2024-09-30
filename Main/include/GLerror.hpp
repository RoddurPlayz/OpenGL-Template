#pragma once


#include <iostream>

#include <glad/glad.h>


void debugMessageCallback(
    GLenum source, GLenum type, GLuint id,
    GLenum severity, GLsizei length,
    const GLchar* message, const void* user_param
);


void GLInitError();
