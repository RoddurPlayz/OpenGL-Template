#include <iostream>
#include <sstream>

//#include <assimp/mesh.h>

//#include <enet/enet.h>

#include <glad/glad.h>
//#include <GL/glew.h> // GLEW MUST BE INCLUDED ALWAYS AND IN EVERY FILE BEFORE GLFW IF YOU WANT TO USE IT !!!
#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//#include <glm/gtx/vector_angle.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <imgui.h>

//#include <miniaudio.h>
//#include <nlohmann/json.hpp>
//#include <AL/al.h>

//#include <stb_image/stb_image.h>
//#include <stb_truetype/stb_truetype.h>

#include "GLerror.hpp"
#include "GLFWfunctions.hpp"
#include "shader.hpp"


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
    if (!gladLoadGL())
    {
        std::cout << "Glad failed to initialize!" << "\n";
        return -1;
    }
    initGlfwFuncs(window);
    GLInitError();

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

    ShaderProgram shader{ RESOURCE_PATH "shaders/test/vert.glsl", RESOURCE_PATH "shaders/test/frag.glsl" };
    shader.bind();

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    shader.destroy();
    glfwTerminate();

    return 0;
}
