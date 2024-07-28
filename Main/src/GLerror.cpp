#include "GLerror.h"


void debugMessageCallback(
    GLenum source, GLenum type, GLuint id,
    GLenum severity, GLsizei length,
    const GLchar* message, const void* userParam
) {

    std::cerr << "GL Debug Message [" << id << "]: " << message << std::endl;
    std::cerr << "Source: ";
    switch (source) {
        case GL_DEBUG_SOURCE_API:             std::cerr << "API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cerr << "Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cerr << "Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cerr << "Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     std::cerr << "Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           std::cerr << "Other"; break;
    }
    std::cerr << std::endl;

    std::cerr << "Type: ";
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:               std::cerr << "Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cerr << "Deprecated Behavior"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cerr << "Undefined Behavior"; break;
        case GL_DEBUG_TYPE_PORTABILITY:         std::cerr << "Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         std::cerr << "Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              std::cerr << "Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          std::cerr << "Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           std::cerr << "Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               std::cerr << "Other"; break;
    }
    std::cerr << std::endl;

    std::cerr << "Severity: ";
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:         std::cerr << "High"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       std::cerr << "Medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          std::cerr << "Low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cerr << "Notification"; break;
    }
    std::cerr << std::endl;

    exit(-1);
}

void GLInitError()
{
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debugMessageCallback, nullptr);
}