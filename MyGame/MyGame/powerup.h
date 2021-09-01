#pragma once
#include "GameObject.h"
#include "config.h"
#include "graphics.h"

class PowerUp : public GameObject, public Collidable
{
	float pos_x, pos_y;
	float speed;
	float size;
	graphics::Brush br;
	bool active = true;
public:
	void update() override;
	void draw() override;
	void init() override;

	bool isActive() { return active; }
	PowerUp(const class Game& mygame);
	~PowerUp();

	Disk getCollisionHull() const override;
};