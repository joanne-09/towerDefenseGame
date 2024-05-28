#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_BULLET4_HPP
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_BULLET4_HPP
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
    struct Point;
}  // namespace Engine

class Bullet4 : public Bullet {
protected:
    const float rotateRadian = 2 * ALLEGRO_PI;
    std::list<Bullet*>::iterator lockedBulletIterator;
public:
    explicit Bullet4(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
    void Update(float deltaTime) override;
    void OnExplode(Enemy* enemy) override;
    void FindTarget(float deltaTime) override;
};

#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_BULLET4_HPP
