#include "core/Engine.h"
#include "core/Scene.h"
#include "core/SceneManager.h"
#include "ecs/camera.h"
#include "math/Random.h"
#include "utils/FileHandler.h"

#ifdef SFML_SYSTEM_IOS
#include <SFML/Main.hpp>
#endif

int main() {

    tj::Random::Seed();

    auto engine = std::make_unique<tj::Engine>("TJ - FW <0.0.1>");

    auto playerObj = std::make_shared<GameObject>("player");
    auto entityObj = std::make_shared<GameObject>("entity");

    auto mainScene = std::make_unique<tj::Scene>("main_scene");

    mainScene->AddGameObject(playerObj);
    mainScene->AddGameObject(entityObj);

    engine->GetSceneManager().AddScene(mainScene);

    engine->GetSceneManager().SetEnabled("main_scene", false);

    // COMMENT: this is for testing only, enabling and disabling scenes (this `freezes` the main thread)
    sf::sleep(sf::seconds(10));

    engine->GetSceneManager().SetEnabled("main_scene", true);

    engine->Run();

    return 0;
}
