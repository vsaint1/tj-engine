#include "input/joystick.h"
#include "utils/platform_utils.hpp"
#include "window/window_manager.h"

#if __ANDROID__
#include <android/log.h>
#endif

int main() {
    if (!tj::WindowManager::GetInstance().createWindow("Gameless - 0.0.1", 60)) {
        std::cerr << "Failed to create window" << std::endl;
#if __ANDROID__
        __android_log_print(ANDROID_LOG_INFO, "TJLog", "Failed to create window");
#endif
        return -1;
    }

    auto test = glm::vec2(5.0f,20.0f);

    const auto a = glm::dot(test, test);
    

    sf::RenderWindow &window = tj::WindowManager::GetInstance().getWindow();

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile(tj::PlatformUtility::getAssetsFolder() + "player.png")) {
        return -1;
    }

    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTexture);
    playerSprite.setPosition(300, 300);

    sf::Font font;
    if (!font.loadFromFile(tj::PlatformUtility::getAssetsFolder() + "mine_font.ttf")) {
        return -1;
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Hello SFML from " + std::string(tj::PlatformUtility::plaftorm()));
    text.setCharacterSize(100);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::White);
    text.setPosition(200.f, 500.f);

    sf::RectangleShape safeAreaRect;

    const auto screenPos = glm::vec2(100, window.getSize().y - 150);
    tj::Joystick joystick(screenPos);

    const float playerSpeed = 200.0f;

    tj::WindowManager::GetInstance().registerUpdateCallback([&](float deltaTime) {
        sf::Vector2f movement(0.f, 0.f);

        if (!tj::PlatformUtility::isMobile()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                movement.y -= playerSpeed * deltaTime;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                movement.x -= playerSpeed * deltaTime;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                movement.y += playerSpeed * deltaTime;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                movement.x += playerSpeed * deltaTime;
            }

        } else {
            joystick.update(deltaTime);
            movement = joystick.getMovement();
        }

        playerSprite.move(movement);
    });

    tj::WindowManager::GetInstance().registerDrawCallback([&]() {
        window.draw(playerSprite);
        window.draw(text);

        if (tj::PlatformUtility::isMobile()) {
            joystick.draw();
        }
    });

    tj::WindowManager::GetInstance().registerEventCallback([&](sf::Event &event) {
        if (event.type == sf::Event::Resized) {
            sf::View view = window.getDefaultView();
            view.setSize(static_cast<float>(event.size.width), static_cast<float>(event.size.height));
            window.setView(view);
        }
    });

    tj::WindowManager::GetInstance().run();

    return 0;
}
