/* 
* Player.h
*
* Created: 4-12-2017 11:35:12
* Author: wsvdy
*/


#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <stdint.h>

typedef struct {
	uint8_t playerLocX;
	uint8_t playerLocY;
	uint8_t oldPlayerLocX;
	uint8_t oldPlayerLocY;
} PLAYER_LOCATION;

class Player
{
public:
	Player(PLAYER_LOCATION location, MI0283QT9 *lcdPointer);
	~Player();
	
	void drawPlayer();
	void moveRight();
protected:
private:
	Player( const Player &c );
	Player& operator=( const Player &c );
	
	PLAYER_LOCATION location;
	
	MI0283QT9 *lcdPointer;

}; //Player

#endif //__PLAYER_H__
