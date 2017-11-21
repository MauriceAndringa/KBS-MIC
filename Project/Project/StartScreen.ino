/* 
* StartScreen.cpp
*
* Created: 20-11-2017 12:41:33
* Author: wsvdy
*/


#include "StartScreen.h"
#include "functions.h"

functions FC;

// default constructor
StartScreen::StartScreen()
{
	//functions FC;
	FC.startTimerScreenBrightness();
	FC.screenBrightness();
	
	LCD.fillScreen(RGB(255,255,255));
	
	int x,i;
	
	x = LCD.drawText(5, 5, "Init SD-card...", RGB(0,0,0), RGB(255,255,255), 1);
	if(!SD.begin(4)){
		LCD.drawText(x, 5 , "failed", RGB(0,0,0), RGB(255,255,255), 1);
		while(1);
	}
	
	// open BMP file
	x = LCD.drawText(5, 5, "Open file...", RGB(0,0,0), RGB(255,255,255), 1);
	i = OpenBMPFile("Sscreen.bmp", 0, 0);
	//LCD.drawInteger(x, 5, i, 10, RGB(0,0,0), RGB(255,255,255), 1);
	LCD.drawRect(60, 150, 200, 30, RGB(255,255,0)); // box voor Start text
	LCD.fillRect(60, 150, 200, 30, RGB(255,255,0));
	LCD.drawText(125, 160, "Start", RGB(128,0,128), RGB(255,255,0), 2);
	
	LCD.drawRect(60, 200, 200, 30, RGB(255,255,0)); // box voor highscore text
	LCD.fillRect(60, 200, 200, 30, RGB(255,255,0));
	LCD.drawText(95, 205, "Highscore", RGB(128,0,128), RGB(255,255,0), 2);
} //StartScreen

int StartScreen::buttonPress()
{
	/*	Debug data
		Serial.print("X: ");
		Serial.println(LCD.touchX());
		Serial.print("Y: ");
		Serial.println(LCD.touchY());
		Serial.println("Hello World");
	*/
	FC.startTimerScreenBrightness();
	FC.screenBrightness();
	
	if(!LCD.touchRead())
		return 0;

	if(LCD.touchX() >= 60 && LCD.touchX() <= 260 && LCD.touchY() >= 150 && LCD.touchY() <= 180)
		return 1;

	if(LCD.touchX() >= 60 && LCD.touchX() <= 260 && LCD.touchY() >= 200 && LCD.touchY() <= 230)
		return 2;
		
}

uint8_t StartScreen::OpenBMPFile(char *file, int16_t x, int16_t y)
{
	File myFile;
	uint8_t buf[40]; //read buf (min. size = sizeof(BMP_DIPHeader))
	BMP_Header *bmp_hd;
	BMP_DIPHeader *bmp_dip;
	int16_t width, height, w, h;
	uint8_t pad, result=0;
	
	//open file
	myFile = SD.open(file);
	if(myFile)
	{
		result = 1;
		//BMP Header
		myFile.read(&buf, sizeof(BMP_Header));
		bmp_hd = (BMP_Header*)&buf[0];
		if((bmp_hd->magic[0] == 'B') && (bmp_hd->magic[1] == 'M') && (bmp_hd->offset == 54))
		{
			result = 2;
			//BMP DIP-Header
			myFile.read(&buf, sizeof(BMP_DIPHeader));
			bmp_dip = (BMP_DIPHeader*)&buf[0];
			if((bmp_dip->size == sizeof(BMP_DIPHeader)) && (bmp_dip->bitspp == 24) && (bmp_dip->compress == 0))
			{
				result = 3;
				//BMP Data (1. pixel = bottom left)
				width  = bmp_dip->width;
				height = bmp_dip->height;
				pad    = width % 4; //padding (line is multiply of 4)
				if((x+width) <= LCD.getWidth() && (y+height) <= LCD.getHeight())
				{
					result = 4;
					LCD.setArea(x, y, x+width-1, y+height-1);
					for(h=(y+height-1); h >= y; h--) //for every line
					{
						for(w=x; w < (x+width); w++) //for every pixel in line
						{
							myFile.read(&buf, 3);
							LCD.drawPixel(w, h, RGB(buf[2],buf[1],buf[0]));
						}
						if(pad)
						{
							myFile.read(&buf, pad);
						}
					}
				}
				else
				{
					LCD.drawText(x, y, "Pic out of screen!", RGB(0,0,0), RGB(255,255,255), 1);
				}
			}
		}

		myFile.close();
	}
	
	return result;
}


// default destructor
StartScreen::~StartScreen()
{
} //~StartScreen
