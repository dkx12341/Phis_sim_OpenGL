#include "ship_renderer.hpp"

#include <glad/glad.h>

ShipRenderer::ShipRenderer()
    : VAO(0),
      VBO(0)
{
    createShip();
}

ShipRenderer::~ShipRenderer()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void ShipRenderer::createShip()
{
    // Dwa trójkąty tworzące sylwetkę statku.
    // Dziób wskazuje lokalnie w kierunku +Y.
    const float vertices[] =
    {
        // Lewy trójkąt
        -0.55f, -0.45f, 0.0f,
         0.00f,  0.65f, 0.0f,
         0.00f, -0.10f, 0.0f,

        // Prawy trójkąt
         0.00f, -0.10f, 0.0f,
         0.00f,  0.65f, 0.0f,
         0.55f, -0.45f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        nullptr
    );

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void ShipRenderer::draw(
    const Ship& ship,
    const Shader& shader,
    const glm::mat4& cameraMatrix
) const
{
    shader.use();

    shader.setVec2(
        "uPosition",
        ship.getPosition()
    );

    shader.setFloat(
        "uRadius",
        ship.getSize()
    );

    shader.setFloat(
        "uRotation",
        ship.getRotation()
    );

    shader.setVec3(
        "uColor",
        ship.getColor()
    );

    shader.setMat4(
        "uCamera",
        cameraMatrix
    );

    glBindVertexArray(VAO);

    glDrawArrays(
        GL_TRIANGLES,
        0,
        6
    );

    glBindVertexArray(0);
}