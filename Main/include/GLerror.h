#pragma once


#include <iostream>

#include <GL/glew.h>


void debugMessageCallback(
    GLenum source, GLenum type, GLuint id,
    GLenum severity, GLsizei length,
    const GLchar* message, const void* userParam
);


void GLInitError();