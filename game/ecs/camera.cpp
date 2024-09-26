#include "camera.h"

void Camera::update(float _deltaTime) {}

Camera::Camera(float _width, float _height) {
    view.setSize(_width, _height);
    view.setCenter(_width / 2, _height / 2);
}

void Camera::draw(sf::RenderWindow& _window) {
    _window.setView(view);
    _window.setView(_window.getDefaultView());
}

sf::Vector2i Camera::screenToWorld(const sf::RenderWindow& _window, const sf::Vector2i& _screenPosition) {
    sf::Vector2f worldPos = _window.mapPixelToCoords(_screenPosition);

    return sf::Vector2i(static_cast<int>(worldPos.x), static_cast<int>(worldPos.y));
}
