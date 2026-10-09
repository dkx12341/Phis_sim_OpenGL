#include "circle.hpp"

Circle::Circle(
    float mass,
    float radius,
    float restitution
)
    : mass(mass),
      radius(radius),
      restitution(restitution),
      rotation(0.0f),
      position(0.0f, 0.0f),
      velocity(0.0f, 0.0f),
      acceleration(0.0f, 0.0f),
      color(1.0f, 1.0f, 1.0f)
{
}

Circle::Circle(
    float mass,
    float radius
)
    : Circle(mass, radius, 0.9f)
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

float Circle::getRotation() const
{
    return rotation;
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

float Circle::getCollisionRadius() const
{
    return radius;
}

void Circle::setPosition(const glm::vec2& position)
{
    this->position = position;
}

void Circle::setVelocity(const glm::vec2& velocity)
{
    this->velocity = velocity;
}

void Circle::setRotation(float rotation)
{
    this->rotation = rotation;
}