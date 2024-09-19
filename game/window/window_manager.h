#ifndef WINDOW_MANAGER_HPP
#define WINDOW_MANAGER_HPP

#include "../pch.hpp"

// TODO: refactor and create fn definitions
namespace tj {
class WindowManager {
  private:
    sf::RenderWindow window;
    sf::View view;
    std::vector<std::function<void(float)>> updateCallbacks;
    std::vector<std::function<void()>> drawCallbacks;
    std::vector<std::function<void(sf::Event &)>> eventCallbacks;

    WindowManager() = default;

  public:
    static WindowManager &GetInstance() {
        static WindowManager instance;
        return instance;
    }

    bool CreateWindow(const std::string &_title, unsigned int _framerate);

    sf::RenderWindow &GetWindow() { return window; }

    void RegisterUpdateCallback(std::function<void(float)> updateCallback) { updateCallbacks.push_back(updateCallback); }

    void RegisterDrawCallback(std::function<void()> drawCallback) { drawCallbacks.push_back(drawCallback); }

    void RegisterEventCallback(std::function<void(sf::Event &)> eventCallback) { eventCallbacks.push_back(eventCallback); }


    void Events();

    void Update(float deltaTime);

    void Draw();

    void Run();
};
} // namespace tj

#endif // WINDOW_MANAGER_HPP
