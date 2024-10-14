#ifndef ENGINE_H
#define ENGINE_H

#include "math/Mathf.h"
#include "pch.h"
#include "sys/SystemInfo.h"
#include "utils/AssetsManager.h"

// TODO: REFACTOR AND MAKE VIRTUAL
class GameObject {

public:
    GameObject(const std::string& _objName) : name(_objName) {}

    void Start() {
        TJ_LOG_INFO("starting %s", this->name.c_str());
    }

    void Update(float _deltaTime) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            TJ_LOG_INFO("updating %s", this->name.c_str());
        }
    }

    void Draw(sf::RenderTarget& _target) {

        TJ_LOG_INFO("drawing %s", this->name.c_str());
    }

    void Destroy() {
        TJ_LOG_INFO("destroying %s", this->name.c_str());
    }

private:
    std::string name;
    bool bPendingDestroy = false;
};

namespace tj {

    class TJ_API Engine {
    public:
        Engine(const std::string& _title, sf::Uint8 _fps = 60, bool _bVsync = true);

        void Start();

        void Update(float _deltaTime);

        void Draw(sf::RenderTarget& _target);

        void AddGameObject(std::shared_ptr<GameObject>& _gameObject) {
            this->gameObjects.emplace_back(_gameObject);
        }

        void Destroy();

        void Run();

        sf::RenderWindow& GetWindow() {
            return *this->window;
        }

        std::vector<std::shared_ptr<GameObject>>& GetGameObjects() {
            return this->gameObjects;
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


    private:
        Engine(Engine const& other)            = delete;
        Engine& operator=(Engine const& other) = delete;

        bool bVsync;
        sf::Uint8 frameRate;
        std::unique_ptr<sf::RenderWindow> window;
        std::vector<std::shared_ptr<GameObject>> gameObjects;

        tj::Debug& debug = tj::Debug::GetInstance();
    };

} // namespace tj

#endif // ENGINE_H
