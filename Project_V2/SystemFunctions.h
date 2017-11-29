/* 
* SystemFunctions.h
*
* Created: 29-11-2017 11:09:18
* Author: Erwin
*/


#ifndef __SYSTEMFUNCTIONS_H__
#define __SYSTEMFUNCTIONS_H__


class SystemFunctions
{
//variables
public:
protected:
private:

//functions
public:
	static void screenBrightness();
	SystemFunctions();
	~SystemFunctions();
protected:
private:
	static int readAnalog(uint8_t pin);

	SystemFunctions( const SystemFunctions &c );
	SystemFunctions& operator=( const SystemFunctions &c );

}; //SystemFunctions

#endif //__SYSTEMFUNCTIONS_H__
