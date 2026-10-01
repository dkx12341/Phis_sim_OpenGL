#pragma once

#include "shader.hpp"
#include "../objects/circle/circle.hpp"


class CircleRenderer
{
public:
    CircleRenderer();

    ~CircleRenderer();

    void draw(
        const Circle& circle,
        const Shader& shader
    ) const;

private:

    unsigned int VAO;
    unsigned int VBO;

    int vertexCount;

    void createCircle();
};