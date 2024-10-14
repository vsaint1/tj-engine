#include "core/Engine.h"


namespace tj {


    Engine::Engine(const std::string& _title, bool _bVsync, sf::Uint8 _fps) {

// COMMENT: we use `windows/osx` for `development`, our focus is mobile/webgl
#if defined(_WIN32) || defined(__EMSCRIPTEN__)
        auto vMode = sf::VideoMode(1280, 720);
#else
        auto vMode = sf::VideoMode::getDesktopMode();
#endif

        std::unique_ptr<sf::RenderWindow> _window =
            std::make_unique<sf::RenderWindow>(vMode, _title, sf::Style::Default);


        if (!_window->isOpen()) {
            TJ_LOG_ERROR("Failed to create window");
        }

        this->frameRate = _fps;
        this->bVsync    = _bVsync;

        if (this->bVsync) {

            _window->setFramerateLimit(_fps);
        }

        _window->setVerticalSyncEnabled(bVsync);


        this->window = std::move(_window);
    }

    void Engine::Start() {
        // COMMENT: initialize here all the `modules`
        auto& _assetsManager = tj::AssetsManager::GetInstance();

        auto _deviceModel   = tj::SystemInfo::GetDeviceModel();
        auto _deviceName    = tj::SystemInfo::GetDeviceName();
        auto _deviceUID     = tj::SystemInfo::GetDeviceUniqueIdentifier();
        auto _deviceBattery = tj::SystemInfo::GetBatteryLevel();

        TJ_LOG_INFO("Device model: %s", _deviceModel.c_str());
        TJ_LOG_INFO("Device name: %s", _deviceName.c_str());
        TJ_LOG_INFO("Device UID: %s", _deviceUID.c_str());
        TJ_LOG_INFO("Battery level: %f", _deviceBattery);
    }

    void Engine::Draw(sf::RenderTarget& _target) {

        this->window->clear(sf::Color::Black);

        this->window->setView(this->window->getDefaultView());

        for (auto& [id, gObject] : this->gameObjects) {

            gObject->Draw(*this->window);
        }

        this->window->display();
    }


    void Engine::Update(float _deltaTime) {
        sf::Event event;

        while (this->window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                this->Destroy();
            }

            if (event.type == sf::Event::Resized) {
                this->window->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
            }

            for (auto& [id, gObject] : this->gameObjects) {

                gObject->Update(_deltaTime);
            }
        }
    }

    void Engine::Run() {
        sf::Clock clock;
        float accumulator     = 0.0f;
        const float DELTA_TIME_STEP = 1.0f / MAX_FRAMERATE;

        while (this->window->isOpen()) {
            sf::Time elapsedTime = clock.restart();
            float deltaTime      = elapsedTime.asSeconds();

            if (deltaTime > 0.1f) {
                deltaTime = 0.1f;
            }

            accumulator += deltaTime;

            while (accumulator >= DELTA_TIME_STEP) {
                this->Update(DELTA_TIME_STEP);
                accumulator -= DELTA_TIME_STEP;
            }

            this->Draw(*this->window);

            float fps = 1.0f / deltaTime;
        }
    }

    void Engine::AddGameObject(std::shared_ptr<GameObject>& _gameObject) {

        sf::Uint32 _id = nextId;
        nextId++;

        _gameObject->SetId(_id);

        this->gameObjects.emplace(_id, _gameObject);
    }


    void Engine::Destroy() {
        this->window->close();
    }

} // namespace tj
