/* 
 * Map.ino
 *
 * Authors:
 *			Erwin
 *			Wesley
 */

#include "Map.h"

// baselevel is a shell which is used to force a few pillars and empty places in the level
uint8_t baseLevel[143] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 1,
	1, 2, 1, 0, 1, 0, 1, 0, 1, 0, 1, 2, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 2, 1, 0, 1, 0, 1, 0, 1, 0, 1, 2, 1,
	1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

// default constructor
Map::Map(MI0283QT9 *lcdPointer, Bomb *bombPointer)
{
	Map::lcdPointer = lcdPointer;
	Map::bombPointer = bombPointer;
	readyToRemoveSecondTimer = 0;
} //Map

void Map::drawMap(float difficulty)
{
	lcdPointer->fillScreen(RGB(0,0,0));
	
	// generate a random seed and use it to generate randoms values.
	srand(SystemFunctions::getRandomSeed());
	
	// generate a level
	for(int i = 0; i < sizeof(baseLevel); i++){
		
		//check if something needs to be generated else copy from basemap.
		if(baseLevel[i] == 0){
			level[i] = ((rand() / (RAND_MAX + 1.0)) < difficulty) ? 3 : 2;
			
			// check if the generated value is a 1 (aka pillar) and if remove it and do it over.
			if(level[i] == 1){
				level[i] = 0;
				i--;
			}
		}else
			// copy value from baselevel into level
			level[i] = baseLevel[i];
	}
	
	int i = 0, j = 0, x = 0, y = 0, row = 0;
	
	for(; i < sizeof(level); i++){
		
		x = i - (row * 13);
		
		switch(level[i]){
				
			case 1:
				// pillar
				lcdPointer->fillRect((x * 20), y, 20, 20, COLOUR_PILLAR);
				break;
				
			case 2:
				// road
				lcdPointer->fillRect((x * 20), y, 20, 20, COLOUR_ROAD);
				break;
			
			case 3:
				// destructible wall
				lcdPointer->fillRect((x * 20), y, 20, 20, COLOUR_DESTROYABLE);
				break;
		}
		
		lcdPointer->drawRect((x * 20), y, 20, 20, COLOUR_GRID);
		
		x = 0;
		j++;
		
		if(j == 13){
			row++;
			y = 20 * row;
			j = 0;
		} 
	}
	// draw the score and remaining live points for you and enemy
	lcdPointer->drawText(268, 20,"Score:", RGB(0,255,0), RGB(0,0,0), 1);
	lcdPointer->drawText(270, 35, "You:", RGB(255,0,0), RGB(0,0,0), 1);
	lcdPointer->drawText(275, 45, "S:", RGB(255,0,0), RGB(0,0,0), 1);
	lcdPointer->drawText(275, 55, "L:", RGB(255,0,0), RGB(0,0,0), 1);
	lcdPointer->drawText(270, 70, "Enemy:", RGB(30,144,255), RGB(0,0,0), 1);
	lcdPointer->drawText(275, 80, "S:", RGB(30,144,255), RGB(0,0,0), 1);
	lcdPointer->drawText(275, 90, "L:", RGB(30,144,255), RGB(0,0,0), 1);
}

void Map::updateChunk(uint8_t loc)
{
	uint8_t x = SystemFunctions::calcX(loc);
	uint8_t y = SystemFunctions::calcY(loc); 
	lcdPointer->fillRect(x+1,y+1,18,18, RGB(91,90,90));
	
	// Keep the bomb on screen if you walk of it.
	if(level[loc] == 4) 
		bombPointer->drawBomb(loc);
}

void Map::updateLevel(uint8_t loc, uint8_t value)
{
	level[loc] = value;		// change old value in new value
}

/*
* update the level in the level array
* input: location
* output: value
*/
uint8_t Map::checkLocation(uint8_t location)
{
	if(level[location] == 1)
		return 1; // return value 1 to indicate that there is a pillar on this location.
	else if (level[location] == 2)
		return 2; // return value 2 to indicate that there is a walk path on this location.
	else if (level[location] == 3)
		return 3; // return value 3 to indicate that there is a destructible object on this location.
	else if(level[location] == 5)
		return 5; // return value 5 to indicate that there is a bomb explosion animation on this location.
	return 0;
}

// default destructor
Map::~Map()
{
} //~Map
