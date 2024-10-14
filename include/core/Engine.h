#ifndef ENGINE_H
#define ENGINE_H

#include "math/Mathf.h"
#include "math/Random.h"
#include "pch.h"
#include "sys/SystemInfo.h"
#include "utils/AssetsManager.h"

// TODO: REFACTOR AND MAKE VIRTUAL
class GameObject {

public:
    GameObject(const std::string& _objName) : name(_objName){}

    void Start() {
        TJ_LOG_INFO("starting %s", this->name.c_str());
    }

    void Update(float _deltaTime) {
        TJ_LOG_INFO("updating object with id: %d", this->id);
    }

    void Draw(sf::RenderTarget& _target) {

        TJ_LOG_INFO("drawing object with id: %d", this->id);
    }

    void Destroy() {
        TJ_LOG_INFO("destroying object with id: %d", this->id);

        this->bPendingDestroy = true;
    }

    bool IsPendingDestroy() {
        return this->bPendingDestroy;
    }

    void SetId(sf::Uint32 _id) {
        this->id = _id;
    }

    sf::Uint32 GetId() {
        return this->id;
    }

private:
    sf::Uint32 id;
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

        void AddGameObject(std::shared_ptr<GameObject>& _gameObject);

        void Destroy();

        void Run();

        sf::RenderWindow& GetWindow() {
            return *this->window;
        }

        std::map<sf::Uint32, std::shared_ptr<GameObject>>& GetGameObjects() {
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
        std::map<sf::Uint32, std::shared_ptr<GameObject>> gameObjects;
        sf::Uint32 nextId = 1;
        tj::Debug& debug  = tj::Debug::GetInstance();
    };

} // namespace tj

#endif // ENGINE_H
