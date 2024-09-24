#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "../utils/platform_utils.hpp"
#include "../core/engine.h"

class GameObject {

  private:
    sf::Uint32 id;
    sf::Uint32 randomId(sf::Uint32 _seed);
    void setWindow(sf::RenderWindow &_target) { target = &_target; }

  protected:
    bool pendingDestroy = false;
    sf::RenderWindow *target;

  public:
    GameObject() : target(nullptr) {}

    GameObject(sf::RenderWindow &_target);

    virtual ~GameObject();

    virtual void draw(sf::RenderStates _states = sf::RenderStates::Default) = 0;

    virtual void update(float _deltaTime) = 0;

    void destroy();

    bool isPendingDestruction() const;

    sf::RenderWindow &getWindow();

    sf::Uint32 getID();
};

#endif // GAME_OBJECT_HPP
