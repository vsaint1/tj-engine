#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "../ecs/game_object.hpp"

namespace tj {

class Joystick : GameObject {
    sf::CircleShape base;
    sf::CircleShape knob;
    glm::vec2 screenPosition;
    bool bActive = false;

  public:
    Joystick(glm::vec2 _screenPosition, float _tickness = 5.0f);

    void Update(float _deltaTime);

    void Draw(sf::RenderStates _states = sf::RenderStates::Default);

    sf::Vector2f GetMovement();

};
} // namespace tj

#endif // JOYSTICK_H
