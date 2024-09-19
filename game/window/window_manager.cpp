#include "window_manager.h"

bool tj::WindowManager::CreateWindow(const std::string &_title, unsigned int _framerate) {
    window.create(sf::VideoMode::getDesktopMode(), _title);

    if (!window.isOpen())
        return false;

    window.setFramerateLimit(_framerate);
    view = window.getDefaultView();

    return true;
}

void tj::WindowManager::Draw() {
    window.clear();
    for (auto &callback : drawCallbacks) {
        callback();
    }
    window.display();
}

void tj::WindowManager::Events() {
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

void tj::WindowManager::Update(float deltaTime) {

    for (auto &callback : updateCallbacks) {
        callback(deltaTime);
    }
}

void tj::WindowManager::Run() {
    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        Events();
        Update(deltaTime);
        Draw();
    }
}