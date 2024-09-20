#include "window_manager.h"

bool tj::WindowManager::createWindow(const std::string &_title, unsigned int _framerate) {
    window.create(sf::VideoMode::getDesktopMode(), _title);

    if (!window.isOpen())
        return false;

    window.setFramerateLimit(_framerate);
    view = window.getDefaultView();

    return true;
}

void tj::WindowManager::draw() {
    window.clear();
    for (auto &callback : drawCallbacks) {
        callback();
    }
    window.display();
}

void tj::WindowManager::events() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::Resized) {
            view.setSize(static_cast<float>(event.size.width), static_cast<float>(event.size.height));
            window.setView(view);
        }

        for (auto &callback : eventCallbacks) {
            callback(event);
        }
    }
}

void tj::WindowManager::update(float deltaTime) {

    for (auto &callback : updateCallbacks) {
        callback(deltaTime);
    }
}

void tj::WindowManager::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        events();
        update(deltaTime);
        draw();
    }
}