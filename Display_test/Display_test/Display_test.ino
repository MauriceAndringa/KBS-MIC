/*
 * Display_test.cpp
 *
 * Created: 17-11-2017 08:54:27
 * Author : wsvdy
 */ 

#include <avr/io.h>
#include <MI0283QT9.h> // Deze is nodig om het LCD schermpje aan te sturen (deze functie bezig niet draw functies maar kan ze wel gebruiken, atmel kan aangeven tijdens het coderen dat de functie niet bestaat, maar build wel)

MI0283QT9 lcd; // maakt het makelijker om de LCD aan te sturen.


int main(void)
{
	int x = 0, y = 0, vierkantGr = 20, i, nr = 0;
	init(); // om de clocks te gelijk te lopen, is niet verplicht maar wel aangeraden
	lcd.begin(); // start het scherm
	
	lcd.fillScreen(RGB(255,192,203)); // achtergrond wordt hier gekleurd met RGB values
	
	for(i = 0; i < 300; i++){
		if(x == 0 || y == 0 || x == 300 || y == 220)
			lcd.fillRect(x,y,vierkantGr,vierkantGr, RGB(128,128,128)); // maakt het eerste blokje aan de zijkanten van het scherm grijs
		
		if(y < 220){
			lcd.drawRect(x,y,vierkantGr, vierkantGr, RGB(0,0,0)); // tekent een vierkant van 20 pixels op cord x en cord y met RGB kleur zwart
			//lcd.drawInteger(x, y, nr, DEC, RGB(0,0,0), RGB(255,192,203), 1); //dec
			//nr++;
		}
		
		//if(x == 0 || y == 0 || x == 300 || y == 220) // TODO test als deze 2 regels weg kunnen
			//lcd.fillRect(x,y,vierkantGr,vierkantGr, RGB(128,128,128)); // TODO test als deze 2 regels weg kunnen
			
		x += vierkantGr; // zorgt er voor dat het volgende blokje precies er naast komt(dus 2 pixel border tussen de blokjes)
		if(x >= 320){ // TODO check als 320 veranderd kan worden door 300
			x = 0; // als het laatste blockje is getekent zorg er dan voor dat x weer aan het begin begint TODO check als 0 veranders kan worden door vierkantGr
			if(y < 220) // TODO check als deze if statement weg kan
				y += vierkantGr; // wanneer x aan het begin begint dan zorgt deze er voor dat cord y naar beneden gaat.
		}
	}
		
    /* Replace with your application code */
    while (1) 
    {
		lcd.drawInteger(26, 26, nr, DEC, RGB(0,0,0), RGB(255,192,203), 1); // slecte timer gaat niet via interupt
		nr++;
    }
}

