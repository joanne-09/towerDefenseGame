#include <allegro5/base.h>
#include <cmath>
#include <random>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Bullet/FreeBullet.hpp"
#include "Engine/Group.hpp"
#include "Enemy/Enemy.hpp"
#include "FreeTurret.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

const int FreeTurret::Price = 0;
FreeTurret::FreeTurret(float x, float y) :
// TODO: [CUSTOM-TOOL] You can imitate the 2 files: 'MachineGunTurret.hpp', 'MachineGunTurret.cpp' to create a new turret.
        Turret("play/tower-base.png", "play/turret-5.png", x, y, 150, Price, 0.5, 20) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}
void FreeTurret::CreateBullet() {
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();
    // Change bullet position to the front of the gun barrel.
    FreeBullet* freeBullet = new FreeBullet(Position + normalized * 36, diff, rotation, this);
    getPlayScene()->BulletGroup->AddNewObject(freeBullet);
    AudioHelper::PlayAudio("gun.wav");
}

void FreeTurret::FindTarget(float deltaTime) {
    PlayScene* scene = getPlayScene();
    imgBase.Position = Position;
    imgBase.Tint = Tint;
    int randint = rand() % 5;

    if (!Enabled)
        return;
    if (Target) {
        Engine::Point diff = Target->Position - Position;
        if (diff.Magnitude() > CollisionRadius) {
            Target->lockedTurrets.erase(lockedTurretIterator);
            Target = nullptr;
            lockedTurretIterator = std::list<Turret*>::iterator();
        }
    }
    if(TurretTarget){
        Engine::Point diff = TurretTarget->Position - Position;
        if (diff.Magnitude() > CollisionRadius) {
            TurretTarget->lockedTurrets.erase(lockedTurretIterator);
            TurretTarget = nullptr;
            lockedTurretIterator = std::list<Turret*>::iterator();
        }
    }

    /// if randint == 0, find enemy target else attack turret
    if(count % 10 == 0){
        TurretTarget = nullptr;
        if (!Target) {
            // Lock first seen target.
            // Can be improved by Spatial Hash, Quad Tree, ...
            // However simply loop through all enemies is enough for this program.
            for (auto& it : scene->EnemyGroup->GetObjects()) {
                Engine::Point diff = it->Position - Position;
                if (diff.Magnitude() <= CollisionRadius) {
                    Target = dynamic_cast<Enemy*>(it);
                    Target->lockedTurrets.push_back(this);
                    lockedTurretIterator = std::prev(Target->lockedTurrets.end());
                    break;
                }
            }
        }
    }else if(randint == 0 && count % 10 == 0){
        Target = nullptr;
        if (!TurretTarget) {
            // Lock first seen target.
            // Can be improved by Spatial Hash, Quad Tree, ...
            // However simply loop through all enemies is enough for this program.
            for (auto& it : scene->TowerGroup->GetObjects()) {
                Engine::Point diff = it->Position - Position;
                if (diff.Magnitude() <= CollisionRadius) {
                    TurretTarget = dynamic_cast<Turret*>(it);
                    TurretTarget->lockedTurrets.push_back(this);
                    lockedTurretIterator = std::prev(TurretTarget->lockedTurrets.end());
                    break;
                }
            }
        }
    }

    if (Target || TurretTarget) {
        Engine::Point TargetPos = (Target == nullptr ? TurretTarget->Position : Target->Position);
        Engine::Point originRotation = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
        Engine::Point targetRotation = (TargetPos - Position).Normalize();
        float maxRotateRadian = rotateRadian * deltaTime;
        float cosTheta = originRotation.Dot(targetRotation);
        // Might have floating-point precision error.
        if (cosTheta > 1) cosTheta = 1;
        else if (cosTheta < -1) cosTheta = -1;
        float radian = acos(cosTheta);
        Engine::Point rotation;
        if (abs(radian) <= maxRotateRadian)
            rotation = targetRotation;
        else
            rotation = ((abs(radian) - maxRotateRadian) * originRotation + maxRotateRadian * targetRotation) / radian;
        // Add 90 degrees (PI/2 radian), since we assume the image is oriented upward.
        Rotation = atan2(rotation.y, rotation.x) + ALLEGRO_PI / 2;
        // Shoot reload.
        reload -= deltaTime;
        if (reload <= 0) {
            // shoot.
            reload = coolDown;
            CreateBullet();
        }
    }

    count++;
    if(count == 30) count = 0;
}
