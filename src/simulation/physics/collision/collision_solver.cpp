#include "collision_solver.hpp"

#include <algorithm>
#include <cmath>
#include <functional>

#include <glm/geometric.hpp>

namespace
{
    template<typename BodyA, typename BodyB>
    void resolveBodies(
        BodyA& a,
        BodyB& b
    )
    {
        const glm::vec2 delta =
            b.getPosition() - a.getPosition();

        const float radiusSum =
            a.getCollisionRadius() + b.getCollisionRadius();

        const float distanceSquared =
            glm::dot(delta, delta);

        if (distanceSquared >= radiusSum * radiusSum)
        {
            return;
        }

        // Przypadek pokrywających się środków.
        // W tej sytuacji normalna nie jest określona.
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

        // Korekcja pozycji rozdzielająca ciała.
        const glm::vec2 correction =
            normal * (penetration / inverseMassSum);

        a.setPosition(
            a.getPosition()
            - correction * inverseMassA
        );

        b.setPosition(
            b.getPosition()
            + correction * inverseMassB
        );

        const glm::vec2 relativeVelocity =
            b.getVelocity() - a.getVelocity();

        const float velocityAlongNormal =
            glm::dot(relativeVelocity, normal);

        // Ciała już się od siebie oddalają.
        if (velocityAlongNormal > 0.0f)
        {
            return;
        }

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
}

void CollisionSolver::solve(
    std::vector<Circle*>& circles,
    const QuadTree& spatialTree,
    Ship& ship
)
{
    std::vector<Circle*> candidates;
    candidates.reserve(64);

    // 1. Kolizje koło–koło.
    for (Circle* circle : circles)
    {
        candidates.clear();

        spatialTree.query(
            *circle,
            candidates
        );

        for (Circle* candidate : candidates)
        {
            if (candidate == circle)
            {
                continue;
            }

            // Każdą parę rozwiązujemy tylko raz.
            if (
                !std::less<Circle*>{}(
                    circle,
                    candidate
                )
            )
            {
                continue;
            }

            resolveCollision(
                *circle,
                *candidate
            );
        }
    }

    // 2. Kolizje statek–koło.
    candidates.clear();

    spatialTree.query(
        ship.getPosition(),
        ship.getCollisionRadius(),
        candidates
    );

    for (Circle* circle : candidates)
    {
        resolveCollision(
            ship,
            *circle
        );
    }
}

void CollisionSolver::resolveCollision(
    Circle& a,
    Circle& b
)
{
    resolveBodies(a, b);
}

void CollisionSolver::resolveCollision(
    Ship& ship,
    Circle& circle
)
{
    resolveBodies(ship, circle);
}