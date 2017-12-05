/* 
* Bomb.h
*
* Created: 5-12-2017 13:33:26
* Author: wsvdy
*/


#ifndef __BOMB_H__
#define __BOMB_H__


class Bomb
{
public:
	Bomb(MI0283QT9 *lcdPointer);
	~Bomb();
	
	void drawBomb(uint8_t x, uint8_t y);
protected:
private:
	Bomb( const Bomb &c );
	Bomb& operator=( const Bomb &c );
	
	MI0283QT9 *lcdPointer;

}; //Bomb

#endif //__BOMB_H__
