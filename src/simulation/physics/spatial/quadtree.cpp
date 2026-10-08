#include "quadtree.hpp"

#include <algorithm>
#include <utility>


QuadTree::QuadTree(
    const glm::vec2& minBounds,
    const glm::vec2& maxBounds,
    int maxObjectsPerNode,
    int maxDepth
)
    : root(
        new Node(
            minBounds,
            maxBounds,
            0
        )
    ),
      minBounds(minBounds),
      maxBounds(maxBounds),
      maxObjectsPerNode(maxObjectsPerNode),
      maxDepth(maxDepth),
      maxCircleRadius(0.0f)
{
}


QuadTree::~QuadTree()
{
    delete root;
}


QuadTree::Node::Node(
    const glm::vec2& minBounds,
    const glm::vec2& maxBounds,
    int depth
)
    : minBounds(minBounds),
      maxBounds(maxBounds),
      depth(depth)
{
    children[0] = nullptr;
    children[1] = nullptr;
    children[2] = nullptr;
    children[3] = nullptr;
}


QuadTree::Node::~Node()
{
    delete children[0];
    delete children[1];
    delete children[2];
    delete children[3];
}


bool QuadTree::Node::isLeaf() const
{
    return children[0] == nullptr;
}


void QuadTree::clear()
{
    delete root;

    root = new Node(
        minBounds,
        maxBounds,
        0
    );

    maxCircleRadius = 0.0f;
}


void QuadTree::insert(
    Circle& circle
)
{
    maxCircleRadius =
        std::max(
            maxCircleRadius,
            circle.getRadius()
        );

    insert(
        root,
        circle
    );
}


void QuadTree::insert(
    Node* node,
    Circle& circle
)
{
    if (!contains(node, circle))
    {
        return;
    }


    // Jeżeli jesteśmy w liściu i mamy miejsce,
    // dodajemy obiekt bez dzielenia noda.

    if (
        node->isLeaf() &&
        (
            node->circles.size()
            < static_cast<size_t>(maxObjectsPerNode)
            ||
            node->depth >= maxDepth
        )
    )
    {
        node->circles.push_back(&circle);

        return;
    }


    // Node jest liściem, ale jest pełny.
    // Dzielimy go na cztery części.

    if (node->isLeaf())
    {
        subdivide(node);


        // Przenosimy istniejące obiekty
        // do odpowiednich dzieci.

        std::vector<Circle*> oldCircles =
            std::move(node->circles);

        node->circles.clear();


        for (Circle* oldCircle : oldCircles)
        {
            bool inserted = false;


            for (int i = 0; i < 4; ++i)
            {
                if (
                    contains(
                        node->children[i],
                        *oldCircle
                    )
                )
                {
                    insert(
                        node->children[i],
                        *oldCircle
                    );

                    inserted = true;

                    break;
                }
            }


            // Jeżeli koło nie mieści się całkowicie
            // w żadnym dziecku, zostaje w obecnym node.

            if (!inserted)
            {
                node->circles.push_back(
                    oldCircle
                );
            }
        }
    }


    // Próbujemy umieścić nowy obiekt
    // w jednym z czterech dzieci.

    for (int i = 0; i < 4; ++i)
    {
        if (
            contains(
                node->children[i],
                circle
            )
        )
        {
            insert(
                node->children[i],
                circle
            );

            return;
        }
    }


    // Koło przecina granice kilku dzieci,
    // więc zostaje w obecnym node.

    node->circles.push_back(
        &circle
    );
}


bool QuadTree::contains(
    const Node* node,
    const Circle& circle
) const
{
    const glm::vec2 position =
        circle.getPosition();

    const float radius =
        circle.getRadius();


    return
        position.x - radius >= node->minBounds.x &&
        position.x + radius <= node->maxBounds.x &&
        position.y - radius >= node->minBounds.y &&
        position.y + radius <= node->maxBounds.y;
}


void QuadTree::subdivide(Node* node)
{
    const glm::vec2 center =
        (node->minBounds + node->maxBounds)
        * 0.5f;


    // ---------------------------------
    // Dolny-lewy
    // ---------------------------------

    node->children[0] =
        new Node(
            glm::vec2(
                node->minBounds.x,
                node->minBounds.y
            ),

            glm::vec2(
                center.x,
                center.y
            ),

            node->depth + 1
        );


    // ---------------------------------
    // Dolny-prawy
    // ---------------------------------

    node->children[1] =
        new Node(
            glm::vec2(
                center.x,
                node->minBounds.y
            ),

            glm::vec2(
                node->maxBounds.x,
                center.y
            ),

            node->depth + 1
        );


    // ---------------------------------
    // Górny-lewy
    // ---------------------------------

    node->children[2] =
        new Node(
            glm::vec2(
                node->minBounds.x,
                center.y
            ),

            glm::vec2(
                center.x,
                node->maxBounds.y
            ),

            node->depth + 1
        );


    // ---------------------------------
    // Górny-prawy
    // ---------------------------------

    node->children[3] =
        new Node(
            glm::vec2(
                center.x,
                center.y
            ),

            glm::vec2(
                node->maxBounds.x,
                node->maxBounds.y
            ),

            node->depth + 1
        );
}


void QuadTree::query(
    const Circle& circle,
    std::vector<Circle*>& result
) const
{
    const glm::vec2 position =
        circle.getPosition();


    // Szukamy wszystkich obiektów,
    // które potencjalnie mogą być wystarczająco blisko.
    //
    // maxCircleRadius pozwala nam odrzucić
    // dużą część QuadTree bez dokładnego testu
    // każdej pary.

    const float searchRadius =
        circle.getRadius()
        + maxCircleRadius;


    const glm::vec2 queryMin =
        position
        - glm::vec2(searchRadius);


    const glm::vec2 queryMax =
        position
        + glm::vec2(searchRadius);


    query(
        root,
        queryMin,
        queryMax,
        result
    );
}


void QuadTree::query(
    const Node* node,
    const glm::vec2& queryMin,
    const glm::vec2& queryMax,
    std::vector<Circle*>& result
) const
{
    // Ten node nie przecina obszaru zapytania.
    // Nie musimy schodzić niżej.

    if (
        !overlaps(
            node,
            queryMin,
            queryMax
        )
    )
    {
        return;
    }


    // Dodajemy obiekty znajdujące się
    // bezpośrednio w tym node.

    for (Circle* circle : node->circles)
    {
        result.push_back(circle);
    }


    // Brak dzieci.

    if (node->isLeaf())
    {
        return;
    }


    // Przeszukujemy dzieci,
    // których obszar przecina query.

    for (int i = 0; i < 4; ++i)
    {
        query(
            node->children[i],
            queryMin,
            queryMax,
            result
        );
    }
}


bool QuadTree::overlaps(
    const Node* node,
    const glm::vec2& queryMin,
    const glm::vec2& queryMax
) const
{
    return
        node->maxBounds.x >= queryMin.x &&
        node->minBounds.x <= queryMax.x &&
        node->maxBounds.y >= queryMin.y &&
        node->minBounds.y <= queryMax.y;
}