#pragma once
#include "GameObject.h"
#include "config.h"
#include "graphics.h"



class Fire : public GameObject, public Collidable
{
	float speed;
	float pos_x, pos_y ;
	float size;

	float height = 1.0f;
	float rotation = -90.0f;
	graphics::Brush brush;
	bool active = true;

public:
	Fire(const class Game& mygame);
	~Fire();

	void update() override;
	void draw() override;
	void init() override;

	void setPosY(float posY) { pos_y = posY; }
	void setPosX(float posX) { pos_x = posX; }

	float getSpeed() { return speed; }
	void setSpeed(float Speed) { speed = Speed; }

	bool isActive() { return active; }

	Disk getCollisionHull() const override;
};

