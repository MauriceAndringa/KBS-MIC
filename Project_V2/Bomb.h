/* 
 * Bomb.h
 *
 * Authors:
 *			Erwin
 *			Wesley
 */


#ifndef __BOMB_H__
#define __BOMB_H__

#define NON_DESTRUCTABLE 1
#define WALKWAY 2
#define DESTRUCTABLE 3
#define PLAYER 4
#define BOMB_ANIMATION 5


class Bomb
{
public:
	Bomb(MI0283QT9 *lcdPointer);
	~Bomb();
	
	void drawBomb(uint8_t loc);
	uint16_t explodeBomb(uint8_t loc);
	void removeAnimation(uint8_t loc);
	void drawBombAni(uint8_t loc);
protected:
private:
	Bomb( const Bomb &c );
	Bomb& operator=( const Bomb &c );

	MI0283QT9 *lcdPointer;
	
	uint16_t numberOfDestroyed;
}; //Bomb

#endif //__BOMB_H__
