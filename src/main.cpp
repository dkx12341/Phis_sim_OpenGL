#include <iostream>
#include <cmath>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer/Shader.hpp"


int main()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(
        1080,
        1080,
        "Physics Simulation",
        nullptr,
        nullptr
    );

    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";

        glfwTerminate();

        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(
        reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cerr << "Failed to initialize GLAD\n";

        glfwDestroyWindow(window);
        glfwTerminate();

        return -1;
    }

    std::cout << "OpenGL initialized!\n";

    std::cout << "Renderer: "
              << glGetString(GL_RENDERER)
              << '\n';

    Shader shader(
        "shaders/basic.vert",
        "shaders/basic.frag"
    );

    const int segments = 32;
    const float radius = 0.5f;

    std::vector<float> vertices;

    // Środek koła
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);

    // Punkty na obwodzie
    for (int i = 0; i <= segments; ++i)
    {
        const float angle =
            2.0f * 3.14159265359f * i / segments;

        const float x =
            radius * std::cos(angle);

        const float y =
            radius * std::sin(angle);

        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(0.0f);
    }


    // =========================================================
    // VAO + VBO
    // =========================================================

    unsigned int VBO;
    unsigned int VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(float),
        vertices.data(),
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);


    // =========================================================
    // GŁÓWNA PĘTLA
    // =========================================================

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(
            0.1f,
            0.1f,
            0.1f,
            1.0f
        );

        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        glBindVertexArray(VAO);

        glDrawArrays(
            GL_TRIANGLE_FAN,
            0,
            static_cast<GLsizei>(vertices.size() / 3)
        );

        glfwSwapBuffers(window);
    }


    // =========================================================
    // SPRZĄTANIE
    // =========================================================

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}