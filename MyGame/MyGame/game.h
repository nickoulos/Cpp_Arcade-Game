#pragma once

#include "Player.h"
#include "meteor.h"
#include "Enemy.h"
#include "GunFire.h"
#include "explosion.h"
#include "fire.h"
#include "powerup.h"

class Game
{
	// status_t holds the the different states of the game 
	typedef enum {STATUS_START, STATUS_PLAYING, STATUS_OVER} status_t;
	// score keeps the points scored and count the number of meteor or enemies killed
	float score;
	float speed;
	float count;


	Player * player = nullptr;
	Enemy* enemy = nullptr;
	Meteor * meteor = nullptr;
	GunFire* gunfire = nullptr;
	Explosion* explosion = nullptr;
	Fire* fire = nullptr;
	PowerUp* powerup = nullptr;

	// expl_X and expl_Y will be used to store the position of the explotion as it will copy the position of the meteor or the enemy
	float expl_X;
	float expl_Y;

	bool player_initialized = false;
	bool debug_mode = false;
	// pwr is false as long as the player has not taken any powerups
	bool pwr = false;
	
	void spawnEnemy();
	void spawnMeteor();
	void spawnGunFire();
	void spawnExplosion();
	void spawnFire();
	void spawnPowerUp();

 	void checkEnemy();
	void checkMeteor();
	void checkExplosion();
	void checkFire();
	void checkPowerUp();

	bool checkCollisionMeteor();
	bool checkCollision();
	bool checkCollisionPowerUp();

	bool alive = true;
	status_t status = STATUS_START;

	unsigned int window_width = WINDOW_WIDTH,
				 window_height = WINDOW_HEIGHT ;


	void updateStartScreen();
	void updateLevelScreen();
	void updateGameOverScreen();
	void drawStartScreen();
	void drawLevelScreen();
	void drawGameOverScreen();

public:
	void setDebugMode(bool d) { debug_mode = d; }
	bool getDebugMode() const { return debug_mode; }
	void update();
	void draw();
	void init();
	float getScore() { return score; }
	unsigned int getWindowWidth() { return window_width; }
	unsigned int getWindowHeight() { return window_height; }
	float window2canvasX(float x);
	float window2canvasY(float y);
	void setWindowWDimensions(unsigned int w, unsigned int h) { window_width = w, window_height = h; }
	Game();
	~Game();

};