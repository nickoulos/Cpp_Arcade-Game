#include "powerup.h"
#include "graphics.h"

void PowerUp::update()
{
	pos_y += speed * graphics::getDeltaTime();

	if (pos_y > WINDOW_HEIGHT)
	{
		active = false;
	}

}

void PowerUp::draw()
{
	br.outline_opacity = 0.0f;

	br.fill_opacity = 1.0f;
	br.texture = std::string(ASSET_PATH) + "singleFire.png";
	graphics::drawRect(pos_x, pos_y, size, size, br);
	graphics::setOrientation(0.f);

}

void PowerUp::init()
{
	speed = 0.3f;
	pos_x = CANVAS_WIDTH * rand0to1();
	pos_y = 0;
	size = 80;
	br.outline_opacity = 0.0f;
}

PowerUp::PowerUp(const Game& mygame)
	: GameObject(mygame)
{
	init();
}

PowerUp::~PowerUp()
{
}

Disk PowerUp::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = size * 0.45f;
	return disk;
}


