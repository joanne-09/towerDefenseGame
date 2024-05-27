#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_TANKBULLET_HPP
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_TANKBULLET_HPP
#include "EBullet.hpp"

class Enemy;
class Turret;
namespace Engine {
    struct Point;
}  // namespace Engine

class TankBullet : public EBullet {
protected:
    ;
public:
    explicit TankBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Enemy* parent);
    void OnExplode(Turret* enemy) override;
};

#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_TANKBULLET_HPP
