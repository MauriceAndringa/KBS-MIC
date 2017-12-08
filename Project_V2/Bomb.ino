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
	uint8_t *xP = (uint8_t *)malloc(sizeof(uint8_t));
	uint8_t *yP = (uint8_t *)malloc(sizeof(uint8_t));
	
	xP = SystemFunctions::calcX(loc);
	yP = SystemFunctions::calcY(loc);
	
	lcdPointer->fillCircle(xP + 9, yP + 9, 4, RGB(255,0,255));
	
	free(&xP);
	free(&yP);
}

void Bomb::explodeBomb(uint8_t loc)
{
	level.updateLevel(loc, 5);	
}

// default destructor
Bomb::~Bomb()
{
} //~Bomb
