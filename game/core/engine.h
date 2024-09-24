#ifndef WINDOW_MANAGER_HPP
#define WINDOW_MANAGER_HPP

#include "../ecs/game_object.h"

class GameObject;


namespace tj {

class Engine {
  private:
    sf::RenderWindow window;
    sf::View view;
    std::vector<std::shared_ptr<GameObject>> gameObjects; 

    Engine() = default;

  public:
    static Engine &getInstance() {
        static Engine instance;
        return instance;
    }

    sf::RenderWindow &getWindow() { return window; }

    bool createWindow(const std::string &_title, sf::VideoMode _videoMode = sf::VideoMode::getDesktopMode(), unsigned int _framerate = 60);

    void registerGameObject(const std::shared_ptr<GameObject> &gameObject) { gameObjects.push_back(gameObject); }

    void events();

    void update(float deltaTime);

    void draw();

    void unregisterPendingGameObjects();

    void run();
};

} // namespace tj
#endif // WINDOW_MANAGER_HPP
