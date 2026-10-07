#include "world_physics.hpp"

#include <glm/vec2.hpp>


WorldPhysics::WorldPhysics(
    const glm::vec2& gravity,
    const glm::vec2& minBounds,
    const glm::vec2& maxBounds
)
    : gravity(gravity),
      minBounds(minBounds),
      maxBounds(maxBounds),
      spatialTree(
          minBounds,
          maxBounds
      )
{
}


void WorldPhysics::addCircle(
    Circle& circle
)
{
    circles.push_back(&circle);
}

glm::vec2 WorldPhysics::getMaxBounds() const{
    return maxBounds;
}


void WorldPhysics::update(
    float deltaTime
)
{
    for (Circle* circle : circles)
    {
        applyGravity(*circle);

        circle->update(deltaTime);

        handleBounds(*circle);
    }

    spatialTree.clear();

    for (Circle* circle : circles)
    {
        spatialTree.insert(*circle);
    }
}


void WorldPhysics::applyGravity(
    Circle& circle
)
{
    circle.applyForce(
        gravity * circle.getMass()
    );
}


void WorldPhysics::handleBounds(
    Circle& circle
)
{
    glm::vec2 position =
        circle.getPosition();

    glm::vec2 velocity =
        circle.getVelocity();

    const float radius =
        circle.getRadius();


    // Lewa ściana
    if (position.x - radius < minBounds.x)
    {
        position.x =
            minBounds.x + radius;

        velocity.x =
            -velocity.x;
        velocity = velocity * circle.getRestitution();
    }


    // Prawa ściana
    else if (position.x + radius > maxBounds.x)
    {
        position.x =
            maxBounds.x - radius;

        velocity.x =
            -velocity.x;
        velocity = velocity * circle.getRestitution();
    }


    // Dolna ściana
    if (position.y - radius < minBounds.y)
    {
        position.y =
            minBounds.y + radius;

        velocity.y =
            -velocity.y;
        velocity = velocity * circle.getRestitution();
    }


    // Górna ściana
    else if (position.y + radius > maxBounds.y)
    {
        position.y =
            maxBounds.y - radius;

        velocity.y =
            -velocity.y;
        velocity = velocity * circle.getRestitution();
    }

    circle.setPosition(position);
    circle.setVelocity(velocity);
}