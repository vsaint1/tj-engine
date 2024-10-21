#include "components/SpriteComponent.h"
#include "core/Engine.h"
#include "core/Scene.h"
#include "core/SceneManager.h"
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


    CSpriteData playerSprite("player", "player.png", sf::Vector2f(100.f, 100.f));

    playerObj->AddComponent<SpriteComponent>(playerSprite);

    // COMMENT: this is for testing only (should give an log_error adding same component twice)
    playerObj->AddComponent<SpriteComponent>(playerSprite);


    auto mainScene = std::make_unique<tj::Scene>("main_scene");

    auto testScene = std::make_unique<tj::Scene>("test_scene");

    mainScene->AddGameObject(playerObj);
    mainScene->AddGameObject(entityObj);

    engine->GetSceneManager().AddScene(mainScene);
    engine->GetSceneManager().AddScene(testScene);

    engine->ChangeScene("test_scene");

    // COMMENT: this is for testing only, enabling and disabling scenes (this `freezes` the main thread)
    sf::sleep(sf::seconds(10));

    engine->ChangeScene("main_scene");

    engine->Run();

    return 0;
}
