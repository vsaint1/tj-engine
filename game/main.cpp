#include "utils/platform_utils.hpp"

int main() {

    auto videoMode = sf::VideoMode::getDesktopMode();

    sf::RenderWindow window(videoMode, "Gameless - 0.0.1");
    sf::CircleShape shape(100.f);
    shape.setPosition(100, 100);
    shape.setFillColor(sf::Color::Blue);

    sf::Font font;

    if (!font.loadFromFile(tp::PlatformUtility::assetsFolder() + "mine_font.ttf")) {
        return -1;
    }

    auto textPos = glm::vec2(200.f, 500.f);

    sf::Text text;
    text.setFont(font);
    text.setString("Hello SFML from " + std::string(tp::PlatformUtility::plaftorm()));
    text.setCharacterSize(100);
    text.setStyle(sf::Text::Bold);
    text.setColor(sf::Color::White);
    text.setPosition(textPos.x, textPos.y);

    sf::RectangleShape safeAreaRect;

    sf::View view = window.getDefaultView();

    while (window.isOpen()) {

        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized) {

                view.setSize(static_cast<float>(event.size.width), static_cast<float>(event.size.height));
                window.setView(view);
            }
        }

        sf::Vector2u windowSize = window.getSize();

        sf::FloatRect safeArea = tp::PlatformUtility::getSafeAreaView(glm::vec2(windowSize.x, windowSize.y));

        safeAreaRect.setPosition(safeArea.left, safeArea.top);
        safeAreaRect.setSize(sf::Vector2f(safeArea.width, safeArea.height));
        safeAreaRect.setFillColor(sf::Color::Black);
        safeAreaRect.setOutlineColor(sf::Color(255, 0, 0, 100));
        safeAreaRect.setOutlineThickness(5.0f);

        window.clear();

        window.draw(safeAreaRect);
        window.draw(text);
        window.draw(shape);

        window.display();
    }

    return 0;
}