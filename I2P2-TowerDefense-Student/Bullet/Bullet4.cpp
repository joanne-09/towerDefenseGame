#include <allegro5/base.h>
#include <random>
#include <string>

#include "UI/Animation/DirtyEffect.hpp"
#include "Enemy/Enemy.hpp"
#include "Bullet4.hpp"
#include "Engine/Group.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/Collider.hpp"

class Turret;

Bullet4::Bullet4(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent) :
        Bullet("play/bullet-4.png", 200, 2, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
    // TODO: [CUSTOM-TOOL] You can imitate the 2 files: 'FireBullet.hpp', 'FireBullet.cpp' to create a new bullet.
}

void Bullet4::FindTarget(float deltaTime) {
    PlayScene* scene = getPlayScene();
    // Can be improved by Spatial Hash, Quad Tree, ...
    // However simply loop through all enemies is enough for this program.
    for (auto& it : scene->EnemyGroup->GetObjects()) {
        Enemy* enemy = dynamic_cast<Enemy*>(it);
        if (!enemy->Visible)
            continue;
        if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, enemy->Position, enemy->CollisionRadius)) {
            OnExplode(enemy);
            enemy->Hit(damage);
            enemy->SlowDown(10);
            getPlayScene()->BulletGroup->RemoveObject(objectIterator);
            return;
        }
    }

    // Check if out of boundary.
    if (!Engine::Collider::IsRectOverlap(Position - Size / 2, Position + Size / 2, Engine::Point(0, 0), PlayScene::GetClientSize()))
        getPlayScene()->BulletGroup->RemoveObject(objectIterator);
}

void Bullet4::Update(float deltaTime) {
    if (!Target) {
        float minDistance = INFINITY;
        Enemy* enemy = nullptr;
        for (auto& it : getPlayScene()->EnemyGroup->GetObjects()) {
            Enemy* e = dynamic_cast<Enemy*>(it);
            float distance = (e->Position - Position).Magnitude();
            if (distance < minDistance) {
                minDistance = distance;
                enemy = e;
            }
        }
        if (!enemy) {
            Bullet::Update(deltaTime);
            return;
        }
        Target = enemy;
        Target->lockedBullets.push_back(this);
        lockedBulletIterator = std::prev(Target->lockedBullets.end());
    }
    Engine::Point originVelocity = Velocity.Normalize();
    Engine::Point targetVelocity = (Target->Position - Position).Normalize();
    float maxRotateRadian = rotateRadian * deltaTime;
    float cosTheta = originVelocity.Dot(targetVelocity);
    // Might have floating-point precision error.
    if (cosTheta > 1) cosTheta = 1;
    else if (cosTheta < -1) cosTheta = -1;
    float radian = acos(cosTheta);
    if (abs(radian) <= maxRotateRadian)
        Velocity = targetVelocity;
    else
        Velocity = ((abs(radian) - maxRotateRadian) * originVelocity + maxRotateRadian * targetVelocity) / radian;
    Velocity = speed * Velocity.Normalize();
    Rotation = atan2(Velocity.y, Velocity.x) + ALLEGRO_PI / 2;

    Sprite::Update(deltaTime);
    FindTarget(deltaTime);
}

void Bullet4::OnExplode(Enemy* enemy) {
    Target->lockedBullets.erase(lockedBulletIterator);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(4, 10);
    getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-3.png", dist(rng), enemy->Position.x, enemy->Position.y));
}

