#include "input/joystick.h"
#include "utils/platform_utils.hpp"
#include "window/window_manager.hpp"

#if __ANDROID__

#include <android/log.h>

#endif

// TODO: create a LogManager for supported platforms

int main() {

    if (!tj::WindowManager::CreateWindow("Gameless - 0.0.1", 60)) {
        std::cerr << "Failed to create window" << std::endl;

#if __ANDROID__

        __android_log_print(ANDROID_LOG_INFO, "TJLog", "Android API %d, device_name %s",
                            android_get_device_api_level(), "unknown");
#endif

    }


#if __ANDROID__

    __android_log_print(ANDROID_LOG_DEBUG, "TJLog", "Created window successfully");

#endif


    sf::RenderWindow &window = tj::WindowManager::GetInstance().GetWindow();

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile(tj::PlatformUtility::GetAssetsFolder() + "player.png")) {
        return -1;
    }

    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTexture);
    playerSprite.setPosition(300, 300);

    sf::Font font;
    if (!font.loadFromFile(tj::PlatformUtility::GetAssetsFolder() + "mine_font.ttf")) {
        return -1;
    }

    auto textPos = glm::vec2(200.f, 500.f);
    sf::Text text;
    text.setFont(font);
    text.setString("Hello SFML from " + std::string(tj::PlatformUtility::plaftorm()));
    text.setCharacterSize(100);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::White);
    text.setPosition(textPos.x, textPos.y);

    sf::RectangleShape safeAreaRect;

    sf::View view = window.getDefaultView();

    const auto screenPos = glm::vec2(100, window.getSize().y - 150);

    tj::Joystick joystick(screenPos);

    const float playerSpeed = 200.0f;

    sf::Clock clock;

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized) {
                view.setSize(static_cast<float>(event.size.width),
                             static_cast<float>(event.size.height));
                window.setView(view);
            }
        }

        sf::Vector2u windowSize = window.getSize();
        sf::FloatRect safeArea = tj::PlatformUtility::GetSafeAreaView(
                glm::vec2(windowSize.x, windowSize.y));

        safeAreaRect.setPosition(safeArea.left, safeArea.top);
        safeAreaRect.setSize(sf::Vector2f(safeArea.width, safeArea.height));
        safeAreaRect.setFillColor(sf::Color::Black);
        safeAreaRect.setOutlineColor(sf::Color(255, 0, 0, 100));
        safeAreaRect.setOutlineThickness(5.0f);

        sf::Vector2f movement(0.f, 0.f);
        float deltaTime = clock.restart().asSeconds();

        if (!tj::PlatformUtility::IsMobile()) {
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

            joystick.Update(deltaTime);
            movement = joystick.GetMovement();
        }

        playerSprite.move(movement);

        window.clear();

        window.draw(safeAreaRect);

        window.draw(playerSprite);

        window.draw(text);

        if (tj::PlatformUtility::IsMobile()) {
            joystick.Draw();
        }

        window.display();
    }

    return 0;
}
