/* 
 * Player.ino
 *
 * Authors:
 *			Erwin
 *			Wesley
 */


#include "Player.h"

#define GRID 20;

// default constructor
Player::Player(PLAYER_LOCATION location, MI0283QT9 *lcdPointer, Map *levelPointer, bool is_slave)
{
	Player::location = location;
	Player::lcdPointer = lcdPointer;
	Player::levelPointer = levelPointer;
	Player::is_slave = is_slave;
	Player::score = 0;
	Player::lives = 3;
} //Player

void Player::drawPlayer()
{
	if(is_slave)
		lcdPointer->fillRect(SystemFunctions::calcX(location.playerLoc) + 5, SystemFunctions::calcY(location.playerLoc) + 5, 10, 10, RGB(255,0,0));
	else
		lcdPointer->fillRect(SystemFunctions::calcX(location.playerLoc) + 5, SystemFunctions::calcY(location.playerLoc) + 5, 10, 10, RGB(30,144,255));
}

uint8_t Player::getLocation()
{
	return location.playerLoc;
}

void Player::move(uint8_t direction)
{
	if((walkDelay + WALK_DELAY) < millis()){
		walkDelay = millis();
		
		location.oldPlayerLoc = location.playerLoc;
		switch (direction)
		{
			case 1:
				moveUp();
				break;
			case 2:
				moveRight();
				break;
			case 3:
				moveDown();
				break;
			case 4:
				moveLeft(); 
		}
		if(levelPointer->checkLocation(location.newPlayerLoc) == 2){ // check if the location is a path to walk on location.
			location.playerLoc = location.newPlayerLoc;
			levelPointer->updateChunk(location.oldPlayerLoc);
			drawPlayer();
		}
	}
}

void Player::updateScore(uint32_t *score)
{
	Player::score += *score;
	*score = 0;
}
uint16_t Player::getScore()
{
	return Player::score;
}

//This function takes one live of the players lives
void Player::killPlayer()
{
	Player::lives -= 1;
}

void Player::moveUp()
{
	location.newPlayerLoc = location.playerLoc-13;
}

void Player::moveRight()
{
	location.newPlayerLoc = location.playerLoc+1;
}

void Player::moveDown()
{
	location.newPlayerLoc = location.playerLoc+13;
}

void Player::moveLeft()
{
	location.newPlayerLoc = location.playerLoc-1;
}

// default destructor
Player::~Player()
{
} //~Player


