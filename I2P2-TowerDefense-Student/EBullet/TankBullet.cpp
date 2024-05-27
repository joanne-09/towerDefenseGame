#include <allegro5/base.h>
#include <random>
#include <string>

#include "UI/Animation/DirtyEffect.hpp"
#include "Enemy/Enemy.hpp"
#include "Turret/Turret.hpp"
#include "TankBullet.hpp"
#include "Engine/Group.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/Collider.hpp"

class Turret;

TankBullet::TankBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Enemy* parent) :
        EBullet("play/bullet-8.png", 500, 0.5, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
    // TODO: [CUSTOM-TOOL] You can imitate the 2 files: 'FireBullet.hpp', 'FireBullet.cpp' to create a new bullet.
}

void TankBullet::OnExplode(Turret* enemy) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(2, 5);
    getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-1.png", dist(rng), enemy->Position.x, enemy->Position.y));
}