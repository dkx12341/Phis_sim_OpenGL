#include "camera.hpp"


Camera::Camera(
    const glm::vec2& position,
    float width,
    float height
)
    : position(position),
      width(width),
      height(height),
      zoomLevel(1.0f)
{
}


void Camera::setPosition(
    const glm::vec2& position
)
{
    this->position = position;
}


void Camera::move(
    const glm::vec2& offset
)
{
    position += offset;
}


void Camera::setZoom(
    float zoom
)
{
    if (zoom <= 0.0f)
        return;

    zoomLevel = zoom;
}


void Camera::zoom(
    float amount
)
{
    setZoom(
        zoomLevel + amount
    );
}


const glm::vec2& Camera::getPosition() const
{
    return position;
}


float Camera::getWidth() const
{
    return width;
}


float Camera::getHeight() const
{
    return height;
}


float Camera::getZoom() const
{
    return zoomLevel;
}