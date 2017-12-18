/* 
* Bomb.h
*
* Created: 5-12-2017 13:33:26
* Author: wsvdy
*/


#ifndef __BOMB_H__
#define __BOMB_H__

//#include "Map.h"
#define NON_DESTRUCTEBLE 1
#define WALKWAY 2
#define DESTRUCTEBLE 3
#define PLAYER 4
#define BOMBANIMANTION 5


class Bomb
{
public:
	Bomb(MI0283QT9 *lcdPointer);
	~Bomb();
	
	void drawBomb(uint8_t loc);
	uint32_t explodeBomb(uint8_t loc);
	void removeAnimation(uint8_t loc);
	void drawBombAni(uint8_t loc);
protected:
private:
	Bomb( const Bomb &c );
	Bomb& operator=( const Bomb &c );

	MI0283QT9 *lcdPointer;
	
	uint32_t numberOfDestroyed;
}; //Bomb

#endif //__BOMB_H__
