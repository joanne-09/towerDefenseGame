#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_ENEMY4_HPP
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_ENEMY4_HPP
#include "Enemy.hpp"

class Enemy4 : public Enemy {
public:
    Enemy4(int x, int y);
    void CreateBullet() override;
};

#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_ENEMY4_HPP
