/*
 * Bomb.ino
 *
 * Authors:
 *			Erwin
 *			Wesley
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

uint32_t Bomb::explodeBomb(uint8_t loc)
{
	level.updateLevel(loc, BOMB_ANIMATION);
	numberOfDestroyed = 0;
	int i;
	//check above
	for(i = -13; i > -27; i -= 13){
		if(level.checkLocation(loc + i) == NON_DESTRUCTABLE)
		break;
		if(level.checkLocation(loc + i) == DESTRUCTABLE){
			numberOfDestroyed++;
			drawBombAni(loc + i);
			break;
		}
		if (externalPlayer.getLocation()==(loc+i))
		externalPlayer.killPlayer();
		if (internalPlayer.getLocation()==(loc+i))
		internalPlayer.killPlayer();
		drawBombAni(loc + i);
	}
	// check left
	for(i = -1; i > -3; i--){
		if(level.checkLocation(loc + i) == NON_DESTRUCTABLE)
		break;
		if(level.checkLocation(loc + i) == DESTRUCTABLE){
			numberOfDestroyed++;
			drawBombAni(loc + i);
			break;
		}
		if (externalPlayer.getLocation()==(loc+i))
		externalPlayer.killPlayer();
		if (internalPlayer.getLocation()==(loc+i))
		internalPlayer.killPlayer();
		drawBombAni(loc + i);
	}
	// check right
	for(i = 1; i < 3; i++){
		if(level.checkLocation(loc + i) == NON_DESTRUCTABLE)
		break;
		if(level.checkLocation(loc + i) == DESTRUCTABLE){
			numberOfDestroyed++;
			drawBombAni(loc + i);

			break;
		}
		if (externalPlayer.getLocation()==(loc+i))
		externalPlayer.killPlayer();
		if (internalPlayer.getLocation()==(loc+i))
		internalPlayer.killPlayer();
		drawBombAni(loc + i);
	}
	// check below
	for(i = 13; i < 27; i += 13){
		if(level.checkLocation(loc + i) == NON_DESTRUCTABLE)
		break;
		if(level.checkLocation(loc + i) == DESTRUCTABLE){
			numberOfDestroyed++;
			drawBombAni(loc + i);
			break;
		}
		if (externalPlayer.getLocation()==(loc+i))
		externalPlayer.killPlayer();
		if (internalPlayer.getLocation()==(loc+i))
		internalPlayer.killPlayer();
		drawBombAni(loc + i);
	}
	// check same location
	if (externalPlayer.getLocation()==(loc))
		externalPlayer.killPlayer();
	if (internalPlayer.getLocation()==(loc))
		internalPlayer.killPlayer();

	return numberOfDestroyed;
}

void Bomb::removeAnimation(uint8_t loc)
{	
	level.updateLevel(loc, WALKWAY);
	level.updateChunk(loc);
	// check above
	if(level.checkLocation(loc - 13) == BOMB_ANIMATION){
		level.updateLevel(loc - 13, WALKWAY);
		level.updateChunk(loc - 13);
		if(level.checkLocation(loc - 26) == BOMB_ANIMATION){
			level.updateLevel(loc - 26, WALKWAY);
			level.updateChunk(loc - 26);
		}
	}
	// check left
	if(level.checkLocation(loc - 1) == BOMB_ANIMATION){
		level.updateLevel(loc - 1, WALKWAY);
		level.updateChunk(loc - 1);
		if(level.checkLocation(loc - 2) == BOMB_ANIMATION){
			level.updateLevel(loc - 2, WALKWAY);
			level.updateChunk(loc - 2);
		}
	}
	//check right
	if(level.checkLocation(loc + 1) == BOMB_ANIMATION){
		level.updateLevel(loc + 1, WALKWAY);
		level.updateChunk(loc + 1);
		if(level.checkLocation(loc + 2) == BOMB_ANIMATION){
			level.updateLevel(loc + 2, WALKWAY);
			level.updateChunk(loc + 2);
		}
	}
	// check below
	if(level.checkLocation(loc + 13) == BOMB_ANIMATION){
		level.updateLevel(loc + 13, WALKWAY);
		level.updateChunk(loc + 13);
		if(level.checkLocation(loc + 26) == BOMB_ANIMATION){
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
	level.updateLevel(loc, BOMB_ANIMATION);
}

// default destructor
Bomb::~Bomb()
{
} //~Bomb
