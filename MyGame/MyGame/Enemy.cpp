#include "Enemy.h"
#include "graphics.h"
#include "config.h"
#include "util.h"
#include "game.h"

void Enemy::update()
{
	pos_x -= speed * graphics::getDeltaTime();
	speed += 0.001f; // we give the enemy the ability to accelarate while alive
	rotation += 0.05* graphics::getDeltaTime();
	rotation = fmodf(rotation, 360); // div 2 floats and sets the rest as the outcome 
	if (pos_x < -size)
	{
		active = false;
	}
}

void Enemy::draw()
{
	graphics::setOrientation(rotation);
	brush.texture = std::string(ASSET_PATH) + "alien.png";
	brush.fill_opacity = 1.0f;
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

void Enemy::init()
{
	speed = 0.3f;
	pos_x = CANVAS_WIDTH + 1.1f * size;
	pos_y = CANVAS_HEIGHT * rand0to1();
	size = 50 + 100 * rand0to1();
	rotation = 360*rand0to1();
	brush.outline_opacity = 0.0f;
}

Enemy::Enemy(const Game& mygame)
	: GameObject(mygame)
{
	init();
}

Enemy::~Enemy()
{
}

Disk Enemy::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = size*0.45f;
	return disk;

}
