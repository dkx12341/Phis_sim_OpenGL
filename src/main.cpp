#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "camera/camera.hpp"

#include "renderer/shader.hpp"
#include "renderer/circle_renderer.hpp"

#include "simulation/simulation.hpp"


GLFWwindow* initializeWindow();

bool initializeOpenGL();


void processInput(
    GLFWwindow* window,
    Camera& camera,
    float deltaTime
);


void handleCameraMovement(
    GLFWwindow* window,
    Camera& camera,
    float deltaTime
);


void render(
    CircleRenderer& renderer,
    const Simulation& simulation,
    Shader& shader,
    Camera& camera
);


void cleanup(
    GLFWwindow* window
);


int main()
{
    GLFWwindow* window =
        initializeWindow();

    if (!window)
    {
        return -1;
    }


    if (!initializeOpenGL())
    {
        cleanup(window);

        return -1;
    }


    Shader shader(
        "shaders/basic.vert",
        "shaders/basic.frag"
    );


    Camera camera(
        glm::vec2(0.0f, 0.0f),
        120.0f,
        120.0f
    );


    Simulation simulation;  //Bajo jajo


    CircleRenderer renderer;


    double lastTime =
        glfwGetTime();


    while (!glfwWindowShouldClose(window))
    {
        const double currentTime =
            glfwGetTime();


        const float deltaTime =
            static_cast<float>(
                currentTime - lastTime
            );


        lastTime =
            currentTime;


        glfwPollEvents();


        processInput(
            window,
            camera,
            deltaTime
        );


        simulation.update(
            deltaTime
        );


        render(
            renderer,
            simulation,
            shader,
            camera
        );


        glfwSwapBuffers(window);
    }


    cleanup(window);

    return 0;
}


GLFWwindow* initializeWindow()
{
    if (!glfwInit())
    {
        std::cerr
            << "Failed to initialize GLFW\n";

        return nullptr;
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
        std::cerr
            << "Failed to create GLFW window\n";

        glfwTerminate();

        return nullptr;
    }


    glfwMakeContextCurrent(window);


    return window;
}


bool initializeOpenGL()
{
    if (!gladLoadGLLoader(
        reinterpret_cast<GLADloadproc>(
            glfwGetProcAddress
        )))
    {
        std::cerr
            << "Failed to initialize GLAD\n";

        return false;
    }


    std::cout
        << "OpenGL initialized!\n";


    std::cout
        << "Renderer: "
        << glGetString(GL_RENDERER)
        << '\n';


    return true;
}


void processInput(
    GLFWwindow* window,
    Camera& camera,
    float deltaTime
)
{
    handleCameraMovement(
        window,
        camera,
        deltaTime
    );
}


void handleCameraMovement(
    GLFWwindow* window,
    Camera& camera,
    float deltaTime
)
{
    const float cameraSpeed = 5.0f;
    const float zoomSpeed = 1.0f;


    if (
        glfwGetKey(
            window,
            GLFW_KEY_W
        ) == GLFW_PRESS
    )
    {
        camera.move(
            glm::vec2(
                0.0f,
                cameraSpeed * deltaTime
            )
        );
    }


    if (
        glfwGetKey(
            window,
            GLFW_KEY_S
        ) == GLFW_PRESS
    )
    {
        camera.move(
            glm::vec2(
                0.0f,
                -cameraSpeed * deltaTime
            )
        );
    }


    if (
        glfwGetKey(
            window,
            GLFW_KEY_A
        ) == GLFW_PRESS
    )
    {
        camera.move(
            glm::vec2(
                -cameraSpeed * deltaTime,
                0.0f
            )
        );
    }


    if (
        glfwGetKey(
            window,
            GLFW_KEY_D
        ) == GLFW_PRESS
    )
    {
        camera.move(
            glm::vec2(
                cameraSpeed * deltaTime,
                0.0f
            )
        );
    }


    if (
        glfwGetKey(
            window,
            GLFW_KEY_Q
        ) == GLFW_PRESS
    )
    {
        camera.zoom(
            zoomSpeed * deltaTime
        );
    }


    if (
        glfwGetKey(
            window,
            GLFW_KEY_E
        ) == GLFW_PRESS
    )
    {
        camera.zoom(
            -zoomSpeed * deltaTime
        );
    }
}


void render(
    CircleRenderer& renderer,
    const Simulation& simulation,
    Shader& shader,
    Camera& camera
)
{
    glClearColor(
        0.1f,
        0.1f,
        0.1f,
        1.0f
    );


    glClear(
        GL_COLOR_BUFFER_BIT
    );


    const glm::vec2& cameraPosition =
        camera.getPosition();


    const float cameraWidth =
        camera.getWidth();


    const float cameraHeight =
        camera.getHeight();


    const float cameraZoom =
        camera.getZoom();


    const glm::mat4 cameraMatrix =
        glm::ortho(
            cameraPosition.x -
                cameraWidth /
                (2.0f * cameraZoom),

            cameraPosition.x +
                cameraWidth /
                (2.0f * cameraZoom),

            cameraPosition.y -
                cameraHeight /
                (2.0f * cameraZoom),

            cameraPosition.y +
                cameraHeight /
                (2.0f * cameraZoom),

            -1.0f,
            1.0f
        );


    for (
        const auto& circle :
        simulation.getCircles()
    )
    {
        renderer.draw(
            *circle,
            shader,
            cameraMatrix
        );
    }
}


void cleanup(
    GLFWwindow* window
)
{
    glfwDestroyWindow(window);

    glfwTerminate();
}