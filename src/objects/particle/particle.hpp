#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>


class Particle
{
public:
    Particle(
        float mass,
        float radius,
        const glm::vec3& color
    );

    void update(float deltaTime);

    float getRadius() const;

    const glm::vec2& getPosition() const;

    const glm::vec3& getColor() const;

private:
    float mass;
    float radius;

    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 acceleration;

    glm::vec3 color;
};