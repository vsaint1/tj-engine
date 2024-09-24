#ifndef HEALTH_BAR_HPP
#define HEALTH_BAR_HPP

#include "../pch.hpp"

namespace tj {

class HealthBar {

  public:
    HealthBar(float _maxValue, float _width, float _height, glm::vec2 _screenPosition)
        : maxValue(_maxValue), currentValue(_maxValue), width(_width), height(_height), screenPosition(_screenPosition) {
        
        background.setSize(sf::Vector2f(_width, _height));
        background.setFillColor(sf::Color::Red);
        background.setOutlineThickness(1.0f);
        background.setOutlineColor(sf::Color::Black);

        foreground.setSize(sf::Vector2f(_width, _height));
        foreground.setFillColor(sf::Color::Green);
    }

    void update(float _value) {
        currentValue = _value;
        float healthPercentage = currentValue / maxValue;
        foreground.setSize(sf::Vector2f(background.getSize().x * healthPercentage, background.getSize().y));
    }

    void draw(sf::RenderWindow &target) {

        background.setPosition(screenPosition.x, screenPosition.y);
        foreground.setPosition(screenPosition.x, screenPosition.y);
        target.draw(background);
        target.draw(foreground);
    }

    glm::vec2 getScreenPosition() { return screenPosition; }

    void setScreenPosition(glm::vec2 _screenPosition) { screenPosition = _screenPosition; }

    float getWidth() { return width; }

    float getHeight() { return height; }

  private:
    glm::vec2 screenPosition;

    sf::RectangleShape background;
    sf::RectangleShape foreground;
    float maxValue;
    float currentValue;
    float width;
    float height;
};
}; // namespace tj
#endif // HEALTH_BAR_HPP
