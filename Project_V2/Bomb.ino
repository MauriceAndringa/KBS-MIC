/* 
* Bomb.cpp
*
* Created: 5-12-2017 13:33:25
* Author: wsvdy
*/


#include "Bomb.h"

// default constructor
Bomb::Bomb(MI0283QT9 *lcdPointer)
{
	Bomb::lcdPointer = lcdPointer;
} //Bomb

void Bomb::drawBomb(uint8_t x, uint8_t y)
{
	lcdPointer->fillCircle(x, y, 4, RGB(255,0,255));
}

// default destructor
Bomb::~Bomb()
{
} //~Bomb
