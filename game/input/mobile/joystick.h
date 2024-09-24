#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "../../ecs/game_object.h"

namespace tj {

class Joystick : public GameObject {
    sf::CircleShape base;
    sf::CircleShape knob;
    glm::vec2 screenPosition;
    bool bActive = false;

  public:
    Joystick(glm::vec2 _screenPosition, float _tickness = 5.0f);

    void update(float _deltaTime);

    void draw(sf::RenderStates _states = sf::RenderStates::Default);

    sf::Vector2f getMovement();

};
} // namespace tj

#endif // JOYSTICK_H
