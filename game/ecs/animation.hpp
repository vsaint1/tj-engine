#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "../pch.hpp"

struct CAnimationData {
    std::string name;
    int frameCount;
    float duration;
    float timeElapsed;
    int startFrame;

    CAnimationData() : name(""), frameCount(0), duration(0.0f), timeElapsed(0.0f), startFrame(0) {}

    CAnimationData(const std::string &_name, int _frameCount, float _durationMs, int _startFrame = 0)
        : name(_name), frameCount(_frameCount), duration(_durationMs), timeElapsed(0.0f), startFrame(_startFrame) {}
};

class Animation {
    CAnimationData animationData;
    int currentFrame;

  public:
    Animation() : animationData(), currentFrame(0) {}

    Animation(const CAnimationData &data) : animationData(data), currentFrame(data.startFrame) {
        // assert(!data.name.empty(), "Animation name cannot be empty");
    }

    void update(float _deltaTime) {
        animationData.timeElapsed += _deltaTime;
        if (animationData.timeElapsed >= animationData.duration) {
            animationData.timeElapsed = 0.0f;
            currentFrame = (currentFrame + 1) % animationData.frameCount;
        }
    }

    void setSpriteFrame(sf::Sprite &_sprite, const sf::Texture &_texture, int _spriteWidth, int _spriteHeight) {
        int cols = _texture.getSize().x / _spriteWidth;
        int row = (currentFrame + animationData.startFrame) / cols;
        int col = (currentFrame + animationData.startFrame) % cols;

        _sprite.setTextureRect(sf::IntRect(col * _spriteWidth, row * _spriteHeight, _spriteWidth, _spriteHeight));
    }

    const std::string &getAnimationName() const { return animationData.name; }

    void resetAnimationFrame() { currentFrame = animationData.startFrame; }

    bool isLastFrame() const { return this->getTotalFrames() == 1; }
    bool isLastFrame(const std::string &_animationName) const { return this->animationData.name.compare(_animationName) == 0 && currentFrame == this->getTotalFrames() - 1; }

    void setTimeElapsed(float _timeElapsed) { animationData.timeElapsed = _timeElapsed; }

    int getTotalFrames() const { return animationData.frameCount; }

    // TODO: fix those functions
    bool animationHasFinished() const { return isLastFrame() && animationData.timeElapsed >= animationData.duration; }

    bool animationHasFinished(const std::string &_animationName) const { return isLastFrame(_animationName) && animationData.timeElapsed >= animationData.duration; }
};

#endif // ANIMATION_HPP
