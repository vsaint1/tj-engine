#ifndef WINDOW_MANAGER_HPP
#define WINDOW_MANAGER_HPP

#include "../pch.hpp"

namespace tj {

class WindowManager {

  public:
    static bool CreateWindow(std::string _title = "TapJoy - 0.0.1", int _fps = 60) {

        sf::RenderWindow window = sf::RenderWindow(sf::VideoMode::getDesktopMode(), _title, sf::Style::Close);

        if (!window.isOpen()) {
            return false;
        } else {
            window.setFramerateLimit(_fps);
            return true;
        }
    }

    static WindowManager &GetInstance() {
        static WindowManager instance;
        return instance;
    }

    sf::RenderWindow &GetWindow() { return window; }

  private:
    sf::RenderWindow window;

    WindowManager() : window(sf::VideoMode::getDesktopMode(), "TapJoy - 0.0.1", sf::Style::Close) {}

    WindowManager(const WindowManager &) = delete;
    void operator=(const WindowManager &) = delete;
};
} // namespace tj

#endif // WINDOW_MANAGER_HPP
