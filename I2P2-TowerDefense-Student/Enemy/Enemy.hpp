#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <allegro5/base.h>
#include <list>
#include <vector>
#include <string>

#include "Engine/Point.hpp"
#include "Engine/Sprite.hpp"

class Bullet;
class PlayScene;
class Turret;

class Enemy : public Engine::Sprite {
protected:
 	std::vector<Engine::Point> path;
	float speed;
	float hp;
	int money;
	PlayScene* getPlayScene();
    virtual void CreateBullet() = 0;
	virtual void OnExplode();
public:
    float reachEndTime;
	std::list<Turret*> lockedTurrets;
	std::list<Bullet*> lockedBullets;
	Enemy(std::string img, float x, float y, float radius, float speed, float hp, int money);
 	void Hit(float damage);
     void SlowDown(float hurt);
     void UpdatePath(const std::vector<std::vector<int>>& mapDistance);
	void Update(float deltaTime) override;
	void Draw() const override;
    virtual void FindTarget(float deltaTime);
};
#endif // ENEMY_HPP
