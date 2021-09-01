#pragma once
#include "GameObject.h"
#include "graphics.h"
#include "config.h"

class Enemy : public GameObject, public Collidable
{
	float pos_x, pos_y;
	float speed;
	float size;
	float rotation;
	graphics::Brush brush;
	bool active = true;
public:
	void update() override;
	void draw() override;
	void init() override;

	float getPosY() { return pos_y; }
	float getPosX() { return pos_x; }

	float getSpeed() { return speed; }
	void setSpeed(float Speed) { speed = Speed; }

	bool isActive() { return active; }
	Enemy(const class Game& mygame);
	~Enemy();

	Disk getCollisionHull() const override;
};