#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "../utils/platform_utils.hpp"
#include "../window/window_manager.h"

class GameObject {
  protected:
    sf::Uint32 id;
    bool pendingDestroy = false;
    sf::RenderWindow *target;

    sf::Uint32 randomId(uint32_t _seed) {
        std::mt19937 gen(_seed);
        std::uniform_int_distribution<uint32_t> dist(1, std::numeric_limits<uint32_t>::max());
        return dist(gen);
    }

  public:
    GameObject() : target(nullptr) {}

    GameObject(sf::RenderWindow &_target) : target(&_target) { id = randomId(10); }

    virtual ~GameObject() { printf("GameObject %d destroyed\n", id); }

    void setWindow(sf::RenderWindow &_target) { target = &_target; }

    virtual void draw(sf::RenderStates _states = sf::RenderStates::Default) = 0;

    virtual void update(float _deltaTime) = 0;

    bool isPendingDestruction() const { return pendingDestroy; }

    void destroy() { pendingDestroy = true; }

    sf::RenderWindow &getWindow() { return *target; }

    sf::Uint32 getID() { return id; }
};

#endif // GAME_OBJECT_HPP
