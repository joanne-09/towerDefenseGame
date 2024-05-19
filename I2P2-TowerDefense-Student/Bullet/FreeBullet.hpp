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
    const float rotateRadian = 2 * ALLEGRO_PI;
    std::list<Bullet*>::iterator lockedBulletIterator;
public:
    explicit FreeBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
    void Update(float deltaTime) override;
    void OnExplode(Enemy* enemy) override;
};

#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_FREEBULLET_HPP
