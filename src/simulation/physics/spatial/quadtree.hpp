#pragma once

#include <vector>

#include <glm/vec2.hpp>

#include "../../objects/circle/circle.hpp"


class QuadTree
{
public:

    QuadTree(
        const glm::vec2& minBounds,
        const glm::vec2& maxBounds,
        int maxObjectsPerNode = 8,
        int maxDepth = 8
    );

    ~QuadTree();


    void clear();

    void insert(Circle& circle);

    std::vector<Circle*> query(
        const Circle& circle
    ) const;


private:

    struct Node
    {
        glm::vec2 minBounds;
        glm::vec2 maxBounds;

        std::vector<Circle*> circles;

        Node* children[4];

        int depth;


        Node(
            const glm::vec2& minBounds,
            const glm::vec2& maxBounds,
            int depth
        );

        ~Node();


        bool isLeaf() const;
    };


    Node* root;

    glm::vec2 minBounds;
    glm::vec2 maxBounds;

    int maxObjectsPerNode;
    int maxDepth;

    float maxCircleRadius;


    void insert(
        Node* node,
        Circle& circle
    );

    void subdivide(Node* node);


    void query(
        const Node* node,
        const glm::vec2& queryMin,
        const glm::vec2& queryMax,
        std::vector<Circle*>& result
    ) const;


    bool contains(
        const Node* node,
        const Circle& circle
    ) const;


    bool overlaps(
        const Node* node,
        const glm::vec2& queryMin,
        const glm::vec2& queryMax
    ) const;
};