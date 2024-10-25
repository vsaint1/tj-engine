#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "Component.h"
#include "utils/AssetsManager.h"

struct CSpriteData {

    sf::Vector2f origin;
    sf::Vector2f scale;
    sf::Vector2f startPosition;
    std::string spriteName;
    std::string spritePath;
    sf::Sprite sprite;
    sf::Vector2i spriteSize;
    sf::Vector2i spriteCoords;

    CSpriteData(const std::string& _name, const std::string& _path,
        const sf::Vector2f& _startPosition = sf::Vector2f(0.f, 0.f),
        const sf::Vector2i& _spriteSize = sf::Vector2i(0, 0), const sf::Vector2i& _spriteCoords = sf::Vector2i(0, 0),
        const sf::Vector2f& _origin = sf::Vector2f(0.f, 0.f), const sf::Vector2f& _scale = sf::Vector2f(1.f, 1.f))
        : spriteName(_name), spritePath(_path), startPosition(_startPosition), origin(_origin), scale(_scale),
          spriteSize(_spriteSize), spriteCoords(_spriteCoords) {

        this->assetsManager.LoadTexture(_name, _path);
    }

    tj::AssetsManager& assetsManager = tj::AssetsManager::GetInstance();
};

class SpriteComponent : public tj::IComponent {
public:
    SpriteComponent(CSpriteData _spritedata) : spriteData(_spritedata) {

        
        auto& texture = this->spriteData.assetsManager.GetTexture(this->spriteData.spriteName);

        if (this->spriteData.spriteSize.x == 0 || this->spriteData.spriteSize.y == 0) {
            this->spriteData.spriteSize = sf::Vector2i(texture.getSize());
        }

        this->spriteData.sprite.setTexture(texture);
        this->spriteData.sprite.setTextureRect(
            sf::IntRect(this->spriteData.spriteCoords.x * this->spriteData.spriteSize.x,
                this->spriteData.spriteCoords.y * this->spriteData.spriteSize.y, this->spriteData.spriteSize.x,
                this->spriteData.spriteSize.y));

        this->spriteData.sprite.setOrigin(this->spriteData.spriteSize.x / 2.f, this->spriteData.spriteSize.y / 2.f);
        this->spriteData.sprite.setPosition(spriteData.startPosition);
        this->spriteData.sprite.setScale(spriteData.scale);
    }


    sf::Vector2f GetPosition() const {
        return this->spriteData.sprite.getPosition();
    }

    sf::Vector2f GetScale() const {
        return this->spriteData.sprite.getScale();
    }

    sf::Vector2f GetOrigin() const {
        return this->spriteData.sprite.getOrigin();
    }

    float GetRotation() const {
        return this->spriteData.sprite.getRotation();
    }

    void SetPosition(sf::Vector2f _position) {
        this->spriteData.sprite.setPosition(_position);
    }

    void SetScale(sf::Vector2f _scale) {
        this->spriteData.sprite.setScale(_scale);
    }

    void SetOrigin(sf::Vector2f _origin) {
        this->spriteData.sprite.setOrigin(_origin);
    }

    void SetRotation(float _angle) {
        this->spriteData.sprite.setRotation(_angle);
    }

    void Draw(sf::RenderTarget& _target) override {
        _target.draw(this->spriteData.sprite);
    }

private:
    CSpriteData spriteData;
};

#endif // SPRITECOMPONENT_H
