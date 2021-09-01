#pragma once
#include "GameObject.h"
#include "config.h"
#include "graphics.h"

class Meteor : public GameObject, public Collidable
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


	float getPosY() { return pos_y; }
	float getPosX() { return pos_x; }
	float getSize() { return size; }

	float getSpeed() { return speed; }
	void setSpeed(float Speed) { speed = Speed; }
	

	bool isActive() { return active; }
	Meteor(const class Game& mygame);
	~Meteor();

	Disk getCollisionHull() const override;
};