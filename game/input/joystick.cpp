#include "joystick.h"

tj::Joystick::Joystick(glm::vec2 _screenPosition, float _tickness) {
    screenPosition = _screenPosition;

    base.setRadius(100.0f);
    base.setFillColor(sf::Color(100, 100, 100, 100));
    base.setOrigin(100.0f, 100.0f);
    base.setPosition(screenPosition.x, screenPosition.y);
    base.setOutlineColor(sf::Color(255, 255, 255, 255));
    base.setOutlineThickness(_tickness);

    knob.setRadius(50.0f);
    knob.setFillColor(sf::Color(150, 150, 150, 150));
    knob.setOrigin(50.0f, 50.0f);
    knob.setPosition(screenPosition.x, screenPosition.y);
}

void tj::Joystick::update(float _deltaTime) {
    if (sf::Touch::isDown(0)) {
        sf::Vector2i touchPosition = sf::Touch::getPosition(0, *target);
        float distance = sqrt(pow(touchPosition.x - screenPosition.x, 2) +
                              pow(touchPosition.y - screenPosition.y, 2));

        if (distance < base.getRadius()) {
            knob.setPosition(touchPosition.x, touchPosition.y);
            bActive = true;
        }
    } else {
        knob.setPosition(base.getPosition());
        bActive = false;
    }
}

sf::Vector2f tj::Joystick::getMovement() {
    if (bActive) {
        sf::Vector2f moveDirection = knob.getPosition() - base.getPosition();
        return moveDirection * 0.05f;
    }

    return sf::Vector2f(0.0f, 0.0f);
}

void tj::Joystick::draw(sf::RenderStates _states) {
    target->draw(base);
    target->draw(knob);
}
