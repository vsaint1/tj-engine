#include "core/SceneManager.h"

namespace tj {

    void SceneManager::ChangeScene(const std::string& _name, bool _bEnable) {
        
        if (this->scenes.find(_name) == this->scenes.end()) {
            TJ_LOG_ERROR("Couldn't find scene with name: %s", _name.c_str());
        }

        if (this->scenes.find(_name) != this->scenes.end()) {


            this->scenes.find(this->activeScene)->second->SetActiveScene(false);
            
            TJ_LOG_INFO("Disabling scene: %s", this->activeScene.c_str());

            this->activeScene = _name;

            this->scenes.find(_name)->second->SetActiveScene(_bEnable);
            const char* status = _bEnable ? "Enabled" : "Disabled";
            TJ_LOG_INFO("%s scene: %s", status, this->activeScene.c_str());
        }
    }

    void SceneManager::AddScene(std::unique_ptr<Scene>& _scene) {

        if (_scene->GetName() == "main_scene") {
            _scene->SetActiveScene(true);
        } else {
            _scene->SetActiveScene(false);
        }


        if (this->scenes.find(_scene->GetName()) != this->scenes.end()) {
            TJ_LOG_ERROR("Scene with name %s already exists", _scene->GetName().c_str());
        }

        this->scenes.emplace(_scene->GetName(), std::move(_scene));
    }

    void SceneManager::RemoveScene(const std::string& _name) {

        if (this->scenes.find(_name) == this->scenes.end()) {

            TJ_LOG_ERROR("Couldn't find scene with name: %s", _name.c_str());
        }

        if (this->scenes.find(_name) != this->scenes.end()) {


            if (this->scenes.find(_name)->second->IsActiveScene()) {
                TJ_LOG_ERROR("Can't remove active scene: %s", _name.c_str());
            } else {

                this->scenes.erase(_name);
            }
        }
    }

} // namespace tj
