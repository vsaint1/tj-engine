#include "core/Scene.h"


namespace tj {

    void Scene::AddGameObject(std::shared_ptr<GameObject>& _gameObject) {

        if (this == nullptr) {
            TJ_LOG_ERROR("Attempted to call AddGameObject on a null Scene");
            return;
        }

        nextId++;
        gameObjects[nextId] = _gameObject;
        TJ_LOG_INFO("Added GameObject with id: %d, to the scene %s", nextId, this->name.c_str());

        _gameObject->SetId(nextId);
    }

    void Scene::RemoveGameObject(sf::Uint32 _id) {

        if (this->gameObjects.find(_id) != this->gameObjects.end()) {

            this->gameObjects.erase(_id);
        } else {

            TJ_LOG_ERROR("Couldn't find object with id: %d", _id);
        }
    }
} // namespace tj
