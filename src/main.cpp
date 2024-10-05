#include "ecs/Camera.h"
#include "math/Mathf.h"
#include "math/Random.h"
#include "sys/SystemInfo.h"
#include "utils/AssetsManager.h"

#include "utils/Json.hpp"

#ifdef SFML_SYSTEM_IOS
#include <SFML/Main.hpp>
#endif

// TODO: refactor to a class EngineCore
int main() {
    tj::Random::seed();

#if _WIN32
    sf::RenderWindow window(sf::VideoMode(1280, 720), "TJ - Game", sf::Style::Close);
#else
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "TJ - Game", sf::Style::Close);
#endif

    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    auto& assetsManager = tj::AssetsManager::getInstance();
    auto& debug         = tj::Debug::geInstance();

    debug.setEnabled(true);
    debug.logInfo(LOG_CONTEXT_FILE, "Test log info");

    auto deviceModel   = tj::SystemInfo::getDeviceModel();
    auto deviceName    = tj::SystemInfo::getDeviceName();
    auto deviceUID     = tj::SystemInfo::getDeviceUniqueIdentifier();
    auto deviceBattery = tj::SystemInfo::getBatteryLevel();

    debug.logInfo(LOG_CONTEXT_FILE, "Test %d", sizeof(uintptr_t));

    debug.logInfo(LOG_CONTEXT_FILE, "Random number %d", tj::Random::range(0, 100));
    debug.logInfo(LOG_CONTEXT_FILE, "Random number %d", tj::Random::range(12, 22));

    sf::FileInputStream fileStream;
    if (!fileStream.open(assetsManager.getAssetsFolder() + "test.json")) {
        debug.logError(
            LOG_CONTEXT_FILE, "Failed to open file 'assets/test.json'. %s", assetsManager.getAssetsFolder().c_str());
    }

    sf::Int64 fileSize = fileStream.getSize();
    if (fileSize <= 0) {
        debug.logError(LOG_CONTEXT_FILE, "File has no content.");
    }

    std::vector<char> fileContent(fileSize);
    if (fileStream.read(fileContent.data(), fileSize) != fileSize) {
        debug.logError(LOG_CONTEXT_FILE, "Error while reading file.");
    }

    std::string jsonData(fileContent.data(), fileSize);

    nlohmann::json jsonObject;
    try {
        jsonObject = nlohmann::json::parse(jsonData);
    } catch (const nlohmann::json::parse_error& e) {
        debug.logError("JSON parsing error, exception %s", e.what());
    }

    auto jObject = jsonObject.dump(4);
    debug.logWarn(LOG_CONTEXT_FILE, "JSON data: %s", jObject.c_str());
    std::string testValue = jsonObject["test"];
    debug.logError(LOG_CONTEXT_FILE, "Test value: %s", testValue.c_str());
    debug.logInfo(
        LOG_CONTEXT_FILE, "Name %s, model %s, uid %s, battery %f", deviceName, deviceModel, deviceUID, deviceBattery);

    auto windowSize = window.getSize();
    tj::Camera camera(windowSize.x, windowSize.y, window);
    camera.setDebugCamera(true);

    assetsManager.loadTexture("player", "player.png");
    assetsManager.loadFont("mine_font", "mine_font.ttf");

    sf::Sprite player(assetsManager.getTexture("player"));
    player.setPosition(
        windowSize.x / 2 - player.getGlobalBounds().width / 2, windowSize.y / 2 - player.getGlobalBounds().height / 2);
    player.setScale(6.0f, 6.0f);

    sf::Font font = assetsManager.getFont("mine_font");
    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(24);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(10.f, 10.f);

    sf::Clock clock;
    float fps = 0.0f;

    const float moveSpeed = 500.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }


            if (event.type == sf::Event::TouchBegan || event.type == sf::Event::TouchMoved) {
                sf::Vector2i touchPosition(event.touch.x, event.touch.y);
                sf::Vector2i touchWorldPosition = camera.screenToWorld(window, touchPosition);

                debug.logInfo(LOG_CONTEXT_FILE, "Touch (%i,%i)", touchWorldPosition.x, touchWorldPosition.y);
                player.setPosition(touchWorldPosition.x - player.getGlobalBounds().width / 2,
                    touchWorldPosition.y - player.getGlobalBounds().height / 2);
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i screenPosition     = sf::Mouse::getPosition(window);
                sf::Vector2i mouseWorldPosition = camera.screenToWorld(window, screenPosition);
                player.setPosition(mouseWorldPosition.x - player.getGlobalBounds().width / 2,
                    mouseWorldPosition.y - player.getGlobalBounds().height / 2);
            }
        }

        sf::Time elapsedTime = clock.restart();
        float deltaTime      = elapsedTime.asSeconds();

        sf::Vector2f velocity(0, 0);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            velocity.y -= moveSpeed * deltaTime;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            velocity.y += moveSpeed * deltaTime;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            velocity.x -= moveSpeed * deltaTime;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            velocity.x += moveSpeed * deltaTime;
        }

        player.move(velocity);

        fps = 1.0f / deltaTime;

#if !defined(__ANDROID__)
        fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));
#endif

        // TODO: refactor draw with the camera view
        window.clear(sf::Color::Black);
        camera.follow(player.getPosition(), deltaTime);
        camera.update(deltaTime);

        camera.draw(window);
        window.draw(player);

        // TODO: refactor draw without the camera view (fixed view)
        window.setView(window.getDefaultView());
        window.draw(fpsText);

        window.display();
    }

    return 0;
}
