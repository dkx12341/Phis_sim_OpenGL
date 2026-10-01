#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>

#include "renderer/shader.hpp"
#include "renderer/particle_renderer.hpp"
#include "objects/particle/particle.hpp"


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
        720,
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


    // =========================================================
    // SHADER
    // =========================================================

    Shader shader(
        "shaders/basic.vert",
        "shaders/basic.frag"
    );


    // =========================================================
    // OBIEKTY
    // =========================================================

    Particle particle(
        0.1f,
        0.05f,
        glm::vec3(1.0f, 1.0f, 1.0f)
    );


    // =========================================================
    // RENDERER
    // =========================================================

    ParticleRenderer renderer;


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


        // Fizyka
        particle.update(0.016f);


        // Renderowanie
        renderer.draw(
            particle,
            shader
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