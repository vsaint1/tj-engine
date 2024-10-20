#ifndef ENGINE_H
#define ENGINE_H

#include "math/Mathf.h"
#include "SceneManager.h"
#include "sys/SystemInfo.h"
#include "utils/AssetsManager.h"

const float MAX_FRAMERATE = 60.f;

namespace tj {

    class TJ_API Engine {
    public:
        Engine(const std::string& _title,  bool _bVsync = true,sf::Uint8 _fps = 60);

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
        

    private:
        Engine(Engine const& other)            = delete;
        Engine& operator=(Engine const& other) = delete;

        bool bVsync;
        sf::Uint8 frameRate;
        std::unique_ptr<sf::RenderWindow> window;
   
        tj::Debug& debug  = tj::Debug::GetInstance();

        tj::SceneManager&  sceneManager = tj::SceneManager::GetInstance();
    };

} // namespace tj

#endif // ENGINE_H
