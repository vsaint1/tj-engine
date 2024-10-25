#include "core/Scene.h"


namespace tj {



    void Scene::RemoveGameObject(sf::Uint32 _id) {

        if (this->gameObjects.find(_id) != this->gameObjects.end()) {

            this->gameObjects.erase(_id);
        } else {

            TJ_LOG_ERROR("Couldn't find object with id: %d", _id);
        }
    }
} // namespace tj
