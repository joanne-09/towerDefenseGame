#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_FREETURRET_HPP
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_FREETURRET_HPP
#include "Turret.hpp"

class FreeTurret: public Turret {
public:
    static const int Price;
    int count = 0;

    FreeTurret(float x, float y);
    void FindTarget(float deltaTime) override;
    void CreateBullet() override;
};

#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_FREETURRET_HPP
