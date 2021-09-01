#pragma once
#include "GameObject.h"
#include "config.h"
#include "graphics.h"

class Explosion : public GameObject
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
	void setPosY(float posY) { pos_y = posY; }
	void setPosX(float posX) { pos_x = posX; }

	bool isActive() { return active; }
	Explosion(const class Game& mygame);
	~Explosion();
};