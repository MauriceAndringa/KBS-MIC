/* 
* Map.cpp
*
* Created: 1-12-2017 15:04:12
* Author: wsvdy
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
} //Map

//Map::Map()
//{
//} //Map

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
}

void Map::updateChunk(uint8_t loc)
{
	uint8_t *xP = (uint8_t *)malloc(sizeof(uint8_t));
	uint8_t *yP = (uint8_t *)malloc(sizeof(uint8_t));
	
	xP = SystemFunctions::calcX(loc);
	yP = SystemFunctions::calcY(loc); 
	lcdPointer->fillRect(xP + 5,yP + 5,10,10, RGB(91,90,90));
	
	if(level[loc] == 4){
		bombPointer->drawBomb(loc);
	}else if(level[loc] == 5)
		lcdPointer->drawRect(xP,yP,10,5,RGB(255,0,255));
		
	free(&xP);
	free(&yP);
}

void Map::updateLevel(uint8_t loc, uint8_t value)
{
	level[loc] = value;
	Map::updateChunk(loc);
}

/*uint8_t Map::calculateArrayLocation(uint8_t x, uint8_t y)
{
	return ((x - 5) + (13 * (y - 5))) / 20;
}*/

uint8_t Map::checkLocation(uint8_t location)
{
	return level[location]==2?1:0;
	
}

// default destructor
Map::~Map()
{
} //~Map
