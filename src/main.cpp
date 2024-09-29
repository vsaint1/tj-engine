#include "ecs/camera.h"
#include "sys/system_info.h"
#include "utils/assets_manager.h"
#include "utils/math_utils.h"

#ifdef SFML_SYSTEM_IOS
#include <SFML/Main.hpp>
#endif


int main() {

    std::srand(std::time(nullptr));

#if _WIN32
    sf::RenderWindow window(sf::VideoMode(800, 600), "TJ - Game", sf::Style::Close);
#else
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "TJ - Game", sf::Style::Close);
#endif

    // window.setFramerateLimit(60); // disabled for testing
    // window.setVerticalSyncEnabled(true); // disabled for testing

    auto& assetsManager = tj::AssetsManager::getInstance();

    auto& debug         = tj::Debug::geInstance();

    debug.setEnabled(true);
    debug.logInfo("Test log info");
    debug.logWarn("Test log warn");
    debug.logError("Test log error");

    auto deviceName = tj::SystemInfo::getDeviceName();

    debug.logError("Device name %s", deviceName);
    debug.logError("Device battery %f", tj::SystemInfo::getBatteryLevel());
    debug.logInfo("Device model %s", tj::SystemInfo::getDeviceModel());
    debug.logError("Device UID %s", tj::SystemInfo::getDeviceUniqueIdentifier());

    Camera camera(800, 600);
    camera.setPosition(0, 0);

    assetsManager.loadTexture("player", "player.png");
    assetsManager.loadFont("mine_font", "mine_font.ttf");

    sf::Sprite player(assetsManager.getTexture("player"));
    sf::Vector2u windowSize = window.getSize();
    player.setPosition(
        windowSize.x / 2 - player.getGlobalBounds().width / 2, windowSize.y / 2 - player.getGlobalBounds().height / 2);
    player.setScale(6.0f, 6.0f);

    debug.logInfo("Screen center {%d, %d}", camera.getView().getCenter().x, camera.getView().getCenter().y);
    int random = tj::MathUtility::numberBetween(0, 20);


    debug.logError("value = %d", random);

    sf::Font font = assetsManager.getFont("mine_font");
    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(24);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(10.f, 10.f);

    sf::Clock clock;
    float fps = 0.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Touch::isDown(0)) {

                sf::Vector2i screenPosition =
                    tj::PlatformUtility::isMobile() ? sf::Touch::getPosition(0) : sf::Mouse::getPosition(window);

                sf::Vector2i mouseWorldPosition = camera.screenToWorld(window, screenPosition);

                debug.logInfo("Mouse/touch at World Position: %d, %d", mouseWorldPosition.x, mouseWorldPosition.y);

                player.setPosition(screenPosition.x - player.getGlobalBounds().width / 2,
                    screenPosition.y - player.getGlobalBounds().height / 2);
            }
        }

        sf::Time elapsedTime = clock.restart();

        fps = 1.0f / elapsedTime.asSeconds();

// Fix: debug crash on android
#if !defined(__ANDROID__)
        fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));
#endif
        window.clear(sf::Color::Black);
        camera.draw(window);
        window.draw(player);

        window.draw(fpsText);

        window.display();
    }

    return 0;
}
