#include <cmath>
#include "Enemy4.hpp"
#include "Engine/AudioHelper.hpp"

Enemy4::Enemy4(int x, int y) : Enemy("play/enemy-4.png", x, y, 20, 60, 20, 30) {
    // TODO: [CUSTOM-TOOL] You can imitate the 2 files: 'SoldierEnemy.hpp', 'SoldierEnemy.cpp' to create a new enemy.
}

void Enemy4::CreateBullet() {}