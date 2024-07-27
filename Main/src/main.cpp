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
    {
        std::cout << "GLFW failed to initialize!" << "\n";
        return -1;
    }

    window = glfwCreateWindow(640, 480, "OpenGL", NULL, NULL);
    if (!window)
    {
        std::cout << "GLFW failed to create a window!" << "\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Glew failed to initialize!" << "\n";
        return -1;
    }

    std::stringstream title;
    title << "OpenGL: " << glGetString(GL_VERSION) << "\n";
    glfwSetWindowTitle(window, title.str().c_str());

    float vertices[8] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // NOTE: 'size' could be sizeof the buffer like this, sizeof(buffer)
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    unsigned int indices[6] = {
        0, 1, 2,
        2, 3, 0
    };
    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    ShaderProgram shader{ RESOURCE_PATH "vert.glsl", RESOURCE_PATH "frag.glsl" };
    shader.bind();

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
