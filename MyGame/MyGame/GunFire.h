#pragma once
#include "GameObject.h"
#include "config.h"
#include "graphics.h"



class GunFire : public GameObject, public Collidable
{
	float speed;
	float pos_x = CANVAS_WIDTH / 2 , pos_y = CANVAS_HEIGHT / 2 + 50.0f;


	float height = 1.0f;
	float size;
	float rotation = -90.0f;
	float score = 0.0f;
	graphics::Brush brush;
	bool active = true;

public:
	GunFire(const class Game& mygame);
	~GunFire();
	void update() override;
	void draw() override;
	void init() override;
	void setPosY(float posY) { pos_y = posY; }
	void setPosX(float posX) { pos_x = posX; }

	Disk getCollisionHull() const override;
};

