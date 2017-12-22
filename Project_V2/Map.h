/* 
 * Map.h
 *
 * Authors:
 *			Erwin
 *			Wesley
 */

#include "Bomb.h"


#ifndef __MAP_H__
#define __MAP_H__
#define BLOCK_SIZE 20
#define COLOUR_PILLAR RGB(51, 49, 49)
#define COLOUR_ROAD RGB(91,90,90) 
#define COLOUR_DESTROYABLE RGB(64,16,10)
#define COLOUR_GRID RGB(0,0,0)

class Map
{
public:
	Map(MI0283QT9 *lcdPointer, Bomb *bombPointer);
	//Map();
	~Map();
	
	void drawMap();
	void genBlocks(float difficulty);
	void updateChunk(uint8_t loc);
	void updateLevel(uint8_t loc, uint8_t value);
	uint8_t checkLocation(uint8_t location);
protected:
private:
	Map( const Map &c );
	Map& operator=( const Map &c );
	MI0283QT9 *lcdPointer;
	Bomb *bombPointer;
	
	// array level is used to generate a random level
	uint8_t level[143];
}; //Map

#endif //__MAP_H__
