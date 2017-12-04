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
Map::Map(MI0283QT9 *lcdPointer)
{
	Map::lcdPointer = lcdPointer;
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
}

void Map::updateChunk(uint8_t x, uint8_t y){
	lcdPointer->fillRect(x,y,10,10, RGB(91,90,90));
}

// default destructor
Map::~Map()
{
} //~Map
