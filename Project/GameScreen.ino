/* 
* GameScreen.cpp
*
* Created: 21-11-2017 14:45:32
* Author: wsvdy
*/

#include <time.h>
#include <stdlib.h>
#include "GameScreen.h"
#include "Functions.h"



// default constructor
GameScreen::GameScreen()
{
} //GameScreen

void GameScreen::terug()
{
	if(LCD.touchRead()){
		int i;	
		//for(i = 0; i < sizeof(map); i++)
			//	map[i] = baseMap[i];
		
		
		SC.drawScreen();
		loaded = 0, startPressed = 0;
		
	}
}

void GameScreen::drawScreen(float level)
{
	// make background grey
	LCD.fillScreen(RGB(128,128,128));
	genValue(level);
	
	int i;
	int j = 0, tempy = 0, row = 0, tempx = 0;
	for(i = 0; i < sizeof(map); i++){
		tempx = i - (row * 13);
		
		switch (map[i]){
		case 1:
			// draw hardblock
			BMP.openFile("Hblock.bmp", (tempx * 20), tempy);
			break;
		case 2:
			//draw nothing (walk path)
			break;
		case 3:
			// draw softblock
			BMP.openFile("Sblock.bmp", (tempx * 20), tempy);
		}
		tempx = 0;
		
		j++;
		if(j == 13){
			row++;
			tempy = 20 * row;
			j = 0;
		}	
	}
}

void GameScreen::genValue(float level)
{
	int i;
	time_t t;
	srand((unsigned) FC.readRandom());
	
	for(i = 0; i < sizeof(map); i++){
		if(!map[i])
			map[i] = (int)((double)rand() / ((double)RAND_MAX + 1.0) < level) ? 3 : 2;
	}
	
	/*for(i = 0; i < sizeof(map); i++){
		if((i % 13) == 0 && i != 0){
			Serial.println();
		}
		Serial.print(map[i]);
		
	}
	*/
}

// default destructor
GameScreen::~GameScreen()
{
} //~GameScreen
