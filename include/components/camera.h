#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "pch.h"
#include "math/Mathf.h"

namespace tj {

    class Camera {
    public:
        Camera() {
            view.setSize(800, 600);
        }

        Camera(float _width, float _height, sf::RenderWindow& _window);

        void Follow(const sf::Vector2f& targetPosition, float _deltaTime);

        void Zoom(float _factor) {
            view.zoom(_factor);
        }

        void Update(float _deltaTime);

        void Draw(sf::RenderWindow& _window);

        sf::View GetCameraView() const {
            return view;
        }

        sf::Vector2f GetCameraCenter(){
            return view.getCenter();
        }

        void SetDebugCamera(bool _draw) {
            bDrawCamera = _draw;
        }

        sf::Vector2i ScreenToWorldPoint(const sf::RenderWindow& _window, const sf::Vector2i& _screenPosition);

    private:
        sf::View view;
        bool bDrawCamera = false;
    };
}; // namespace tj

#endif // CAMERA_HPP
