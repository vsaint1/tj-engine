#include <SFML/Graphics.hpp>

#if __ANDROID__ || __IPHONEOS__
#define ASSETS_FOLDER ""
#else
#define ASSETS_FOLDER "assets/"
#endif

const char *getPlatform() {
#if defined(_WIN32)
    return "Windows";
#elif __IPHONEOS__
    return "iOS";
#elif __ANDROID__
    return "Android";
#else
    return "Unknown";
#endif
}

int main() {
    auto videoMode = sf::VideoMode::getDesktopMode();

    sf::RenderWindow window(videoMode, "Gameless");
    sf::CircleShape shape(100.f);
    shape.setPosition(100, 100);
    shape.setFillColor(sf::Color::Blue);

    sf::Font font;

    if (!font.loadFromFile(ASSETS_FOLDER "mine_font.ttf")) {
        return -1;
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Hello SFML from " + std::string(getPlatform()));
    text.setCharacterSize(100);
    text.setStyle(sf::Text::Bold);
    text.setColor(sf::Color::White);
    text.setPosition(200, 300);

    while (window.isOpen()) {
        sf::Event event{};
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(text);
        window.draw(shape);
        window.display();
    }

    window.close();

    return 0;
}