#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Component.h"
#include <typeindex>

class GameObject {
public:
    GameObject(const std::string& _objName) : name(_objName) {}

    bool IsPendingDestroy() const {
        return this->bPendingDestroy;
    }

    void SetId(sf::Uint32 _id) {
        this->id = _id;
    }

    sf::Uint32 GetId() const {
        return this->id;
    }

    template <typename T, typename... TArgs>
    std::shared_ptr<T> AddComponent(TArgs&&... args) {
        std::string componentName = this->name + "_" + typeid(T).name(); 
        std::shared_ptr<T> component = std::make_shared<T>(std::forward<TArgs>(args)...);

        if (HasComponent<T>()) {
            TJ_LOG_ERROR("Component(%s) already added to GameObject(%s)", typeid(T).name(), this->name.c_str());
            return component;
        }

        components[componentName] = component;
        return component;
    }

    template <typename T>
    std::shared_ptr<T> GetComponent() {
        std::string componentName = this->name + "_" + typeid(T).name(); 

        auto it = components.find(componentName);
        if (it != components.end()) {
            return std::dynamic_pointer_cast<T>(it->second);
        }
  
    
        TJ_LOG_ERROR("Couldn't find component of type: %s for GameObject(%s)", typeid(T).name(), this->name.c_str());
        return nullptr;
    }

    template <typename T>
    bool HasComponent() const {
        std::string componentName = this->name + "_" + typeid(T).name(); 
        return components.find(componentName) != components.end();
    }

    std::unordered_map<std::string, std::shared_ptr<tj::IComponent>> GetComponents() {
        return this->components;
    }

    virtual void Start() = 0;
    virtual void Update(float _deltaTime) = 0;
    virtual void Draw(sf::RenderTarget& _target) = 0;

    std::string GetName() const {
        return this->name;
    }

protected:
    void Destroy() {
        TJ_LOG_INFO("GameObject->Destroy called GameObject(%s:%d) ", this->name.c_str(), this->id);
        this->bPendingDestroy = true;
    }

private:
    sf::Uint32 id;
    std::string name;
    bool bPendingDestroy = false;
    std::unordered_map<std::string, std::shared_ptr<tj::IComponent>> components; 
};

#endif // GAMEOBJECT_H
