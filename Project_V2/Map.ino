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

void Map::drawMap()
{
	lcdPointer->fillScreen(RGB(255,0,0));
	
	seed = SystemFunctions::getRandomSeed();
	srand(seed);
	Serial.println(seed);
	// generate a level
	for(int i = 0; i < sizeof(baseLevel); i++){
		if(baseLevel[i] == 0){
			level[i] = ((rand() / (RAND_MAX + 1.0)) < 0.8) ? 3 : 2;
			if(level[i] == 1){
				level[i] = 0;
				i--;
			}
		}else
			level[i] = baseLevel[i];
	}
	
	int i = 0, j = 0, x = 0, y = 0, row = 0;
	
	for(; i <= sizeof(level); i++){
		
		x = i - (row * 13);
		switch(level[i]){
				
			case 1:
				// pillar
				lcdPointer->fillRect((x * 20), y, 20, 20, RGB(0,0,0));
				break;
				
			case 2:
				// road
				lcdPointer->fillRect((x * 20), y, 20, 20, RGB(255,255,0));
				break;
			
			case 3:
				// destructible wall
				lcdPointer->fillRect((x * 20), y, 20, 20, RGB(64,16,10));
				break;
		}
		
		x = 0;
		j++;
		
		if(j == 13){
			row++;
			y = 20 * row;
			j = 0;
		} 
	}	
}

// default destructor
Map::~Map()
{
} //~Map
