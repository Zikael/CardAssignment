#ifndef _GAME_H
#define _GAME_H

#include "player.h"

class CGame
{
private:
	//pointers for players
	CPlayer* wizard = new CPlayer;
	CPlayer* sorceress = new CPlayer;
	//round counter
	int mRound;
	//max rounds (defined as 30)
	int mMAX_ROUND;
	bool playing = true;

	const int gameDraw = 0;
	const int gameWin = 1;
	const int gameLose = 2;

public:
	CGame();
	~CGame();

	//setters
	//set number of rounds
	void setRounds(int v);

	//getters

	//returns a seed from the file
	int getSeed();
	//return number of rounds
	int getRounds();

	//manager for the logic loop, handles win/lose/draw
	void gameManager();
	//Game logic loop
	int MainLoop();
	//display type
	std::string displayType(int v);
	//delay before enxt round starts
	void pressToContinue();
	//draw a line between rounds to help stand out
	inline void drawLine();
	//select valid card function
	int playCard();
};

#endif