#pragma once

#include <glm/mat4x4.hpp>

#include "shader.hpp"
#include "../simulation/objects/circle/circle.hpp"

class CircleRenderer
{
public:
    CircleRenderer();
    ~CircleRenderer();

    CircleRenderer(const CircleRenderer&) = delete;
    CircleRenderer& operator=(const CircleRenderer&) = delete;

    void draw(
        const Circle& circle,
        const Shader& shader,
        const glm::mat4& cameraMatrix
    ) const;

private:
    unsigned int VAO;
    unsigned int VBO;

    int vertexCount;

    void createCircle();
};