#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_TURRET4_HPP
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_TURRET4_HPP
#include "Turret.hpp"

class Turret4: public Turret {
public:
    static const int Price;

    Turret4(float x, float y);

    void CreateBullet() override;
};
#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_TURRET4_HPP
