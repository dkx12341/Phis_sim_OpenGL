#include "collision_solver.hpp"

#include <algorithm>
#include <cmath>
#include <functional>

#include <glm/geometric.hpp>


void CollisionSolver::solve(
    std::vector<Circle*>& circles,
    const QuadTree& spatialTree
)
{
    // Bufor kandydatów jest tworzony tylko raz.
    // Nie alokujemy nowego vectora dla każdego koła.
    std::vector<Circle*> candidates;
    candidates.reserve(64);


    for (Circle* circle : circles)
    {
        candidates.clear();

        spatialTree.query(
            *circle,
            candidates
        );


        for (Circle* candidate : candidates)
        {
            // Nie kolidujemy obiektu z samym sobą.
            if (candidate == circle)
            {
                continue;
            }


            // Każdą parę rozwiązujemy tylko raz.
            //
            // Jeśli mamy:
            //
            // A -> B
            //
            // to później:
            //
            // B -> A
            //
            // zostanie pominięte.

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


    // Wektor od A do B.

    const glm::vec2 delta =
        positionB - positionA;


    const float radiusSum =
        radiusA + radiusB;


    const float distanceSquared =
        glm::dot(
            delta,
            delta
        );


    // Brak kolizji.

    if (
        distanceSquared >=
        radiusSum * radiusSum
    )
    {
        return;
    }


    // Środki są praktycznie w tym samym miejscu.
    //
    // Nie możemy wtedy bezpiecznie znormalizować delta.
    //
    // Docelowo można tutaj obsłużyć ten przypadek
    // losową/stabilną normalną.

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


    // ---------------------------------
    // Inverse mass
    // ---------------------------------

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


    // Obiekty już się od siebie oddalają.
    //
    // Korekcja pozycji została wykonana wyżej,
    // ale nie dokładamy kolejnego impulsu.

    if (velocityAlongNormal > 0.0f)
    {
        return;
    }


    // ---------------------------------
    // Restitution
    // ---------------------------------

    const float restitution =
        std::min(
            a.getRestitution(),
            b.getRestitution()
        );


    // ---------------------------------
    // Collision impulse
    // ---------------------------------

    const float impulseMagnitude =
        -(1.0f + restitution)
        * velocityAlongNormal
        / inverseMassSum;


    const glm::vec2 impulse =
        impulseMagnitude * normal;


    // A dostaje impuls w przeciwną stronę.

    a.setVelocity(
        a.getVelocity()
        - impulse * inverseMassA
    );


    // B dostaje impuls w stronę normalnej.

    b.setVelocity(
        b.getVelocity()
        + impulse * inverseMassB
    );
}