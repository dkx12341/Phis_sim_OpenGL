#pragma once

#include <glm/mat4x4.hpp>

#include "shader.hpp"
#include "../simulation/objects/ship/ship.hpp"

class ShipRenderer
{
public:
    ShipRenderer();
    ~ShipRenderer();

    ShipRenderer(const ShipRenderer&) = delete;
    ShipRenderer& operator=(const ShipRenderer&) = delete;

    void draw(
        const Ship& ship,
        const Shader& shader,
        const glm::mat4& cameraMatrix
    ) const;

private:
    unsigned int VAO;
    unsigned int VBO;

    void createShip();
};