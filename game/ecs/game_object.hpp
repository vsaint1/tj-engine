#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "../utils/platform_utils.hpp"
#include "../window/window_manager.hpp"

class GameObject {

  protected:
    uint32_t id = 0;
    sf::RenderWindow& target; 

  public:
    GameObject() : target(tj::WindowManager::GetInstance().GetWindow()) {}    
    virtual ~GameObject() = default;

    virtual void Draw(sf::RenderStates _states = sf::RenderStates::Default) = 0;

    virtual void Update(float _deltaTime) = 0;

      sf::RenderWindow& GetWindow() {
        return target;
    }
};

#endif // GAME_OBJECT_HPP
