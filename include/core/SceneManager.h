#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Scene.h"

namespace tj {

    class TJ_API SceneManager : public sf::NonCopyable {


    public:
        static SceneManager& GetInstance() {
            static SceneManager instance;
            return instance;
        }

        void AddScene(std::unique_ptr<Scene>& _scene);

        void ChangeScene(const std::string& _name, bool _bEnable);

        void RemoveScene(const std::string& _name);

        std::string GetActiveScene() {
            return this->activeScene;
        }

        std::map<std::string, std::unique_ptr<Scene>>& GetScenes() {
            return this->scenes;
        }

    private:
        SceneManager() = default;
        static SceneManager* instance;
        SceneManager(const SceneManager& other)            = delete;
        SceneManager& operator=(const SceneManager& other) = delete;
        std::map<std::string, std::unique_ptr<Scene>> scenes;
        std::string activeScene = "main_scene";
    };


} // namespace tj

#endif // SCENEMANAGER_H
