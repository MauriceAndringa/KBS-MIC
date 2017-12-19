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
	readyToRemoveSecondTimer = 0;
	//minute = 0;
	//secondTenth = 0;
	//second = 0;
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
	
	if(level[loc] == 4) // draw the bom on this location
		bombPointer->drawBomb(loc);
	//else if(level[loc] == 5) // draw the bomb explode animation
		//bombPointer->drawBombAni(loc);
		//lcdPointer->drawRect(x + 5,y + 5,10,5,RGB(255,0,255));
}

void Map::updateLevel(uint8_t loc, uint8_t value)
{
	level[loc] = value;		// change old value in new value
	//Map::updateChunk(loc);	// call update Chunk
}

/* 
 * drawTimer 
 draws the time on screen is minutes and seconds
 * input:  na
 * output: na
 */
/*
void Map::drawTimer()
{
	lcdPointer->drawInteger(270, 10, minute, 10, RGB(0,255,0), RGB(0,0,0), 1);
	lcdPointer->drawChar(276,10,':',RGB(0,255,0),RGB(0,0,0),1);
	lcdPointer->drawInteger(284, 10, secondTenth, 10, RGB(0,255,0), RGB(0,0,0), 1);
	lcdPointer->drawInteger(292, 10, second, 10, RGB(0,255,0), RGB(0,0,0), 1);
}

void Map::updateTimer()
{
	if(minute == 0 && secondTenth == 0 && second == 0){
		exit(1);		
	}
	
	if(millis() < readyToRemoveSecondTimer + 1000)
		return;
	
	readyToRemoveSecondTimer = millis();
	if(second > 0){
		second--;
		return;
	}
	
	if(secondTenth == 0 && second == 0){
		secondTenth = 5; second = 9;
		minute--;
		return;
	}
	
	if(second == 0){
		second = 9;
		secondTenth --;
		return;
	}
	
	second--;
}

void Map::drawScore(){
	//internalPlayerScore = internalPlayer.getScore();
	//   externalPlayerScore = externalPlayer.getScore();
	
	lcdPointer->drawInteger(270, 30, internalPlayer.getScore(), 10, RGB(255,0,0), RGB(0,0,0), 1);
	lcdPointer->drawInteger(270, 40, externalPlayer.getScore(), 10, RGB(30,144,255), RGB(0,0,0), 1);
}*/

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
		return 3; // return value 3 to indicate that there is a destructeble object on this location.
	else if(level[location] == 5)
		return 5; // return value 5 to indicate that there is a bomb explosion animation on this location.
	return 0;
}

// default destructor
Map::~Map()
{
} //~Map
