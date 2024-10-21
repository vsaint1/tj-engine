#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "Component.h"
#include "utils/AssetsManager.h"

struct CSpriteData {
    sf::Vector2i size;
    sf::Vector2f origin;
    sf::Vector2f position;
    sf::Vector2f scale;
    std::string spriteName;
    std::string spritePath;
    sf::Sprite sprite;

    CSpriteData(const std::string& _name, const std::string& _path,
        const sf::Vector2f& _starterPosition = sf::Vector2f(0.f, 0.f),
        const sf::Vector2f& _origin = sf::Vector2f(0.f, 0.f), const sf::Vector2f& _scale = sf::Vector2f(1.f, 1.f))
        : spriteName(_name), spritePath(_path), position(_starterPosition), origin(_origin), scale(_scale) {


        this->assetsManager.LoadTexture(_name, _path);
    }

    tj::AssetsManager& assetsManager = tj::AssetsManager::GetInstance();
};

class SpriteComponent : public tj::IComponent {
public:
    SpriteComponent(CSpriteData _spritedata) : spriteData(_spritedata) {}

    void Start() override {
        TJ_LOG_INFO("Starting SpriteComponent");

        auto& texture = this->spriteData.assetsManager.GetTexture(this->spriteData.spriteName);

        this->spriteData.size = sf::Vector2i(texture.getSize());
        this->spriteData.sprite.setTexture(texture);
        this->spriteData.sprite.setOrigin(this->spriteData.sprite.getLocalBounds().width / 2.f,
            this->spriteData.sprite.getLocalBounds().height / 2.f);
        this->spriteData.sprite.setPosition(spriteData.position);
    }

    void Update(float _deltaTime) override {
        TJ_LOG_INFO("Updating SpriteComponent");
    }

    void Draw(sf::RenderTarget& _target) override {

        TJ_LOG_INFO("Drawing SpriteComponent %s", this->spriteData.spriteName.c_str());
        _target.draw(this->spriteData.sprite);
    }

    void SetPosition(sf::Vector2f _position) {
        this->spriteData.sprite.setPosition(_position);
    }

private:
    CSpriteData spriteData;
};

#endif // SPRITECOMPONENT_H
