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
	drawBombAni(loc);
	int i;
	//check above
	for(i = -13; i > -27; i -= 13){
		if(level.checkLocation(loc + i) == NON_DESTRUCTEBLE)
			break;
		if(level.checkLocation(loc + i) == DESTRUCTEBLE){
			drawBombAni(loc + i);
			break;
		}
		drawBombAni(loc + i);
	}
	// check left
	for(i = -1; i > -3; i--){
		if(level.checkLocation(loc + i) == NON_DESTRUCTEBLE)
			break;
		if(level.checkLocation(loc + i) == DESTRUCTEBLE){
			drawBombAni(loc + i);
			break;
		}
		drawBombAni(loc + i);
	}
	// check right
	for(i = 1; i < 3; i++){
		if(level.checkLocation(loc + i) == NON_DESTRUCTEBLE)
			break;
		if(level.checkLocation(loc + i) == DESTRUCTEBLE){
			drawBombAni(loc + i);
			break;
		}
		drawBombAni(loc + i);
	}
	// check below
	for(i = 13; i < 27; i += 13){
		if(level.checkLocation(loc + i) == NON_DESTRUCTEBLE)
			break;
		if(level.checkLocation(loc + i) == DESTRUCTEBLE){
			drawBombAni(loc + i);
			break;
		}
		drawBombAni(loc + i);
	}
}

void Bomb::removeAnimation(uint8_t loc)
{
	
	level.updateLevel(loc, WALKWAY);
	level.updateChunk(loc);
	// check above
	if(level.checkLocation(loc - 13) == BOMBANIMANTION){
		level.updateLevel(loc - 13, WALKWAY);
		level.updateChunk(loc - 13);
		if(level.checkLocation(loc - 26) == BOMBANIMANTION){
			level.updateLevel(loc - 26, WALKWAY);
			level.updateChunk(loc - 26);
		}
	}
	// check left
	if(level.checkLocation(loc - 1) == BOMBANIMANTION){
		level.updateLevel(loc - 1, WALKWAY);
		level.updateChunk(loc - 1);
		if(level.checkLocation(loc - 2) == BOMBANIMANTION){
			level.updateLevel(loc - 2, WALKWAY);
			level.updateChunk(loc - 2);
		}
	}
	//check right
	if(level.checkLocation(loc + 1) == BOMBANIMANTION){
		level.updateLevel(loc + 1, WALKWAY);
		level.updateChunk(loc + 1);
		if(level.checkLocation(loc + 2) == BOMBANIMANTION){
			level.updateLevel(loc + 2, WALKWAY);
			level.updateChunk(loc + 2);
		}
	}
	// check below
	if(level.checkLocation(loc + 13) == BOMBANIMANTION){
		level.updateLevel(loc + 13, WALKWAY);
		level.updateChunk(loc + 13);
		if(level.checkLocation(loc + 26) == BOMBANIMANTION){
			level.updateLevel(loc + 26, WALKWAY);
			level.updateChunk(loc + 26);
		}
	}
}

void Bomb::drawBombAni(uint8_t loc)
{
	uint8_t x = SystemFunctions::calcX(loc);
	uint8_t y = SystemFunctions::calcY(loc);
	lcdPointer->drawRect(x + 5,y + 5,10,5,RGB(255,0,255));
	level.updateLevel(loc, BOMBANIMANTION);
}

// default destructor
Bomb::~Bomb()
{
} //~Bomb
