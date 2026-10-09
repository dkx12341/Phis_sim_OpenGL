#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class Ship
{
public:
    Ship(
        float mass,
        float size,
        float collisionRadius,
        float restitution = 0.5f
    );

    void applyForce(const glm::vec2& force);
    void update(float deltaTime);
    void rotate(float angle);

    float getMass() const;
    float getSize() const;
    float getCollisionRadius() const;
    float getRestitution() const;
    float getRotation() const;

    const glm::vec2& getPosition() const;
    const glm::vec2& getVelocity() const;
    const glm::vec3& getColor() const;

    void setPosition(const glm::vec2& position);
    void setVelocity(const glm::vec2& velocity);
    void setRotation(float rotation);
    void setColor(const glm::vec3& color);

private:
    float mass;
    float size;
    float collisionRadius;
    float restitution;
    float rotation;

    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 acceleration;

    glm::vec3 color;
};