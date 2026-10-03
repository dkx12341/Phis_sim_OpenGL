#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>


class Circle
{
public:
    Circle(
        float mass,
        float radius,
        float restitution
    );

    Circle(
        float mass,
        float radius
    );

    void applyForce(const glm::vec2& force);

    void update(float deltaTime);

    float getRadius() const;
    float getMass() const;
    float getRestitution() const;

    const glm::vec2& getPosition() const;
    const glm::vec2& getVelocity() const;

    const glm::vec3& getColor() const;

    void setPosition(const glm::vec2& position);
    void setVelocity(const glm::vec2& velocity);

private:
    float mass;
    float radius;
    float restitution;

    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 acceleration;

    glm::vec3 color;
};