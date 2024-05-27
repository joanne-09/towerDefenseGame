#ifndef TURRET_HPP
#define TURRET_HPP
#include <allegro5/base.h>
#include <list>
#include <string>

#include "Engine/Sprite.hpp"

class Enemy;
class PlayScene;

class Turret: public Engine::Sprite {
protected:
    float hp;
    int price;
    float coolDown;
    float reload = 0;
    float rotateRadian = 2 * ALLEGRO_PI;
    Sprite imgBase;
    std::list<Turret*>::iterator lockedTurretIterator;
    PlayScene* getPlayScene();
    // Reference: Design Patterns - Factory Method.
    virtual void CreateBullet() = 0;
    virtual void OnExplode();
public:
    float turretRadius;
    bool Enabled = true;
    bool Preview = false;
    int tilePosX, tilePoxY;
    Enemy* Target = nullptr;
    Turret* TurretTarget = nullptr;
    Turret(std::string imgBase, std::string imgTurret, float x, float y, float radius, float itsradius, int price, float coolDown, float hp);
    virtual void FindTarget(float deltaTime);
    void Update(float deltaTime) override;
    void Draw() const override;
	int GetPrice() const;
    void Hit(float damage);
};
#endif // TURRET_HPP
