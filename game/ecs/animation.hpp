#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "../pch.hpp"

class Animation {

    // TODO: create CAnimationData struct

    std::string name;
    int frameCount;
    float duration;
    float time;
    int currentFrame;
    int startFrame;

  public:
    Animation() : name(""), frameCount(0), duration(0.0f), currentFrame(0), time(0.0f), startFrame(0) {}

    Animation(const std::string &_name, int _frameCount, float _durationMs, int _startFrame = 0) : name(_name), frameCount(_frameCount), duration(_durationMs), startFrame(_startFrame) {

        // assert(!_name.empty(), "Animation name cannot be empty");

        currentFrame = _startFrame;
        time = 0.0f;
    }

    void update(float deltaTime) {
        time += deltaTime;
        if (time >= duration) {
            time = 0.0f;
            currentFrame = (currentFrame + 1) % frameCount;
        }
    }

    void setSpriteFrame(sf::Sprite &_sprite, const sf::Texture &_texture, int _spriteWidth, int _spriteHeight) {
        int cols = _texture.getSize().x / _spriteWidth;
        int row = (currentFrame + startFrame) / cols;
        int col = (currentFrame + startFrame) % cols;

        _sprite.setTextureRect(sf::IntRect(col * _spriteWidth, row * _spriteHeight, _spriteWidth, _spriteHeight));
    }

    const std::string &getAnimationName() const { return name; }

    void resetAnimationFrame() { currentFrame = 0; }

  private:
};

#endif // ANIMATION_HPP
