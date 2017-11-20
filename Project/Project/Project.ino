
/*
 * Project.cpp
 *
 * Created: 20-11-2017 11:48:05
 * Author : wsvdy
 */ 

#include <avr/io.h>
#include <MI0283QT9.h>
#include "StartScreen.h"

MI0283QT9 LCD;


int main(void)
{
	init();
	Serial.begin(9600);

	StartScreen SC;
	//LCD.drawText()
    /* Replace with your application code */
    while (1) 
    {
    }
}

