#include "world_physics.hpp"

WorldPhysics::WorldPhysics(
    const glm::vec2& gravity,
    const glm::vec2& minBounds,
    const glm::vec2& maxBounds
)
    : gravity(gravity),
      minBounds(minBounds),
      maxBounds(maxBounds),
      spatialTree(minBounds, maxBounds)
{
}

void WorldPhysics::addCircle(Circle& circle)
{
    circles.push_back(&circle);
}

glm::vec2 WorldPhysics::getMaxBounds() const
{
    return maxBounds;
}

void WorldPhysics::applyGravity(Circle& circle)
{
    circle.applyForce(gravity * circle.getMass());
}

void WorldPhysics::applyGravity(Ship& ship)
{
    ship.applyForce(gravity * ship.getMass());
}

void WorldPhysics::handleBounds(Circle& circle)
{
    glm::vec2 position = circle.getPosition();
    glm::vec2 velocity = circle.getVelocity();

    const float radius = circle.getRadius();

    if (position.x - radius < minBounds.x)
    {
        position.x = minBounds.x + radius;
        velocity.x = -velocity.x;
        velocity *= circle.getRestitution();
    }
    else if (position.x + radius > maxBounds.x)
    {
        position.x = maxBounds.x - radius;
        velocity.x = -velocity.x;
        velocity *= circle.getRestitution();
    }

    if (position.y - radius < minBounds.y)
    {
        position.y = minBounds.y + radius;
        velocity.y = -velocity.y;
        velocity *= circle.getRestitution();
    }
    else if (position.y + radius > maxBounds.y)
    {
        position.y = maxBounds.y - radius;
        velocity.y = -velocity.y;
        velocity *= circle.getRestitution();
    }

    circle.setPosition(position);
    circle.setVelocity(velocity);
}

void WorldPhysics::handleBounds(Ship& ship)
{
    glm::vec2 position = ship.getPosition();
    glm::vec2 velocity = ship.getVelocity();

    const float radius = ship.getCollisionRadius();

    if (position.x - radius < minBounds.x)
    {
        position.x = minBounds.x + radius;
        velocity.x = -velocity.x;
        velocity *= ship.getRestitution();
    }
    else if (position.x + radius > maxBounds.x)
    {
        position.x = maxBounds.x - radius;
        velocity.x = -velocity.x;
        velocity *= ship.getRestitution();
    }

    if (position.y - radius < minBounds.y)
    {
        position.y = minBounds.y + radius;
        velocity.y = -velocity.y;
        velocity *= ship.getRestitution();
    }
    else if (position.y + radius > maxBounds.y)
    {
        position.y = maxBounds.y - radius;
        velocity.y = -velocity.y;
        velocity *= ship.getRestitution();
    }

    ship.setPosition(position);
    ship.setVelocity(velocity);
}

void WorldPhysics::update(
    float deltaTime,
    Ship& ship
)
{
    // 1. Aktualizacja fizyki kół.
    for (Circle* circle : circles)
    {
        applyGravity(*circle);
        circle->update(deltaTime);
        handleBounds(*circle);
    }

    // 2. Aktualizacja fizyki statku.
    applyGravity(ship);
    ship.update(deltaTime);
    handleBounds(ship);

    // 3. Budowa drzewa na podstawie aktualnych pozycji kół.
    spatialTree.clear();

    for (Circle* circle : circles)
    {
        spatialTree.insert(*circle);
    }

    // 4. Rozwiązanie kolizji koło–koło i statek–koło.
    collisionSolver.solve(
        circles,
        spatialTree,
        ship
    );
}