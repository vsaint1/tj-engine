#include "game_object.h"

uint32_t GameObject::randomId(uint32_t _seed) {

    std::mt19937 gen(_seed);
    std::uniform_int_distribution<uint32_t> dist(1, std::numeric_limits<uint32_t>::max());
    return dist(gen);
}

GameObject::GameObject(sf::RenderWindow &_target) : target(&_target) { id = randomId(10); }

bool GameObject::isPendingDestruction() const { return pendingDestroy; }

sf::Uint32 GameObject::getID() { return id; }

sf::RenderWindow &GameObject::getWindow() { return *target; }

void GameObject::destroy() { pendingDestroy = true; }

GameObject::~GameObject() { printf("GameObject %d being destroyed\n", id); }