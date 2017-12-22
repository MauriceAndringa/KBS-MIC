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

/*
 * drawPlayer function draws the player
 * input: nothing
 * returns: noting
 */
void Player::drawPlayer()
{
	if(is_slave)
		lcdPointer->fillRect(SystemFunctions::calcX(location.playerLoc) + 5, SystemFunctions::calcY(location.playerLoc) + 5, 10, 10, RGB(255,0,0));
	else
		lcdPointer->fillRect(SystemFunctions::calcX(location.playerLoc) + 5, SystemFunctions::calcY(location.playerLoc) + 5, 10, 10, RGB(30,144,255));
}

/*
 * move function checks if the player is allowed to walk and to where
 * input: uint8_t direction of the movement
 * returns: noting
 */
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

/*
 * updateScore function updates the score of the player
 * input: uint16_t score as a pointer
 * returns: noting
 */
void Player::updateScore(uint16_t *score)
{
	Player::score += *score;
	*score = 0;
}

/*
 * getScore function draws the end screen on the display
 * input: nothing
 * returns: uint16_t score of the player
 */
uint16_t Player::getScore()
{
	return Player::score;
}

/*
 * KillPlayer function takes one live of the players lives
 * input: nothing
 * returns: noting
 */
void Player::killPlayer()
{
	Player::lives -= 1;
}

/*
 * getLocation get the array location of the player
 * input: nothing
 * returns: uint8_t of location
 */
uint8_t Player::getLocation()
{
	return location.playerLoc;
}

/*
 * setLocation get the array location of the player
 * input: uint8_t of location
 * returns: nothing
 */
void Player::setLocation(uint8_t newLoc)
{
	if(levelPointer->checkLocation(newLoc) == 2){ // check if the location is a path to walk on location.
		location.playerLoc = newLoc;
	}
}

/*
 * moveUp function moves the player one place up
 * input: nothing
 * returns: nothing
 */
void Player::moveUp()
{
	location.newPlayerLoc = location.playerLoc-13;
}

/*
 * moveRight function moves the player one place right
 * input: nothing
 * returns: nothing
 */
void Player::moveRight()
{
	location.newPlayerLoc = location.playerLoc+1;
}

/*
 * moveDown function moves the player one place down
 * input: nothing
 * returns: nothing
 */
void Player::moveDown()
{
	location.newPlayerLoc = location.playerLoc+13;
}

/*
 * moveLeft function moves the player one place left
 * input: nothing
 * returns: nothing
 */
void Player::moveLeft()
{
	location.newPlayerLoc = location.playerLoc-1;
}

// default destructor
Player::~Player()
{
} //~Player


