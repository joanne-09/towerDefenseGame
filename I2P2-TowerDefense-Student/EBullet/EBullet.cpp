#include "EBullet.hpp"
#include "Engine/Collider.hpp"
#include "Enemy/Enemy.hpp"
#include "Turret/Turret.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IObject.hpp"
#include "Engine/IScene.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/Sprite.hpp"

PlayScene* EBullet::getPlayScene() {
    return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
void EBullet::OnExplode(Turret* enemy) {
}
EBullet::EBullet(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Enemy* parent) :
        Sprite(img, position.x, position.y), speed(speed), damage(damage), parent(parent) {
    Velocity = forwardDirection.Normalize() * speed;
    Rotation = rotation;
    CollisionRadius = 4;
}

void EBullet::FindTarget(float deltaTime) {
    PlayScene* scene = getPlayScene();
    // Can be improved by Spatial Hash, Quad Tree, ...
    // However simply loop through all enemies is enough for this program.
    for (auto& it : scene->TowerGroup->GetObjects()) {
        Turret* turret = dynamic_cast<Turret*>(it);
        if (!turret->Visible)
            continue;
        if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, turret->Position, turret->turretRadius)) {
            OnExplode(turret);
            turret->Hit(damage);
            getPlayScene()->EBulletGroup->RemoveObject(objectIterator);
            return;
        }
    }

    // Check if out of boundary.
    if (!Engine::Collider::IsRectOverlap(Position - Size / 2, Position + Size / 2, Engine::Point(0, 0), PlayScene::GetClientSize()))
        getPlayScene()->EBulletGroup->RemoveObject(objectIterator);
}
void EBullet::Update(float deltaTime) {
    Sprite::Update(deltaTime);
    FindTarget(deltaTime);
}
