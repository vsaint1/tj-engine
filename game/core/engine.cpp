#include "engine.h"

bool tj::Engine::createWindow(const std::string &_title, sf::VideoMode _videoMode, unsigned int _framerate) {
    window.create(_videoMode, _title);
    window.setFramerateLimit(_framerate);
    return window.isOpen();
}

void tj::Engine::events() {
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

void tj::Engine::update(float deltaTime) {
    for (auto &gameObject : gameObjects) {
        gameObject->update(deltaTime);
    }
}

void tj::Engine::draw() {
    window.clear(sf::Color::White);
    for (auto &gameObject : gameObjects) {
        gameObject->draw();
    }
    window.display();
}

void tj::Engine::unregisterPendingGameObjects() {
    for (auto obj = gameObjects.begin(); obj != gameObjects.end();) {
        
        if ((*obj)->isPendingDestruction()) {
            printf("GameObject %d being destroyed\n", (*obj)->getID());
            obj = gameObjects.erase(obj);
        } else {
            obj++;
        }


    }
}

void tj::Engine::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        events();
        update(deltaTime);
        unregisterPendingGameObjects();
        draw();
    }
}
