/* 
 * Player.h
 *
 * Authors:
 *			Erwin
 *			Wesley
 */


#ifndef __PLAYER_H__
#define __PLAYER_H__


#include <stdint.h>

#define WALK_DELAY 100
#define SCOREPLAYER 6

typedef struct {
	uint8_t playerLoc;
	uint8_t newPlayerLoc;
	uint8_t oldPlayerLoc;
	
} PLAYER_LOCATION;

class Player
{
public:
	Player(PLAYER_LOCATION location, MI0283QT9 *lcdPointer, Map *levelPointer, bool is_slave);
	~Player();
	
	void drawPlayer();
	void move(uint8_t direction);
	void updateScore(uint16_t *score);
	uint16_t getScore();
	void killPlayer();
	uint8_t getLocation();
	void setLocation(uint8_t newLoc);
	
	uint8_t lives;
protected:
private:
	Player( const Player &c );
	Player& operator=( const Player &c );
	void moveUp();
	void moveRight();
	void moveDown();
	void moveLeft();
	PLAYER_LOCATION location;
	
	MI0283QT9 *lcdPointer;
	Map  *levelPointer;
	View *requestedViewPointer;
	
	unsigned long walkDelay;
	bool is_slave;
	uint16_t score;
}; //Player

#endif //__PLAYER_H__
