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
	level.updateLevel(loc, BOMBANIMANTION);
	//check above
	if(level.checkLocation(loc - 13) == DESTRUCTEBLE)
		level.updateLevel(loc - 13, BOMBANIMANTION);
	else if(level.checkLocation(loc - 13) == WALKWAY){
		level.updateLevel(loc - 13, BOMBANIMANTION);
		if(level.checkLocation(loc - 26) == WALKWAY || level.checkLocation(loc - 26) == DESTRUCTEBLE)
			level.updateLevel(loc - 26, BOMBANIMANTION);
	}
	// check left
	if(level.checkLocation(loc - 1) == DESTRUCTEBLE)
		level.updateLevel(loc - 1, BOMBANIMANTION);
	else if(level.checkLocation(loc - 1) == WALKWAY){
		level.updateLevel(loc - 1, BOMBANIMANTION);
		if(level.checkLocation(loc - 2) == WALKWAY || level.checkLocation(loc - 2) == DESTRUCTEBLE)
			level.updateLevel(loc - 2, BOMBANIMANTION);
	}
	// check right
	if(level.checkLocation(loc + 1) == DESTRUCTEBLE)
		level.updateLevel(loc + 1, BOMBANIMANTION);
	else if(level.checkLocation(loc + 1) == WALKWAY){
		level.updateLevel(loc + 1, BOMBANIMANTION);
		if(level.checkLocation(loc + 2) == WALKWAY || level.checkLocation(loc + 2) == DESTRUCTEBLE)
			level.updateLevel(loc + 2, BOMBANIMANTION);
	}
	// check below
	if(level.checkLocation(loc + 13) == DESTRUCTEBLE)
		level.updateLevel(loc + 13, BOMBANIMANTION);
	else if(level.checkLocation(loc + 13) == WALKWAY){
		level.updateLevel(loc + 13, BOMBANIMANTION);
		if(level.checkLocation(loc + 26) == 2 || level.checkLocation(loc + 26) == DESTRUCTEBLE)
			level.updateLevel(loc + 26, BOMBANIMANTION);
	}
}

void Bomb::removeAnimation(uint8_t loc)
{
	
	level.updateLevel(loc, WALKWAY);
	// check above
	if(level.checkLocation(loc - 13) == BOMBANIMANTION){
		level.updateLevel(loc - 13, WALKWAY);
		if(level.checkLocation(loc - 26) == BOMBANIMANTION)
			level.updateLevel(loc - 26, WALKWAY);
	}
	// check left
	if(level.checkLocation(loc - 1) == BOMBANIMANTION){
		level.updateLevel(loc - 1, WALKWAY);
		if(level.checkLocation(loc - 2) == BOMBANIMANTION)
			level.updateLevel(loc - 2, WALKWAY);
	}
	//check right
	if(level.checkLocation(loc + 1) == BOMBANIMANTION){
		level.updateLevel(loc + 1, WALKWAY);
		if(level.checkLocation(loc + 2) == BOMBANIMANTION)
			level.updateLevel(loc + 2, WALKWAY);
	}
	// check below
	if(level.checkLocation(loc + 13) == BOMBANIMANTION){
		level.updateLevel(loc + 13, WALKWAY);
		if(level.checkLocation(loc + 26) == BOMBANIMANTION)
			level.updateLevel(loc + 26, WALKWAY);
	}
}

// default destructor
Bomb::~Bomb()
{
} //~Bomb
