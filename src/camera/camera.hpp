#pragma once

#include <glm/vec2.hpp>

class Camera
{
public:
    Camera(
        const glm::vec2& position,
        float width,
        float height
    );

    void setPosition(
        const glm::vec2& position
    );

    void move(
        const glm::vec2& offset
    );

    void setZoom(float zoom);

    void zoom(float amount);

    const glm::vec2& getPosition() const;

    float getWidth() const;
    float getHeight() const;

    float getZoom() const;

private:
    glm::vec2 position;

    float width;
    float height;

    float zoomLevel;
}; 