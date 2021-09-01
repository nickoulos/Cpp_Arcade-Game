#include "explosion.h"
#include "graphics.h"

void Explosion::update()
{
	graphics::playSound(std::string(ASSET_PATH) + "explosion1.mp3", 0.5f, false);
	if (graphics::getDeltaTime() > 2.0f)
	{
		active = false;
	}
}

void Explosion::draw()
{
	br.outline_opacity = 0.0f;

	br.fill_opacity = 1.0f;
	br.texture = std::string(ASSET_PATH) + "explosion.png";
	graphics::drawRect(pos_x, pos_y, size, size, br);
	graphics::setOrientation(0.f);

}

void Explosion::init()
{
	size = 50 + 100 * rand0to1();
	
}

Explosion::Explosion(const Game& mygame)
	: GameObject(mygame)
{
	init();
}

Explosion::~Explosion()
{
}



