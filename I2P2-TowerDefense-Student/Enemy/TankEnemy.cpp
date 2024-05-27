#include <allegro5/base.h>
#include <random>
#include <string>

#include "Engine/Point.hpp"
#include "Engine/Group.hpp"
#include "TankEnemy.hpp"
#include "EBullet/EBullet.hpp"
#include "EBullet/TankBullet.hpp"
#include "Engine/AudioHelper.hpp"
#include "Scene/PlayScene.hpp"

TankEnemy::TankEnemy(int x, int y) : Enemy("play/enemy-3.png", x, y, 20, 20, 100, 50),
head("play/enemy-3-head.png", x, y), targetRotation(0) {
}
void TankEnemy::Draw() const {
	Enemy::Draw();
	head.Draw();
}

void TankEnemy::FindTarget(float deltaTime) {
    reload -= deltaTime;
    if (reload <= 0) {
        // shoot.
        reload = 2;
        CreateBullet();
    }
}

void TankEnemy::Update(float deltaTime) {
	Enemy::Update(deltaTime);
    FindTarget(deltaTime);
	head.Position = Position;
	// Choose arbitrary one.
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_real_distribution<> dist(0.0f, 4.0f);
	float rnd = dist(rng);
	if (rnd < deltaTime) {
		// Head arbitrary rotation.
		std::uniform_real_distribution<> distRadian(-ALLEGRO_PI, ALLEGRO_PI);
		targetRotation = distRadian(rng);
	}
	head.Rotation = (head.Rotation + deltaTime * targetRotation) / (1 + deltaTime);
}

void TankEnemy::CreateBullet() {
    Engine::Point diff = Engine::Point(cos(head.Rotation), sin(head.Rotation));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();
    // Change bullet position to the front of the gun barrel.
    getPlayScene()->EBulletGroup->AddNewObject(new TankBullet(Position + normalized * 30, diff, rotation, this));
    AudioHelper::PlayAudio("gun.wav");
}
