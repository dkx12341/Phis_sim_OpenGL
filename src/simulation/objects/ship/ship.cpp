#include "ship.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

Ship::Ship(
    float mass,
    float size,
    float collisionRadius,
    float restitution
)
    : mass(mass),
      size(size),
      collisionRadius(collisionRadius),
      restitution(restitution),
      rotation(0.0f),
      position(0.0f, 0.0f),
      velocity(0.0f, 0.0f),
      acceleration(0.0f, 0.0f),
      color(0.2f, 0.8f, 1.0f)
{
    if (
        !std::isfinite(mass) ||
        mass <= 0.0f ||
        !std::isfinite(size) ||
        size <= 0.0f ||
        !std::isfinite(collisionRadius) ||
        collisionRadius <= 0.0f ||
        !std::isfinite(restitution)
    )
    {
        throw std::invalid_argument(
            "Invalid Ship physical parameters"
        );
    }

    this->restitution =
        std::clamp(restitution, 0.0f, 1.0f);
}

void Ship::applyForce(const glm::vec2& force)
{
    acceleration += force / mass;
}

void Ship::update(float deltaTime)
{
    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;

    acceleration = glm::vec2(0.0f);
}

void Ship::rotate(float angle)
{
    constexpr float twoPi = 6.28318530718f;

    rotation = std::fmod(rotation + angle, twoPi);
}

float Ship::getMass() const
{
    return mass;
}

float Ship::getSize() const
{
    return size;
}

float Ship::getCollisionRadius() const
{
    return collisionRadius;
}

float Ship::getRestitution() const
{
    return restitution;
}

float Ship::getRotation() const
{
    return rotation;
}

const glm::vec2& Ship::getPosition() const
{
    return position;
}

const glm::vec2& Ship::getVelocity() const
{
    return velocity;
}

const glm::vec3& Ship::getColor() const
{
    return color;
}

void Ship::setPosition(const glm::vec2& position)
{
    this->position = position;
}

void Ship::setVelocity(const glm::vec2& velocity)
{
    this->velocity = velocity;
}

void Ship::setRotation(float rotation)
{
    constexpr float twoPi = 6.28318530718f;

    this->rotation = std::fmod(rotation, twoPi);
}

void Ship::setColor(const glm::vec3& color)
{
    this->color = color;
}