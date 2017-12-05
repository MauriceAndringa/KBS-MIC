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
Player::Player(PLAYER_LOCATION location, MI0283QT9 *lcdPointer)
{
	Player::location = location;
	Player::lcdPointer = lcdPointer;
} //Player

void Player::drawPlayer()
{
	lcdPointer->fillRect(location.playerLocX, location.playerLocY, 10, 10, RGB(255,0,0));
	
	if(location.oldPlayerLocX != 0 && location.oldPlayerLocY != 0){
		level.updateChunk(location.oldPlayerLocX, location.oldPlayerLocY);
	}
}

void Player::move(uint8_t direction)
{
	location.oldPlayerLocX = location.playerLocX;
	location.oldPlayerLocY = location.playerLocY;
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
}

void Player::moveUp()
{
	location.playerLocY += GRID;
}

void Player::moveRight()
{
	location.playerLocX += GRID;
}

void Player::moveDown()
{

	location.playerLocY -= GRID;
}

void Player::moveLeft()
{

	location.playerLocX -= GRID;
}


// default destructor
Player::~Player()
{
} //~Player


