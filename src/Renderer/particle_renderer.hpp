#pragma once

#include "shader.hpp"
#include "../objects/particle/particle.hpp"


class ParticleRenderer
{
public:
    ParticleRenderer();

    ~ParticleRenderer();

    void draw(
        const Particle& particle,
        const Shader& shader
    ) const;

private:

    unsigned int VAO;
    unsigned int VBO;

    int vertexCount;

    void createCircle();
};