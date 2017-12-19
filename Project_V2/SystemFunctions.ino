/*
 * SystemFunctions.ino
 *
 * Authors: 
 *			Erwin
 *			Wesley
 */



// variables
volatile uint32_t seed;	//values needed for random numbers
volatile int8_t nrot;

/*
* wat doet dit?
* input: 
* returns: 
*/
ISR(WDT_vect)
{
	nrot--;
	seed = seed << 8;
	seed = seed ^ TCNT1L;
}

/*
* Public Functions
*/

/*
* Function to determine the screenbrightness.
*/
void SystemFunctions::screenBrightness()
{
	
	OCR1A = readAnalog(0);		//Save ADC value from A0 in OCR1A to change LCD brightness
	
}

/*
* returns a random integer
*/
uint32_t SystemFunctions::getRandomSeed()
{
	SystemFunctions::createRandomSeed(); // calls createRandomseed to generate random value
	return seed;
}

/*
* Function to read the nunchuck
* returns: value between 0 and 5 for each function
*/
uint8_t SystemFunctions::readNunchuck()
{
	uint8_t result = 0, i = 0;		//variables for function
	uint8_t buffer[6];				//buffer to store data received from nunchuck

	Wire.requestFrom (0x52, 6);		// request data from nunchuck
	while (Wire.available ()) {		// Receive all data
									
		buffer[i] = decodeNunchuck(Wire.read());	// receive and decode byte as an integer
		i++;
	}
	
	sendRequest();					// send data request
	
	if (buffer[1]>200)				// determine different movements
	result = UP;					// buffer[1] contains X data about the joystick
	else if (buffer[1]<50)			// buffer[0] contains Y data about the joystick
	result = DOWN;					// buffer[5] contains data about the Z-button
	else if (buffer[0]> 200)
	result = RIGHT;
	else if (buffer[0] < 50)
	result = LEFT;
	else if (!((buffer[5] >> 0) & 1))
	result = SELECT;				// Z-button

	return result;					// return result
}

/*
* Function to determine X location in pixels
* input: integer with arraylocation
* returns: integer with pixel location
*/
uint8_t SystemFunctions::calcX(uint8_t loc)
{
	return loc%13*GRID;		
}

/*
* Function to determine Y location in pixels
* input: integer with arraylocation
* returns: integer with pixel location
*/
uint8_t SystemFunctions::calcY(uint8_t loc)
{
	return loc/13*GRID;
}

/*
* This function reads the EEPROM and returns a 3 character long name
* input: ranking in list
* returns: 3 character long string
*/
char* SystemFunctions::readName(uint8_t place)
{
	char *result = calloc(4, sizeof(char));
	uint8_t i;				// declaration of needed variables

	
	place = (place*10)-10;	// determine memory location
	
	for	(i=0; i<=2; i++)	// read the 3 characters
	{
		result[i] = (char)eeprom_read_byte((uint8_t*)place+i+1); // save the characters in array
	}
	
	result [4] = NULL;		//end 0
	
	return result;			//return the array
	free(&result);
	
}

/*
* This function reads the EEPROM and returns a 5 character long score
* input: ranking in list
* returns: 5 character long string
*/
char* SystemFunctions::printScore(uint8_t place)
{
	
	char *result = calloc(6, sizeof(char));
	uint16_t i;				// declaration of needed variables
	
	place = (place*10)-7;	// determine memory location
	
	i = (eeprom_read_byte((uint8_t*)place+1)<<8)|(eeprom_read_byte((uint8_t*)place+2)); // combine 2 8bit-bytes into 1 16 bit-byte

	result[0] = (char)(i/10000) + 48;	//turn integer into string
	i = i%10000;
	result[1] = (char)(i/1000)	+ 48;
	i = i%1000;
	result[2] = (char)(i/100)	+ 48;
	i = i%100;
	result[3] =	(char)(i/10)	+ 48;
	i = i%10;
	result[4] = (char) i + 48;
	result[5] = NULL;					//end 0

	
	return result;			//return the array
	free(&result);
}

uint16_t SystemFunctions::readScore(uint8_t place)
{
	
		uint16_t result;				// declaration of needed variables
	
	place = (place*10)-7;	// determine memory location
	
	result = (eeprom_read_byte((uint8_t*)place+1)<<8)|(eeprom_read_byte((uint8_t*)place+2)); // combine 2 8bit-bytes into 1 16 bit-byte

	
	return result;			//return the array
	free(&result);
	
}

void SystemFunctions::scoreToEEPROM(uint8_t score, uint8_t place)
{
	uint8_t a, b;
	place = (place*10)-7;
	a = (score>>8);
	b = score;
	eeprom_write_byte((uint8_t*)place+1, a);
	eeprom_busy_wait();
	eeprom_write_byte((uint8_t*)place+2, b);
	eeprom_busy_wait();
}

// default constructor
SystemFunctions::SystemFunctions()
{
} //SystemFunctions

// default destructor
SystemFunctions::~SystemFunctions()
{
} //~SystemFunctions

/*
* Reads value of analog input
* input: pin number between 0 and 5 corresponding with A0 ... A5
* returns: integer with value
*/
int SystemFunctions::readAnalog(uint8_t pin)
{
	if (pin<6)							//Check if pin exists.
	{
		ADMUX = 0x40;					//Declare Reference
		ADMUX |= pin;					//Define pin
		

		ADCSRA |= (1<<ADSC);        	//Single AD-conversion
		
		while (ADCSRA & (1<<ADSC)); 	//Wait for result
		
		return ADC;						// return value
	} else
	return 0;							//Error value
}

/*
* function to create random value for blok placement
*/
void SystemFunctions::createRandomSeed()
{
	seed = 0;
	nrot = 32; // Must be at least 4, but more increased the uniformity of the produced
	// seeds entropy.
	// The following five lines of code turn on the watch dog timer interrupt to create
	// the seed value
	cli();
	MCUSR = 0;
	_WD_CONTROL_REG |= (1<<_WD_CHANGE_BIT) | (1<<WDE);
	_WD_CONTROL_REG = (1<<WDIE);
	sei();

	while (nrot > 0); // wait here until seed is created

	// The following five lines turn off the watch dog timer interrupt
	cli();
	MCUSR = 0;
	_WD_CONTROL_REG |= (1<<_WD_CHANGE_BIT) | (0<<WDE);
	_WD_CONTROL_REG = (0<< WDIE);
	sei();
}

/*
* Decode data received from nunchuck
* input: integer from nunchuck
* returns: decoded integer 
*/
uint8_t SystemFunctions::decodeNunchuck(uint8_t data)
{
	data = (data ^ 0x17) + 0x17;		//decode data
	return data;						// return data
}

/*
* Send data request from nunchuck
*/
void SystemFunctions::sendRequest()
{
	Wire.beginTransmission(NUNCHUCKADRESS);   // transmit to Nunchcuk adress
	Wire.write(0x00);
	Wire.endTransmission();
}