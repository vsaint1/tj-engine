#include "ecs/camera.h"

int main() {

    sf::RenderWindow window(sf::VideoMode(1280, 720), "TJ Game Engine", sf::Style::Close);

    auto& debug = tj::Debug::geInstance();

    debug.logInfo("Test log info");
    debug.logWarn("Test log warn");

    debug.logError("Test log error");

    window.setFramerateLimit(60);

    Camera camera(1280, 720);

    sf::CircleShape circle(50);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(300, 300);

    debug.logInfo("Screen center {%f, %f}", camera.getView().getCenter().x, camera.getView().getCenter().y);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Touch::isDown(0)) {
                sf::Vector2i screenPosition = sf::Mouse::getPosition(window);
                sf::Vector2f worldPosition  = camera.screenToWorld(window, screenPosition);

                debug.logInfo("Mouse Clicked at World Position: %f, %f", worldPosition.x, worldPosition.y);

                circle.setPosition(worldPosition.x - circle.getRadius(), worldPosition.y - circle.getRadius());
            }
            
        }

        window.clear(sf::Color::Black);

        camera.draw(window);

        window.draw(circle);

        window.display();
    }

    return 0;
}
