#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "pch.h"
#include "utils/math_utils.h"

namespace tj {

    class Camera {
    public:
        Camera() {
            view.setSize(800, 600);
        }

        Camera(float _width, float _height, sf::RenderWindow& _window);

        void follow(const sf::Vector2f& targetPosition, float _deltaTime);

        void zoom(float _factor) {
            view.zoom(_factor);
        }

        void update(float _deltaTime);

        void draw(sf::RenderWindow& _window);

        sf::View getView() const {
            return view;
        }

        void setDebugCamera(bool _draw) {
            bDrawCamera = _draw;
        }

        sf::Vector2i screenToWorld(const sf::RenderWindow& _window, const sf::Vector2i& _screenPosition);

    private:
        sf::View view;
        bool bDrawCamera = false;
    };
}; // namespace tj

#endif // CAMERA_HPP
