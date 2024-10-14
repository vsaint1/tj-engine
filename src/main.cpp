#include "ecs/camera.h"
#include "math/Mathf.h"
#include "math/Random.h"
#include "sys/SystemInfo.h"
#include "utils/AssetsManager.h"
#include "utils/FileHandler.h"

#ifdef SFML_SYSTEM_IOS
#include <SFML/Main.hpp>
#endif

int main() {
    tj::Random::Seed();

#if defined(_WIN32) || defined(__EMSCRIPTEN__)
    sf::RenderWindow window(sf::VideoMode(1280, 720), "TJ - Game", sf::Style::Default);
#else
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "TJ - Game", sf::Style::Default);
#endif

    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);

    auto& assetsManager = tj::AssetsManager::GetInstance();
    auto& debug         = tj::Debug::GetInstance();

    debug.SetSaveToDisk(false);
    // debug.SetEnabled(false); // COMMENT: By default debug is enabled

    auto deviceModel   = tj::SystemInfo::GetDeviceModel();
    auto deviceName    = tj::SystemInfo::GetDeviceName();
    auto deviceUID     = tj::SystemInfo::GetDeviceUniqueIdentifier();
    auto deviceBattery = tj::SystemInfo::GetBatteryLevel();

    TJ_LOG_INFO("Test log info");

    TJ_LOG_INFO("Random number between (0,100) %d", tj::Random::Range(0, 100));
    TJ_LOG_INFO("Random number between (12,22) %d", tj::Random::Range(12, 22));


    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    assetsManager.LoadFont("mine_font", "mine_font.ttf");
    assetsManager.LoadFont("mine_font", "mine_font.ttf");
    assetsManager.LoadMusic("time_for_adventure", "time_for_adventure.mp3");
    assetsManager.LoadTexture("player", "player.png");
    assetsManager.LoadTexture("skeleton_spirte", "skeleton_spirte.png"); // ERROR JUST FOR TESTING
    assetsManager.LoadTexture("skeleton_sprite", "skeleton_sprite.png");

    sf::Text randomText;
    randomText.setFont(assetsManager.GetFont("mine_font"));
    randomText.setCharacterSize(32);
    randomText.setString("Hello world!");


    sf::Clock clock;
    float fps = 0.0f;


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
        }

        sf::Time deltaTime     = clock.restart();
        float deltaTimeSeconds = deltaTime.asSeconds();
        deltaTimeSeconds       = tj::Mathf::Clamp(deltaTimeSeconds, 0.0f, 0.1f);
        fps                    = 1.0f / deltaTimeSeconds;


        window.clear();
        window.draw(shape);
        window.draw(randomText);


        window.display();
    }


    return 0;
}
