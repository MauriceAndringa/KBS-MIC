/* 
* Player.cpp
*
* Created: 4-12-2017 11:35:12
* Author: wsvdy
*/


#include "Player.h"
#include "Map.h"

#define GRID 20;

// default constructor
Player::Player(PLAYER_LOCATION location, MI0283QT9 *lcdPointer, Map *levelPointer)
{
	Player::location = location;
	Player::lcdPointer = lcdPointer;
	Player::levelPointer = levelPointer;
} //Player

void Player::drawPlayer()
{
	levelPointer->updateChunk(location.oldPlayerLoc);
	lcdPointer->fillRect(SystemFunctions::calcX(location.playerLoc) + 5, SystemFunctions::calcY(location.playerLoc) + 5, 10, 10, RGB(255,0,0));
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
			drawPlayer();
		}
	}
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


