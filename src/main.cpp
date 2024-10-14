#include "core/Engine.h"
#include "ecs/camera.h"
#include "math/Random.h"
#include "utils/FileHandler.h"

#ifdef SFML_SYSTEM_IOS
#include <SFML/Main.hpp>
#endif

int main() {

    tj::Random::Seed();

    tj::Engine engine("TJ - FW <0.0.1>");

    auto playerObj = std::make_shared<GameObject>("player");
    auto playerObj2 = std::make_shared<GameObject>("player");

    engine.AddGameObject(playerObj);
    engine.AddGameObject(playerObj2);

    engine.Run();

    return 0;
}
