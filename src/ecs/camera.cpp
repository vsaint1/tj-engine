#include "ecs/camera.h"
namespace tj {

    void Camera::follow(const sf::Vector2f& targetPosition, float _deltaTime) {
        sf::Vector2f currentPosition = view.getCenter();
        sf::Vector2f newPosition     = tj::Mathf::lerp(currentPosition, targetPosition, 0.3f);
        view.setCenter(newPosition);
    }


    void Camera::update(float _deltaTime) {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            view.zoom(1.1f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            view.zoom(0.9f);
        }
    }

    Camera::Camera(float _width, float _height, sf::RenderWindow& _window) {
        view.setSize(_width, _height);
        view.setCenter(_width / 2, _height / 2);
    }


    void Camera::draw(sf::RenderWindow& _window) {
        _window.setView(view);

        if (bDrawCamera) {
            sf::Vector2f rectSize = sf::Vector2f(view.getSize().x * 0.9f, view.getSize().y * 0.9f);
            sf::RectangleShape rect(rectSize);

            rect.setPosition(view.getCenter().x - rectSize.x / 2, view.getCenter().y - rectSize.y / 2);

            rect.setOutlineColor(sf::Color::Red);
            rect.setOutlineThickness(2.0f);
            rect.setFillColor(sf::Color::Transparent);

            _window.draw(rect);
        }
    }

    sf::Vector2i Camera::screenToWorld(const sf::RenderWindow& _window, const sf::Vector2i& _screenPosition) {

        sf::Vector2f worldPos = _window.mapPixelToCoords(_screenPosition, view);

        return sf::Vector2i(static_cast<int>(worldPos.x), static_cast<int>(worldPos.y));
    }

} // namespace tj
