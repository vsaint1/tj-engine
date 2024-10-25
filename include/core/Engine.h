#ifndef ENGINE_H
#define ENGINE_H

#include "SceneManager.h"
#include "math/Mathf.h"
#include "sys/SystemInfo.h"
#include "utils/AssetsManager.h"

const float MAX_FRAMERATE = 60.f;

namespace tj {

    class TJ_API Engine {
    public:

        static Engine& GetInstance() {
            static Engine instance;
            return instance;
        }

        bool Create(const std::string& _title, bool _bVsync = true, sf::Uint8 _fps = 60);

        void Start();

        void Update(float _deltaTime);

        void Draw(sf::RenderTarget& _target);

        void Destroy();

        void Run();

        sf::RenderWindow& GetWindow() {
            return *this->window;
        }


        sf::Uint8 GetFrameRate() {
            return this->frameRate;
        }

        void SetVsync(bool _bVsync) {
            this->bVsync = _bVsync;
        }

        void SetFrameRate(sf::Uint8 _frameRate) {
            this->frameRate = _frameRate;
        }

        tj::SceneManager& GetSceneManager() {
            return this->sceneManager;
        }

        void ChangeScene(const std::string& _newScene) {
            this->sceneManager.ChangeScene(_newScene, true);
            this->Start();
        }

        template <typename T>
        std::shared_ptr<T> GetGameObject(const std::string& _name) {
            auto sceneName = this->sceneManager.GetActiveScene();

            auto gameObjects = this->sceneManager.GetScenes()[sceneName]->GetGameObjects();

            for (auto [id, gObject] : gameObjects) {
                if (gObject->GetName() == _name) {
                    return std::dynamic_pointer_cast<T>(gObject);
                }
            }

            TJ_LOG_ERROR("Couldn't find object with name: %s", _name.c_str());

            return nullptr;
        }

    private:
        Engine() = default;

        static tj::Engine* instance;
        bool bVsync;
        sf::Uint8 frameRate;
        std::unique_ptr<sf::RenderWindow> window;

        tj::Debug& debug = tj::Debug::GetInstance();

        tj::SceneManager& sceneManager = tj::SceneManager::GetInstance();
    };

} // namespace tj

#endif // ENGINE_H
