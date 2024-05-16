#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Bullet/Bullet4.hpp"
#include "Engine/Group.hpp"
#include "Turret4.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

const int Turret4::Price = 500;
Turret4::Turret4(float x, float y) :
// TODO: [CUSTOM-TOOL] You can imitate the 2 files: 'MachineGunTurret.hpp', 'MachineGunTurret.cpp' to create a new turret.
        Turret("play/tower-base.png", "play/turret-4.png", x, y, 500, Price, 0.3) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}
void Turret4::CreateBullet() {
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();
    Engine::Point normal = Engine::Point(-normalized.y, normalized.x);
    // Change bullet position to the front of the gun barrel.
    getPlayScene()->BulletGroup->AddNewObject(new Bullet4(Position + normalized * 36 - normal * 5, diff, rotation, this));
    getPlayScene()->BulletGroup->AddNewObject(new Bullet4(Position + normalized * 36 + normal * 5, diff, rotation, this));
    AudioHelper::PlayAudio("missile.wav");
}
