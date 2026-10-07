#include "collision_solver.hpp"

#include <algorithm>
#include <cmath>

#include <glm/geometric.hpp>


void CollisionSolver::solve(
    std::vector<Circle*>& circles,
    const QuadTree& spatialTree
)
{
    for (Circle* circle : circles)
    {
        std::vector<Circle*> candidates =
            spatialTree.query(*circle);


        for (Circle* candidate : candidates)
        {
            if (candidate == circle)
            {
                continue;
            }


            resolveCollision(
                *circle,
                *candidate
            );
        }
    }
}


void CollisionSolver::resolveCollision(
    Circle& a,
    Circle& b
)
{
    const glm::vec2 positionA =
        a.getPosition();

    const glm::vec2 positionB =
        b.getPosition();


    const float radiusA =
        a.getRadius();

    const float radiusB =
        b.getRadius();


    const glm::vec2 delta =
        positionB - positionA;


    const float radiusSum =
        radiusA + radiusB;


    const float distanceSquared =
        glm::dot(
            delta,
            delta
        );


    if (
        distanceSquared >=
        radiusSum * radiusSum
    )
    {
        return;
    }


    if (distanceSquared <= 0.000001f)
    {
        return;
    }


    const float distance =
        std::sqrt(distanceSquared);


    const glm::vec2 normal =
        delta / distance;


    const float penetration =
        radiusSum - distance;


    const float inverseMassA =
        1.0f / a.getMass();

    const float inverseMassB =
        1.0f / b.getMass();


    const float inverseMassSum =
        inverseMassA + inverseMassB;


    // ---------------------------------
    // Position correction
    // ---------------------------------

    const glm::vec2 correction =
        normal *
        (penetration / inverseMassSum);


    a.setPosition(
        a.getPosition()
        - correction * inverseMassA
    );


    b.setPosition(
        b.getPosition()
        + correction * inverseMassB
    );


    // ---------------------------------
    // Relative velocity
    // ---------------------------------

    const glm::vec2 relativeVelocity =
        b.getVelocity()
        - a.getVelocity();


    const float velocityAlongNormal =
        glm::dot(
            relativeVelocity,
            normal
        );


    // Obiekty już się oddalają.

    if (velocityAlongNormal > 0.0f)
    {
        return;
    }


    // ---------------------------------
    // Impulse
    // ---------------------------------

    const float restitution =
        std::min(
            a.getRestitution(),
            b.getRestitution()
        );


    const float impulseMagnitude =
        -(1.0f + restitution)
        * velocityAlongNormal
        / inverseMassSum;


    const glm::vec2 impulse =
        impulseMagnitude * normal;


    a.setVelocity(
        a.getVelocity()
        - impulse * inverseMassA
    );


    b.setVelocity(
        b.getVelocity()
        + impulse * inverseMassB
    );
}