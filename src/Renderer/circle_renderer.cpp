#include "circle_renderer.hpp"

#include <cmath>
#include <vector>

#include <glad/glad.h>


CircleRenderer::CircleRenderer()
    : VAO(0),
      VBO(0),
      vertexCount(0)
{
    createCircle();
}


CircleRenderer::~CircleRenderer()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}


void CircleRenderer::createCircle()
{
    constexpr int segments = 8;

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

        const float x = std::cos(angle);
        const float y = std::sin(angle);

        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(0.0f);
    }

    vertexCount =
        static_cast<int>(vertices.size() / 3);


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

    glBindVertexArray(0);
}


void CircleRenderer::draw(
    const Circle& circle,
    const Shader& shader
) const
{
    shader.use();

    const glm::vec2& position =
        circle.getPosition();

    const glm::vec3& color =
        circle.getColor();

    const float radius =
        circle.getRadius();

    shader.setVec2(
        "uPosition",
        position
    );

    shader.setFloat(
        "uRadius",
        radius
    );

    shader.setVec3(
        "uColor",
        color
    );

    glBindVertexArray(VAO);

    glDrawArrays(
        GL_TRIANGLE_FAN,
        0,
        vertexCount
    );
}