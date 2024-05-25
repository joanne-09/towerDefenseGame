#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_FREEBULLET_HPP
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_FREEBULLET_HPP
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
    struct Point;
}  // namespace Engine

class FreeBullet : public Bullet {
protected:
    ;
public:
    explicit FreeBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
    void OnExplode(Enemy* enemy) override;
    void FindTarget(float deltaTime) override;
};

#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_FREEBULLET_HPP
