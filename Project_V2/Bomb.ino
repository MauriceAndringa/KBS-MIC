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

void Bomb::drawBomb(uint8_t loc)
{
	uint8_t x = SystemFunctions::calcX(loc);
	uint8_t y = SystemFunctions::calcY(loc);
	
	lcdPointer->fillCircle(x + 9, y + 9, 4, RGB(255,0,255));
}

void Bomb::explodeBomb(uint8_t loc)
{
	level.updateLevel(loc, 5);	
}

// default destructor
Bomb::~Bomb()
{
} //~Bomb
