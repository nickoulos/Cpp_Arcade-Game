#include "meteor.h"
#include "graphics.h"

void Meteor::update()
{
	pos_x -= speed * graphics::getDeltaTime();
	if (pos_x < -size)
	{
		active = false;
	}

}

void Meteor::draw()
{
	br.outline_opacity = 0.0f;

	br.fill_opacity = 1.0f;
	br.texture = std::string(ASSET_PATH) + "meteor4.png";
	graphics::drawRect(pos_x, pos_y, size, size, br);
	graphics::setOrientation(0.f);

}

void Meteor::init()
{
	speed = 0.3f;
	pos_x = CANVAS_WIDTH + 2.0f * size;
	pos_y = CANVAS_HEIGHT * rand0to1();
	size = 50 + 100 * rand0to1();
	br.outline_opacity = 0.0f;
}

Meteor::Meteor(const Game& mygame)
	: GameObject(mygame)
{
	init();
}

Meteor::~Meteor()
{
}

Disk Meteor::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = size * 0.45f;
	return disk;
}


