#include "components/SpriteComponent.h"
#include "core/Engine.h"
#include "core/Scene.h"
#include "core/SceneManager.h"
#include "math/Random.h"
#include "utils/FileHandler.h"

#ifdef SFML_SYSTEM_IOS
#include <SFML/Main.hpp>
#endif

class Player : public GameObject {

public:
    Player() : GameObject("player") {}

    void Start() override {

        TJ_LOG_INFO("Player Start called");
        CSpriteData playerSprite("player", "player.png", sf::Vector2f(100.f, 100.f));

        this->spriteComponent = this->AddComponent<SpriteComponent>(playerSprite);
        this->spriteComponent->SetScale(sf::Vector2f(2.0f, 2.0f));
    }

    void Update(float _deltaTime) override {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            this->spriteComponent->SetPosition(sf::Vector2f(
                this->spriteComponent->GetPosition().x - _deltaTime * speed, this->spriteComponent->GetPosition().y));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            this->spriteComponent->SetPosition(sf::Vector2f(
                this->spriteComponent->GetPosition().x + _deltaTime * speed, this->spriteComponent->GetPosition().y));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            this->spriteComponent->SetPosition(sf::Vector2f(
                this->spriteComponent->GetPosition().x, this->spriteComponent->GetPosition().y - _deltaTime * speed));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

            this->spriteComponent->SetPosition(sf::Vector2f(
                this->spriteComponent->GetPosition().x, this->spriteComponent->GetPosition().y + _deltaTime * speed));
        }

    }

    void Draw(sf::RenderTarget& _target) override {

        this->spriteComponent->Draw(_target);
    }

protected:
    // COMMENT: this is optional
    std::shared_ptr<SpriteComponent> spriteComponent;

private:
    float speed = 200.f;
};

class Entity : public GameObject {

public:
    Entity() : GameObject("entity") {}

    void Start() override {

        TJ_LOG_INFO("Entity Start called");

        CSpriteData entitySprite("skeleton_sprite", "skeleton_sprite.png", sf::Vector2f(200.f, 200.f),
            sf::Vector2i(48, 48), sf::Vector2i(0, 0));

        this->spriteComponent = this->AddComponent<SpriteComponent>(entitySprite);
    }

    void Update(float _deltaTime) override {}

    void Draw(sf::RenderTarget& _target) override {

        this->spriteComponent->Draw(_target);
    }

private:
    std::shared_ptr<SpriteComponent> spriteComponent;
};

int main() {

    tj::Random::Seed();


    auto& engine = tj::Engine::GetInstance();

    engine.Create("TJ - FW <0.0.1>");

    auto playerObj = std::make_shared<Player>();

    auto entityObj = std::make_shared<Entity>();


    auto mainScene = std::make_unique<tj::Scene>("main_scene");

    auto testScene = std::make_unique<tj::Scene>("test_scene");


    mainScene->AddGameObject(entityObj);
    mainScene->AddGameObject(playerObj);

    engine.GetSceneManager().AddScene(mainScene);

    // engine.ChangeScene("test_scene");

    // COMMENT: this is for testing only, enabling and disabling scenes (this `freezes` the main thread)
    // sf::sleep(sf::seconds(1));

    engine.ChangeScene("main_scene");

    engine.Run();


    return 0;
}
