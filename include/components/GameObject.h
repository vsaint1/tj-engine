#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Component.h"

class GameObject {

public:
    GameObject(const std::string& _objName) : name(_objName) {}

    bool IsPendingDestroy() {
        return this->bPendingDestroy;
    }

    void SetId(sf::Uint32 _id) {
        this->id = _id;
    }

    sf::Uint32 GetId() {
        return this->id;
    }

    template <typename T, typename... TArgs>
    void AddComponent(TArgs&&... args) {
        std::shared_ptr<T> component = std::make_shared<T>(std::forward<TArgs>(args)...);

        if (HasComponent<T>()) {
            TJ_LOG_ERROR("Component(%s) already added to GameObject(%s)", typeid(T).name(), this->name.c_str());
            return;
        }

        components.emplace(typeid(T).name(), component);
    }


    template <typename T>
    std::shared_ptr<T> GetComponent() {

        for (auto& component : components) {

            auto dynComponent = std::dynamic_pointer_cast<T>(component);

            if (dynComponent) {
                return dynComponent;
            }
        }

        TJ_LOG_ERROR("Couldn't find component of type: %s", typeid(T).name());

        return nullptr;
    }

    template <typename T>
    bool HasComponent() {
        return components.contains(typeid(T).name());
    }

    std::unordered_map<std::string, std::shared_ptr<tj::IComponent>>& GetComponents() {
        return this->components;
    }

    void Destroy() {
        TJ_LOG_INFO("Destroying GameObject(%s:%d) ", this->name.c_str(), this->id);

        this->bPendingDestroy = true;
    }


private:
    sf::Uint32 id;
    std::string name;
    bool bPendingDestroy = false;
    std::unordered_map<std::string, std::shared_ptr<tj::IComponent>> components;
};

#endif // GAMEOBJECT_H
