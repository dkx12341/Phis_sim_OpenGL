#include "particle.hpp"

#include <cmath>


Particle::Particle(
    float mass,
    float radius,
    const glm::vec3& color
)
    : mass(mass),
      radius(radius),
      position(0.0f, 0.0f),
      velocity(0.0f, 0.0f),
      acceleration(0.0f, 0.0f),
      color(color)
{
}

void Particle::update(float deltaTime)
{
    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;
}

float Particle::getRadius() const
{
    return radius;
}

const glm::vec2& Particle::getPosition() const
{
    return position;
}

const glm::vec3& Particle::getColor() const
{
    return color;
}