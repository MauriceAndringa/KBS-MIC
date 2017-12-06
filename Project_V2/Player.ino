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
	
	levelPointer->updateChunk(pixelX(location.oldPlayerLoc), pixelY(location.oldPlayerLoc));
	lcdPointer->fillRect(pixelX(location.playerLoc), pixelY(location.playerLoc), 10, 10, RGB(255,0,0));
	
}

uint8_t Player::getLocationX()
{
	return pixelX(location.playerLoc);
}

uint8_t Player::getLocationY()
{
	return pixelY(location.playerLoc);
}

void Player::move(uint8_t direction)
{
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
		break;
	}
	if(levelPointer->checkLocation(location.newPlayerLoc)){
		location.playerLoc = location.newPlayerLoc;
		drawPlayer();
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

uint8_t Player::pixelX(uint8_t loc)
{
	return 5+(loc%13)*GRID;
}

uint8_t Player::pixelY(uint8_t loc)
{
	return 5+(loc/13)*GRID;	
}

// default destructor
Player::~Player()
{
} //~Player


