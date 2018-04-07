#ifndef _GAME_H
#define _GAME_H

#include "player.h"

class CGame
{
private:
	//pointers for players
	CPlayer* mpWizard = new CPlayer;
	CPlayer* mpSorceress = new CPlayer;

	int mRound;					//round counter
	const int ROUND_MAX = 30;	//max rounds (defined as 30)
	bool mPlaying = true;		//control main game loop
	int mSeed;					//mSeed for random function
	int mDrawnCard;				//card number that has been randomly drawn

	//flags to check the state of the game
	int mGameState;
	const int mGamePlay = 10;	//keep playing
	const int mGameDraw = 0;	//both alive after 30 rounds
	const int mGameWin = 1;		//wizard wins
	const int mGameLose = 2;	//sorceress wins
	const int mError = -1;		//internal error
public:
	CGame();					
	~CGame();

	//getters
	int GetSeed();						//returns a mSeed from the file

	//functions
	int ControlPlayers(CPlayer*& pPlayerAttack, CPlayer*& pPlayerHit, bool playerControl);
	inline bool IsMinion(int i);				//check if the card is a minino -- used to see if it can be place on the table
	void GameManager();					//manager for the logic loop, handles win/lose/draw
	int MainLoop();						//Game logic loop
	std::string DisplayType(int v);		//display type
	void PressToContinue();				//delay before next round starts
	inline void DrawLine();				//draw a line between rounds to help stand out
	int Random(const float n);			//return a random value
};

#endif