#include <iostream>
#include <sstream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include <miniaudio.h>

#include <enet/enet.h>

#include "shader.h"


int main()
{
    GLFWwindow *window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "OpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Glew failed to initialize" << "\n";
        return -1;
    }

    std::stringstream title;
    title << "OpenGL: " << glGetString(GL_VERSION) << "\n";
    glfwSetWindowTitle(window, title.str().c_str());

    float triangle[6] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };
    unsigned int triangleBuffer;
    glGenBuffers(1, &triangleBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, triangleBuffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), triangle, GL_STATIC_DRAW); // NOTE: 'size' could be sizeof the buffer like this, sizeof(buffer)
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    ShaderProgram shader{ RESOURCE_PATH "vert.glsl", RESOURCE_PATH "frag.glsl" };
    shader.bind();

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
