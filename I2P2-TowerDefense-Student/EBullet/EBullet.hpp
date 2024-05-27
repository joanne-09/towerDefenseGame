#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_EBULLET_HPP
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_EBULLET_HPP
#include <string>

#include "Engine/Sprite.hpp"

class Enemy;
class PlayScene;
class Turret;
namespace Engine {
    struct Point;
}  // namespace Engine

class EBullet : public Engine::Sprite {
protected:
    float speed;
    float damage;
    Enemy* parent;
    PlayScene* getPlayScene();
    virtual void OnExplode(Turret* enemy);
public:
    Enemy* Target = nullptr;
    Turret* TurretTarget = nullptr;
    explicit EBullet(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Enemy* parent);
    virtual void FindTarget(float deltaTime);
    void Update(float deltaTime) override;
};

#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_EBULLET_HPP
