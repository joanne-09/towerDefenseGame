#ifndef TANKENEMY_HPP
#define TANKENEMY_HPP
#include "Enemy.hpp"
#include "Engine/Sprite.hpp"

class TankEnemy : public Enemy {
private:
	Sprite head;
	float targetRotation;
    float reload = 0;
public:
	TankEnemy(int x, int y);
	void Draw() const override;
	void Update(float deltaTime) override;
    void CreateBullet() override;
    void FindTarget(float deltaTime) override;
};
#endif // TANKENEMY_HPP
