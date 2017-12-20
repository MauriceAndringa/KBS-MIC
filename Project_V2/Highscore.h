/*
 * Highscore.h
 *
 * Authors:
 *			Erwin
 *			Wesley
 */


#ifndef _HIGHSCORE_H__
#define _HIGHSCORE_H__

#include <MI0283QT9.h>


class Highscore
{
 public:
	Highscore(MI0283QT9 *lcdPointer, View *requestedViewPointer);
	~Highscore();
	
	void draw();
	void listenToTouchInput();
  protected:
  private:
	MI0283QT9	*lcdPointer;
	View		*requestedViewPointer;
};

#endif _HIGHSCORE_H__
