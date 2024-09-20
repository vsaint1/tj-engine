#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "../utils/platform_utils.hpp"
#include "../window/window_manager.h"

class GameObject {

  protected:
    uint32_t id = 0;
    sf::RenderWindow& target; 

  public:
    GameObject() : target(tj::WindowManager::GetInstance().getWindow()) {}    
    virtual ~GameObject() = default;

    virtual void draw(sf::RenderStates _states = sf::RenderStates::Default) = 0;

    virtual void update(float _deltaTime) = 0;

      sf::RenderWindow& GetWindow() {
        return target;
    }
};

#endif // GAME_OBJECT_HPP