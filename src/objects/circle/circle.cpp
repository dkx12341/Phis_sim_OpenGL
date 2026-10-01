#include "circle.hpp"

#include <cmath>

Circle::Circle(
    float mass,
    float radius,
    float restitution,
    const glm::vec3& color
)
    : mass(mass),
      radius(radius),
      restitution(restitution),
      position(0.0f, 0.0f),
      velocity(0.0f, 0.0f),
      acceleration(0.0f, 0.0f),
      color(color)
{
}

Circle::Circle(
    float mass,
    float radius,
    const glm::vec3& color
)
    : Circle(mass, radius, 0.9f, color)
{
}

void Circle::applyForce(const glm::vec2& force)
{
    acceleration += force / mass;
}

void Circle::update(float deltaTime)
{
    velocity += acceleration * deltaTime;

    position += velocity * deltaTime;

    acceleration = glm::vec2(0.0f, 0.0f);
}


float Circle::getRadius() const
{
    return radius;
}

float Circle::getMass() const
{
    return mass;
}

float Circle::getRestitution() const
{
    return restitution;
}

const glm::vec2& Circle::getPosition() const
{
    return position;
}

const glm::vec2& Circle::getVelocity() const
{
    return velocity;
}

const glm::vec3& Circle::getColor() const
{
    return color;
}

void Circle::setPosition(
    const glm::vec2& position
)
{
    this->position = position;
}


void Circle::setVelocity(
    const glm::vec2& velocity
)
{
    this->velocity = velocity;
}