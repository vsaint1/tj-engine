#include "window_manager.h"

bool tj::WindowManager::createWindow(const std::string &_title, sf::VideoMode _videoMode, unsigned int _framerate) {
    window.create(_videoMode, _title);
    window.setFramerateLimit(_framerate);
    return window.isOpen();
}

void tj::WindowManager::events() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        for (auto &gameObject : gameObjects) {
            // TODO
        }
    }
}

void tj::WindowManager::update(float deltaTime) {
    for (auto &gameObject : gameObjects) {
        gameObject->update(deltaTime);
    }
}

void tj::WindowManager::draw() {
    window.clear(sf::Color::White);
    for (auto &gameObject : gameObjects) {
        gameObject->draw();
    }
    window.display();
}

void tj::WindowManager::unregisterPendingGameObjects() {
    for (auto obj = gameObjects.begin(); obj != gameObjects.end();) {
        
        if ((*obj)->isPendingDestruction()) {
            printf("GameObject %d being destroyed\n", (*obj)->getID());
            obj = gameObjects.erase(obj);
        } else {
            obj++;
        }


    }
}

void tj::WindowManager::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        events();
        update(deltaTime);
        unregisterPendingGameObjects();
        draw();
    }
}
