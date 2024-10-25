#ifndef SCENE_H
#define SCENE_H

#include "components/GameObject.h"
#include "math/Random.h"

namespace tj {

    class TJ_API Scene : public sf::NonCopyable {
    public:
        Scene(const std::string& _name = "default") : name(_name) {

            if (_name.empty() || _name == "default") {
                TJ_LOG_ERROR("Scene name cannot be empty or have default name");
            }

            TJ_LOG_INFO("Scene with name: %s created", _name.c_str());
        }

        template <typename T>
        void AddGameObject(std::shared_ptr<T>& _gameObject) {
            static_assert(std::is_base_of<GameObject, T>::value, "T must inherit from GameObject");
            
            if (this == nullptr) {
                TJ_LOG_ERROR("Attempted to call AddGameObject on a null Scene");
                return;
            }

            nextId++;
            gameObjects[nextId] = _gameObject;
            TJ_LOG_INFO("Added GameObject with id: %d, to the scene %s", nextId, this->name.c_str());

            _gameObject->SetId(nextId);
        }

        void RemoveGameObject(sf::Uint32 _id);

        std::string GetName() {
            return this->name;
        }

        void SetActiveScene(bool _bActive) {
            this->bActive = _bActive;
        }

        bool IsActiveScene() {
            return bActive;
        }


        std::map<sf::Uint32, std::shared_ptr<GameObject>>& GetGameObjects() {
            return this->gameObjects;
        }

        void Destroy() {

            this->gameObjects.clear();
        }

    private:
        bool bActive = false;
        std::map<sf::Uint32, std::shared_ptr<GameObject>> gameObjects;
        sf::Uint32 nextId = 1;
        std::string name;
    };
} // namespace tj

#endif // SCENE_H
