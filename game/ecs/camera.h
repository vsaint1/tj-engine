#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../pch.hpp"

class Camera {
public:
    Camera(float _width, float _height);

    void setPosition(float _x, float _y) {
        view.setCenter(_x, _y);
    }

    void zoom(float _factor) {
        view.zoom(_factor);
    }

    void update(float _deltaTime);

    void draw(sf::RenderWindow& _window);

    sf::View getView() const {
        return view;
    }

    sf::Vector2f screenToWorld(const sf::RenderWindow& _window, const sf::Vector2i& _screenPosition);

private:
    sf::View view;
};

#endif // CAMERA_HPP
