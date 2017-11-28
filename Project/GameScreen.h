/* 
* GameScreen.h
*
* Created: 21-11-2017 14:45:32
* Author: wsvdy
*/


#ifndef __GAMESCREEN_H__
#define __GAMESCREEN_H__


class GameScreen
{
//variables
public:
protected:
private:

	int playerLoc[2][2] = {{0,0},{320,240}};
	/*uint8_t baseMap[143] = {
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
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	};
*/	
	uint8_t map[143] = {
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
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	};
	
//functions
public:
	GameScreen();
	~GameScreen();
	void terug(); //TODO vertalen naar het engels
	void drawScreen(float level);
protected:
private:
	GameScreen( const GameScreen &c );
	GameScreen& operator=( const GameScreen &c );
	void genValue(float level);
	

}; //GameScreen

#endif //__GAMESCREEN_H__
