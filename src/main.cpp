#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>

#include "renderer/shader.hpp"
#include "renderer/circle_renderer.hpp"
#include "objects/circle/circle.hpp"
#include "physics/world_physics.hpp"



int main()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(
        GLFW_CONTEXT_VERSION_MAJOR,
        3
    );

    glfwWindowHint(
        GLFW_CONTEXT_VERSION_MINOR,
        3
    );

    glfwWindowHint(
        GLFW_OPENGL_PROFILE,
        GLFW_OPENGL_CORE_PROFILE
    );


    GLFWwindow* window =
        glfwCreateWindow(
            720,
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
        reinterpret_cast<GLADloadproc>(
            glfwGetProcAddress
        )))
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
    // PARTICLE
    // =========================================================

    Circle circle(
        0.02f,
        0.02f,
        1.0f,
        glm::vec3(
            1.0f,
            0.5f,
            0.0f
        )
    );


    // =========================================================
    // PHYSICS
    // =========================================================

    WorldPhysics physicsWorld(
        glm::vec2(0.0f, -0.3f),
        glm::vec2(-0.95f, -0.95f),
        glm::vec2(1.0f, 1.0f)
    );

    physicsWorld.addCircle(circle);


    // =========================================================
    // RENDERER
    // =========================================================

    CircleRenderer renderer;


    // =========================================================
    // MAIN LOOP
    // =========================================================

    double lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        // Czas od poprzedniej klatki
        double currentTime = glfwGetTime();

        float deltaTime =
            static_cast<float>(currentTime - lastTime);

        lastTime = currentTime;


        glfwPollEvents();


        glClearColor(
            0.1f,
            0.1f,
            0.1f,
            1.0f
        );

        glClear(GL_COLOR_BUFFER_BIT);


        // Fizyka
        physicsWorld.update(deltaTime);


        // Renderowanie
        renderer.draw(
            circle,
            shader
        );


        glfwSwapBuffers(window);
    }

    // =========================================================
    // CLEANUP
    // =========================================================

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}