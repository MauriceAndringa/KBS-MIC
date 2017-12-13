/*
* Highscore.h
*
* Created: 8-12-2017
* Author: Erwin Jacobs
*/


#ifndef _HIGHSCORE_H__
#define _HIGHSCORE_H__

#include <MI0283QT9.h>


class Highscore
{
//variables
public:
protected:
private:
	MI0283QT9	*lcdPointer;
	View		*currentViewPointer;
	View		*requestedViewPointer;

//functions
 public:
	Highscore(MI0283QT9 *lcdPointer, View *currentViewPointer, View *requestedViewPointer);
	~Highscore();
	
	void draw();
  protected:
  private:
  char* Highscore::readName(uint8_t place);
};

#endif _HIGHSCORE_H__
