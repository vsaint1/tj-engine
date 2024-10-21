#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Component.h"

class GameObject : public tj::IComponent {

public:
    GameObject(const std::string& _objName) : name(_objName) {}

    virtual void Start() {
        TJ_LOG_INFO("starting %s", this->name.c_str());
    }

    virtual void Update(float _deltaTime) {
        TJ_LOG_INFO("updating object with id: %d", this->id);
    }

    virtual void Draw(sf::RenderTarget& _target) {

        TJ_LOG_INFO("drawing object with id: %d", this->id);
    }

    virtual void Destroy() {
        TJ_LOG_INFO("destroying object with id: %d", this->id);

        this->bPendingDestroy = true;
    }

    bool IsPendingDestroy() {
        return this->bPendingDestroy;
    }

    void SetId(sf::Uint32 _id) {
        this->id = _id;
    }

    sf::Uint32 GetId() {
        return this->id;
    }

private:
    sf::Uint32 id;
    std::string name;
    bool bPendingDestroy = false;
};

#endif // GAMEOBJECT_H
