#include "GunFire.h"
#include "graphics.h"
#include "game.h"

#include "config.h"
#include "util.h"

void GunFire::update()
{
	if (pos_x < -size)
	{
		active = false;
	}

}

void GunFire::draw()
{
	graphics::setOrientation(rotation);
	brush.texture = std::string(ASSET_PATH) + "Gun.png";
	brush.fill_opacity = 1.0f;
	brush.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, 100, 100, brush);
	graphics::resetPose();

	if (game.getDebugMode())
	{
		graphics::Brush br;
		br.outline_opacity = 1.0f;
		br.texture = "";
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 0.3f;
		br.fill_color[2] = 0.3f;
		br.fill_opacity = 0.3f;
		br.gradient = false;

		Disk hull = getCollisionHull();
		graphics::drawDisk(hull.cx, hull.cy, hull.radius, br);

	}
}

void GunFire::init()
{
}


Disk GunFire::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = 55.0f;
	return disk;
}

GunFire::GunFire(const Game& mygame)
	: GameObject(mygame)
{
	init();
}

GunFire::~GunFire()
{
}













