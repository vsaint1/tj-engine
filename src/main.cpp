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
    tj::Random::Seed();

#if defined(_WIN32) || defined(__EMSCRIPTEN__)
    sf::RenderWindow window(sf::VideoMode(1280, 720), "TJ - Game", sf::Style::Close);
#else
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "TJ - Game", sf::Style::Close);
#endif

    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    auto& assetsManager = tj::AssetsManager::GetInstance();
    auto& debug         = tj::Debug::GetInstance();
    debug.SetEnabled(true);


    debug.LogInfo(LOG_CONTEXT_FILE, "Test log info");

    auto deviceModel   = tj::SystemInfo::GetDeviceModel();
    auto deviceName    = tj::SystemInfo::GetDeviceName();
    auto deviceUID     = tj::SystemInfo::GetDeviceUniqueIdentifier();
    auto deviceBattery = tj::SystemInfo::GetBatteryLevel();

    debug.LogInfo(LOG_CONTEXT_FILE, "Test %d", sizeof(uintptr_t));

    debug.LogInfo(LOG_CONTEXT_FILE, "Random number between (0,100) %d", tj::Random::Range(0, 100));
    debug.LogInfo(LOG_CONTEXT_FILE, "Random number between (12,22) %d", tj::Random::Range(12, 22));

    sf::FileInputStream fileStream;
    if (!fileStream.open(assetsManager.GetAssetsFolder() + "test.json")) {
        debug.LogError(LOG_CONTEXT_FILE, "Failed to open file '%s/test.json'", assetsManager.GetAssetsFolder().c_str());
    }

    sf::Int64 fileSize = fileStream.getSize();
    if (fileSize <= 0) {
        debug.LogError(LOG_CONTEXT_FILE, "File has no content.");
    }

    std::vector<char> fileContent(fileSize);
    if (fileStream.read(fileContent.data(), fileSize) != fileSize) {
        debug.LogError(LOG_CONTEXT_FILE, "Error while reading file.");
    }

    std::string jsonData(fileContent.data(), fileSize);

    nlohmann::json jsonObject;
    try {
        jsonObject = nlohmann::json::parse(jsonData);
    } catch (const nlohmann::json::parse_error& e) {
        debug.LogError("JSON parsing error, exception %s", e.what());
    }

    auto jObject = jsonObject.dump(4);
    debug.LogWarn(LOG_CONTEXT_FILE, "JSON data: %s", jObject.c_str());
    std::string testValue = jsonObject["test"];
    debug.LogError(LOG_CONTEXT_FILE, "Test value: %s", testValue.c_str());
    debug.LogInfo(
        LOG_CONTEXT_FILE, "Name %s, model %s, uid %s, battery %f", deviceName.c_str(), deviceModel.c_str(), deviceUID.c_str(), deviceBattery);

    auto windowSize = window.getSize();
    tj::Camera camera(windowSize.x, windowSize.y, window);
    camera.SetDebugCamera(true);

    assetsManager.LoadTexture("player", "player.png");
    assetsManager.LoadFont("mine_font", "mine_font.ttf");
    assetsManager.LoadMusic("time_for_adventure", "time_for_adventure.mp3");

    sf::Text playerPos;

    playerPos.setFont(assetsManager.GetFont("mine_font"));

    playerPos.setCharacterSize(24);
    playerPos.setPosition(10.f, 40.f);
    playerPos.setScale(4.0f, 4.0f);
    sf::Sprite player(assetsManager.GetTexture("player"));

    player.setPosition(
        windowSize.x / 2 - player.getGlobalBounds().width / 2, windowSize.y / 2 - player.getGlobalBounds().height / 2);
    player.setScale(6.0f, 6.0f);

    sf::Text fpsText;
    fpsText.setFont(assetsManager.GetFont("mine_font"));
    fpsText.setCharacterSize(24);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(10.f, 5.f);

    sf::Clock clock;
    float fps = 0.0f;

    const float moveSpeed = 500.0f;

    auto& music = assetsManager.GetMusic("time_for_adventure");
    music.setLoop(true);
    music.play();
    music.setVolume(20.0f);

    while (window.isOpen()) {


        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }


            if (event.type == sf::Event::TouchBegan || event.type == sf::Event::TouchMoved) {
                sf::Vector2i touchPosition(event.touch.x, event.touch.y);
                sf::Vector2i touchWorldPosition = camera.ScreenToWorldPoint(window, touchPosition);

                debug.LogInfo(LOG_CONTEXT_FILE, "Touch (%i,%i)", touchWorldPosition.x, touchWorldPosition.y);
                player.setPosition(touchWorldPosition.x - player.getGlobalBounds().width / 2,
                    touchWorldPosition.y - player.getGlobalBounds().height / 2);
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i screenPosition     = sf::Mouse::getPosition(window);
                sf::Vector2i mouseWorldPosition = camera.ScreenToWorldPoint(window, screenPosition);
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

        playerPos.setString("X: " + std::to_string(static_cast<int>(player.getPosition().x))
                            + " Y: " + std::to_string(static_cast<int>(player.getPosition().y)));

        fps = 1.0f / deltaTime;
        fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));

        // TODO: refactor draw with the camera view
        window.clear(sf::Color::Black);
        camera.Follow(player.getPosition(), deltaTime);
        camera.Update(deltaTime);

        camera.Draw(window);
        window.draw(player);

        // TODO: refactor draw without the camera view (fixed view)
        window.setView(window.getDefaultView());

        window.draw(fpsText);
        window.draw(playerPos);

        window.display();
    }

    return 0;
}
