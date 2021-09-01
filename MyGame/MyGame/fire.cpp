#include "Fire.h"
#include "graphics.h"
#include "game.h"

#include "config.h"
#include "util.h"

void Fire::update()
{
	pos_x += speed * graphics::getDeltaTime();

	if (pos_x > WINDOW_WIDTH)
	{
		active = false;
	}

}

void Fire::draw()
{
	graphics::setOrientation(rotation);
	brush.texture = std::string(ASSET_PATH) + "tripleFire.png";
	brush.fill_opacity = 1.0f;
	brush.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, size, size, brush);
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

void Fire::init()
{
	speed = 1.0f;
	float pos_x = CANVAS_WIDTH / 2 + 20.0f, pos_y = CANVAS_HEIGHT / 2 + 50.0f;
	size = 80;
	graphics::playSound(std::string(ASSET_PATH) + "fire.mp3", 0.1f, false);
}


Disk Fire::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = 55.0f;
	return disk;
}

Fire::Fire(const Game& mygame)
	: GameObject(mygame)
{
	init();
}

Fire::~Fire()
{
}
