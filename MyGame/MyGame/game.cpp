#include "game.h"
#include "graphics.h"
#include "config.h"


void Game::spawnEnemy()
{
	if (!enemy) 
	{
		// Every new enemy has more speed than the previous one
		enemy = new Enemy(*this);
		speed = enemy->getSpeed();
		enemy->setSpeed(speed + count * 0.1);
	}
	
}

void Game::spawnMeteor()
{
	if (!meteor)
	{
		// Every new meteor has more speed than the previous one
		meteor = new Meteor(*this);
		speed = meteor->getSpeed();
		meteor->setSpeed(speed + count*0.1);
	}

}

void Game::spawnGunFire()
{
	if (!gunfire)
	{
		gunfire = new GunFire (*this);
	}

}

void Game::spawnExplosion()
{
	if (!explosion)
	{
		explosion = new Explosion(*this);
	}
}

void Game::spawnFire()
{
	if (!fire)
	{
		fire = new Fire(*this);
		
		if (pwr==true)
		{
			// If player has taken powerup he has more speed 
			speed = fire->getSpeed();
			fire->setSpeed(speed + 5);
		}
	}
}

void Game::spawnPowerUp()
{
	if (!powerup)
	{
		powerup = new PowerUp(*this);
	}

}





void Game::checkEnemy()
{
	if (enemy && !enemy->isActive())
	{
		delete  enemy;
		enemy = nullptr;
	}
}

void Game::checkMeteor()
{
	if (meteor && !meteor->isActive())
	{
		delete  meteor;
		meteor = nullptr;
	}
}

void Game::checkExplosion()
{
	if (explosion && !explosion->isActive())
	{
		delete  explosion;
		explosion = nullptr;
	}
}

void Game::checkFire()
{
	if(fire && !fire->isActive())
	{
		delete  fire;
		fire = nullptr;
	}
}
void Game::checkPowerUp()
{
	if (powerup && !powerup->isActive())
	{
		delete  powerup;
		powerup = nullptr;
	}
}



bool Game::checkCollisionMeteor()
{
	if (!player || !meteor )
	{
		return false;
	}

	Disk d1 = player->getCollisionHull();
	Disk d2 = fire->getCollisionHull();
	Disk d3 = gunfire->getCollisionHull();
	Disk d4 = meteor->getCollisionHull();

	float dx14 = d1.cx - d4.cx;
	float dy14 = d1.cy - d4.cy;

	float dx34 = d3.cx - d4.cx;
	float dy34 = d3.cy - d4.cy;

	float dx24 = d2.cx - d4.cx;
	float dy24 = d2.cy - d4.cy;

	//if the fire collide with the meteor we get points

	if (sqrt(dx24 * dx24 + dy24 * dy24) < d2.radius + d4.radius)
	{
		score += 5.0f;
		alive = false;
		expl_X = meteor->getPosX();
		expl_Y = meteor->getPosY();
		count += 0.1f;
		return true;
	}

	//if the meteor collide with the player or his weapon we lose life points

	if ((sqrt(dx14 * dx14 + dy14 * dy14) < d1.radius + d4.radius) || (sqrt(dx34 * dx34 + dy34 * dy34) < d4.radius + d3.radius))
	{
		player->drainLife(0.1f);
		expl_X = meteor->getPosX();
		expl_Y = meteor->getPosY();
		alive = false;
		if (player->getRemainingLife() == 0.0f)
		{
			status = STATUS_OVER;
			delete player;
			player = nullptr;
			player_initialized = false;

			delete explosion;
			explosion = nullptr;
		}
		return true;
	}
	else
		return false;
}

bool Game::checkCollision()
{
	if (!player || !enemy)
	{
		return false;
	}

	Disk d1 = player->getCollisionHull();
	Disk d2 = enemy->getCollisionHull();
	Disk d3 = gunfire->getCollisionHull();
	Disk d4 = fire->getCollisionHull();

	float dx12 = d1.cx - d2.cx;
	float dy12 = d1.cy - d2.cy;

	float dx23 = d3.cx - d2.cx;
	float dy23 = d3.cy - d2.cy;

	float dx24 = d2.cx - d4.cx;
	float dy24 = d2.cy - d4.cy;

	//if the fire collide with the enemy we get points
	if (sqrt(dx24 * dx24 + dy24 * dy24) < d2.radius + d4.radius)
	{
		score += 10.0f;
		alive = false;
		expl_X = enemy->getPosX();
		expl_Y = enemy->getPosY();
		count += 1.0f;
		return true;
	}

	//if the enemy collide with the player or his weapon we lose life points
	if ((sqrt(dx12 * dx12 + dy12 * dy12) < d1.radius + d2.radius) || (sqrt(dx23 * dx23 + dy23 * dy23) < d2.radius + d3.radius))
	{
		player->drainLife(0.1f);
		expl_X = enemy->getPosX();
		expl_Y = enemy->getPosY();
		alive = false;
		if (player->getRemainingLife() == 0.0f)
		{
			
			delete player;
			player = nullptr;
			player_initialized = false;	

			delete explosion;
			explosion = nullptr;

			status = STATUS_OVER;
		}
		return true;
	}
	else
		return false;
}

bool Game::checkCollisionPowerUp()
{
	if (!player || !powerup)
	{
		return false;
	}

	Disk d1 = player->getCollisionHull();
	Disk d2 = powerup->getCollisionHull();

	float dx12 = d1.cx - d2.cx;
	float dy12 = d1.cy - d2.cy;

	// if the player collides with the power up he sets the variable pwr as true
	if (sqrt(dx12 * dx12 + dy12 * dy12) < d1.radius + d2.radius)
	{
		pwr = true;
		return true;
	}
	else
		return false;
}


void Game::updateStartScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		status = STATUS_PLAYING;
	}

	graphics::MouseState ms;
	graphics::getMouseState(ms);
	if (ms.button_left_pressed)
	{
		if (ms.cur_pos_y > 465 && ms.cur_pos_y < 565) status = STATUS_PLAYING;
	}

	if (ms.cur_pos_y > 565 && ms.cur_pos_y < 610) {
		graphics::Brush br;
		char info[40];
		sprintf_s(info, "Movement WASD, Exit ESC");
		graphics::drawText(2 * CANVAS_WIDTH / 5, CANVAS_HEIGHT / 2 + 100, 60, info, br);
	} 
}



void Game::updateLevelScreen()
{
	

	if (!player_initialized && graphics::getGlobalTime() > 1000)
	{
		player = new Player(*this);
		player_initialized = true;
		
	}
	
	
	if (player)
	{
		spawnGunFire();
		

		player->update();

		//gunFire takes the position of the player and spawns always according to his position
		gunfire->setPosX(player->getPosX());
		gunfire->setPosY(player->getPosY() + 50.0f);
		gunfire->update();

		checkFire();
		//fire takes the position of the player and spawns always according to his position
		if (!fire) 
		{
			spawnFire();
			fire->setPosX(player->getPosX() + 60.0f);
			fire->setPosY(player->getPosY() + 60.0f);
		}
		else
		{
			fire->update();
		}	
	}
	// we want the power up to be accessible only once above 200 score
	if (score >= 200 && score < 210)
	{
		spawnPowerUp();
		checkPowerUp();
	}
	if (powerup)
	{
		powerup->update();
	}

	checkEnemy();
	spawnEnemy();
	
	if (enemy)
	{
		enemy->update();
	}
	checkMeteor();
	spawnMeteor();

	if (meteor)
	{
		meteor->update();
	}

	if (alive == false) 
	{
		spawnExplosion();
		if (explosion)
		{

			explosion->setPosX(expl_X);
			explosion->setPosY(expl_Y);
			explosion->update();

			alive = true;
		}
	}
	

	if (checkCollisionMeteor())
	{
		delete meteor;
		meteor = nullptr;
	}

	if (checkCollision())
	{
		delete enemy;
		enemy = nullptr;
	}

	if (checkCollisionPowerUp())
	{
		delete powerup;
		powerup = nullptr;
	}

}

void Game::updateGameOverScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_SPACE))
	{
		//we set some variables to zero as this is the only place that this change will not influence any other aspects of the game
		count = 0.0f;
		score = 0.0f;
		speed = 0.0f;
		status = STATUS_START;
	}

}

void Game::drawStartScreen()
{
	graphics::Brush br;
	char info[40];
	sprintf_s(info, "Press Enter to Start");
	graphics::drawText(2 * CANVAS_WIDTH / 5, CANVAS_HEIGHT / 2, 60, info, br);


	sprintf_s(info, "Controls");
	graphics::drawText(2 * CANVAS_WIDTH / 5, CANVAS_HEIGHT / 2 + 50, 60, info, br);

	graphics::MouseState ms;
	graphics::getMouseState(ms);

	graphics::drawDisk(window2canvasX((float)ms.cur_pos_x), window2canvasY((float)ms.cur_pos_y), 10, br);
}

void Game::drawGameOverScreen()
{

	graphics::Brush br;
	char info[100];
	sprintf_s(info, "Game over! Press Space to play again. ESC to Exit.");
	graphics::drawText(2*CANVAS_WIDTH / 6, CANVAS_HEIGHT / 2, 60, info, br);

	sprintf_s(info, "Score: %6.2f", score);
	
	graphics::drawText(3 * CANVAS_WIDTH / 6, CANVAS_HEIGHT / 2 + 50, 60, info, br);

	
	graphics::MouseState ms;
	graphics::getMouseState(ms);

	graphics::drawDisk(window2canvasX((float)ms.cur_pos_x), window2canvasY((float)ms.cur_pos_y), 10, br);

	
}

void Game::drawLevelScreen()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "background.png";
	br.outline_opacity = 0.0f;

	//float offset = CANVAS_HEIGHT + sinf(graphics::getGlobalTime()) / 4;


	//draw background
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	
	//draw enemy
	if (enemy)
		enemy->draw();

	//draw player
	if (player)
		player->draw();

	//draw gunfire
	if (gunfire)
		gunfire->draw();

	//draw fire
	if (fire)
		fire->draw();

	//draw meteor
	if (meteor)
		meteor->draw();

	//draw explosion
	if (explosion)
		explosion->draw();
	
	//draw powerup
	if (powerup)
		powerup->draw();

	//draw score
	if (player)
	{
		char info[40];
		sprintf_s(info, "%6.2f", score);
		graphics::drawText(30, 30, 40, info, br);
	}


	//UI/info player
#ifdef GAME_BEDUG
	if (player || debug_mode)
	{
		char info[40];
		sprintf_s(info, "%6.2f, %6.2f", player->getPosX(), player->getPosY());
		graphics::drawText(30, 30, 40, info, br);
	}
	#endif

	float player_life = player ? player->getRemainingLife() : 0.0f;

	br.outline_opacity = 0.0f;

	br.fill_color[0] = 0.2f;

	br.texture = "";


	br.fill_secondary_color[0] = 1.0f;


	br.gradient = true;
	br.gradient_dir_u = 1.0f;
	br.gradient_dir_v = 0.0f;

	graphics::drawRect(CANVAS_WIDTH - 100 - ((1.0f - player_life) * 120 / 2), 30, player_life * 120, 20, br);

	br.outline_opacity = 1.0f;
	br.gradient = true;
	br.fill_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH - 100, 30, 120, 20, br);

}

void Game::update()
{
	if (status == STATUS_START)
	{
		updateStartScreen();
	}
	else if (status == STATUS_PLAYING)
	{
		updateLevelScreen();	
	}
	else
	{
		updateGameOverScreen();
	}
}

void Game::draw()
{
	if (status == STATUS_START)
	{
		drawStartScreen();
	}
	else if (status == STATUS_PLAYING)
	{
		drawLevelScreen();
	}
	else
	{
		drawGameOverScreen();
	}
}

void Game::init()
{
	graphics::setFont(std::string(ASSET_PATH) + "MenuFont.ttf");
	graphics::playMusic(std::string(ASSET_PATH) + "music.mp3", 0.5f, true, 4000);
}

float Game::window2canvasX(float x)
{
	return x*CANVAS_WIDTH/(float)window_width;
}

float Game::window2canvasY(float y)
{
	return y * CANVAS_HEIGHT / (float)window_height;
}

Game::Game()
{
}

Game::~Game()
{
	if (player)
	{
		delete player;
	}
	if (gunfire)
	{
		delete gunfire;
	}
	if (fire)
	{
		delete fire;
	}
	if (meteor)
	{
		delete meteor;
	}
}
