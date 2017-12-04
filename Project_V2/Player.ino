/* 
* Player.cpp
*
* Created: 4-12-2017 11:35:12
* Author: wsvdy
*/


#include "Player.h"
#include "Map.h"

// default constructor
Player::Player(PLAYER_LOCATION location, MI0283QT9 *lcdPointer, Map *levelPointer)
{
	Player::location = location;
	Player::lcdPointer = lcdPointer;
	Player::levelPointer = levelPointer;
} //Player

void Player::drawPlayer()
{
	lcdPointer->fillRect(location.playerLocX, location.playerLocY, 10, 10, RGB(255,0,0));
	
	if(location.oldPlayerLocX != 0 && location.oldPlayerLocY != 0){
		levelPointer->updateChunk(location.oldPlayerLocX, location.oldPlayerLocY);
	}
}

void Player::moveRight()
{
	location.oldPlayerLocX = location.playerLocX;
	location.oldPlayerLocY = location.playerLocY;
	
	location.playerLocX += 20;
}

// default destructor
Player::~Player()
{
} //~Player
