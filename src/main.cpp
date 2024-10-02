#include "ecs/camera.h"
#include "sys/system_info.h"
#include "utils/assets_manager.h"
#include "utils/math_utils.h"

#include <SFML/Graphics.hpp>

#ifdef SFML_SYSTEM_IOS
#include <SFML/Main.hpp>
#endif

// TODO: refactor to a class EngineCore

int main() {
    std::srand(std::time(nullptr));

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
    debug.logInfo("Test log info");

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
                
                debug.logInfo("Touch (%i,%i)",touchWorldPosition.x,touchWorldPosition.y);
                player.setPosition(touchWorldPosition.x - player.getGlobalBounds().width / 2,
                                   touchWorldPosition.y - player.getGlobalBounds().height / 2);
            }
            
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i screenPosition = sf::Mouse::getPosition(window);
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
