#pragma once
#include "GameObject.h"
#include "config.h"

class Player : public GameObject, public Collidable
{
	float speed = 10.0f;
	float pos_x = CANVAS_WIDTH/2, pos_y=CANVAS_HEIGHT/2;
	float gunfire_pos_x = CANVAS_WIDTH / 2  + 1.0f, gunfire_pos_y = CANVAS_HEIGHT / 2;
	float height = 1.0f;
	float life = 1.0f;

public:
	Player(const class Game& mygame);
	void update() override;
	void draw() override;
	void init() override;
	float getPosY() { return pos_y; }
	float getPosX() { return pos_x; }

	Disk getCollisionHull() const override;
	float getRemainingLife() const { return life; }
	void drainLife(float amount) { life = std::max<float>(0.0f, life - amount); }
};