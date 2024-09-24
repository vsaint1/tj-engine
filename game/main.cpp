#include "core/engine.h"
#include "ecs/animation.hpp"
#include "input/mobile/joystick.h"
#include "ui/health_bar.hpp"
#include "utils/assets_mannager.hpp"

class Enemy : public GameObject {
  public:
    Enemy(sf::RenderWindow &_window, const sf::Texture &_texture, int _initialFrame, int _spriteWidth = 64, int _spriteHeight = 64)
        : GameObject(_window), texture(_texture), spriteWidth(_spriteWidth), spriteHeight(_spriteHeight), healthBar(100.0f, 120.f, 10.0f, {0.0f, 0.0f}) {

        sprite.setTexture(texture);
        sprite.setScale(6.0f, 6.0f);
        setSpriteFrame(_initialFrame);
    }

    void addAnimation(const Animation &animation) { animations[animation.getAnimationName()] = animation; }

    void playAnimation(const std::string &name) {
        printf("Playing animation: %s\n", name.c_str());

        if (animations.find(name) != animations.end()) {
            if (currentAnimation != name) {
                currentAnimation = name;
                animations[currentAnimation].resetAnimationFrame();
                animations[currentAnimation].setTimeElapsed(0.0f);
                printf("Switched to animation: %s with frame_count: %d\n", name.c_str(), animations[currentAnimation].getTotalFrames());
            }
        }
    }

    void update(float _deltaTime) override {

        if (!currentAnimation.empty()) {
            animations[currentAnimation].update(_deltaTime);
            animations[currentAnimation].setSpriteFrame(sprite, texture, spriteWidth, spriteHeight);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y) || sf::Touch::isDown(0)) {
            health -= 10.0f;

            if (health < 0.0f) {
                health = 0.0f;
                this->playAnimation("DYING");
            }
        }

        healthBar.update(health);

        if(health <= 0.0f && animations[currentAnimation].isLastFrame("DYING")) {
            // TODO: "destory game_object for example"
        }

    }

    void draw(sf::RenderStates _states = sf::RenderStates::Default) override {
        target->draw(sprite, _states);

        float spriteMidX = sprite.getGlobalBounds().left + sprite.getGlobalBounds().width / 2.0f;
        float healthBarX = spriteMidX - healthBar.getWidth() / 2.0f;
        float healthBarY = sprite.getGlobalBounds().top;
        glm::vec2 healthBarPosition = {healthBarX, healthBarY};
        healthBar.setScreenPosition(healthBarPosition);

        healthBar.draw(*target);
    }

    void setPosition(float x, float y) { sprite.setPosition(x, y); }

  private:
    void setSpriteFrame(int _frame) {
        int cols = texture.getSize().x / spriteWidth;
        int row = _frame / cols;
        int col = _frame % cols;
        sprite.setTextureRect(sf::IntRect(col * spriteWidth, row * spriteHeight, spriteWidth, spriteHeight));
    }

    int spriteWidth, spriteHeight;
    sf::Sprite sprite;
    const sf::Texture &texture;
    tj::HealthBar healthBar;
    float health = 100.0f;
    std::unordered_map<std::string, Animation> animations;
    std::string currentAnimation;
};

int main() {

    auto &windowManager = tj::Engine::getInstance();
    auto &window = windowManager.getWindow();
    windowManager.createWindow("Game Window", sf::VideoMode(800, 600));

#if __ANDROID__
    __android_log_print(ANDROID_LOG_INFO, "TJLog", "Failed to create window");
#endif

    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile(tj::AssetsManager::getAssetsFolder() + "skeleton_sprite.png")) {
        return -1;
    }

#if __ANDROID__
    __android_log_print(ANDROID_LOG_INFO, "TJLog", "Loaded succesifully");
#endif

    CAnimationData idleAnimation("IDLE", 4, 1.0f, 0);

    Animation animIdle(idleAnimation);
    Animation animAttack({"ATTACK", 5, 0.5f, 5});
    Animation animDeath({"DYING", 12, 0.2f, 14});

    std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(window, enemyTexture, 2);
    enemy->addAnimation(animIdle);
    enemy->addAnimation(animAttack);
    enemy->addAnimation(animDeath);
    enemy->setPosition(100, 100);
    enemy->playAnimation("IDLE");
    windowManager.registerGameObject(enemy);

    windowManager.run();

    return 0;
}
