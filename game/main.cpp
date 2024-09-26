#include "ecs/camera.h"
#include "utils/assets_mannager.hpp"


#ifdef SFML_SYSTEM_IOS
    #include <SFML/Main.hpp>
#endif

int main() {

#if SFML_SYSTEM_WINDOWS

    sf::RenderWindow window(sf::VideoMode(800,600), "TJ - Game", sf::Style::Close);
#else
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "TJ - Game", sf::Style::Close);
    
#endif
    
    auto& debug = tj::Debug::geInstance();

    debug.logInfo("Test log info");
    debug.logWarn("Test log warn");
    debug.logError("Test log error");

    window.setFramerateLimit(60);

    Camera camera(800, 600);
    camera.setPosition(0, 0);

    sf::Texture playerTexture;
 
    if (!playerTexture.loadFromFile(tj::AssetsManager::getAssetsFolder() + "player.png")) {
        debug.logError("Failed to load player texture");
    }
    
    sf::Sprite player(playerTexture);
    sf::Vector2u windowSize = window.getSize();
    player.setPosition(
                       windowSize.x / 2 - player.getLocalBounds().width / 2,
                       windowSize.y / 2 - player.getLocalBounds().height / 2
    );
    
    player.setScale(6.0f, 6.0f);

    debug.logInfo("Screen center {%d, %d}", camera.getView().getCenter().x, camera.getView().getCenter().y);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Touch::isDown(0)) {

                sf::Vector2i screenPosition = sf::Touch::getPosition(0, window);
                sf::Vector2i worldPosition = camera.screenToWorld(window,screenPosition);

                debug.logInfo("Mouse/touch at World Position: %d, %d", worldPosition.x, worldPosition.y);

                player.setPosition(
                                   screenPosition.x - player.getLocalBounds().width,
                                   screenPosition.y - player.getLocalBounds().height
                );
            }
        }

        window.clear(sf::Color::Black);

        camera.draw(window);

        window.draw(player);

        window.display();
    }

    return 0;
}
