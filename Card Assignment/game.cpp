#include "stdafx.h"
#include <iostream>
#include <fstream>

#include "game.h"
#include "types.h"

CGame::CGame()
{
	mRound = 0;
	//load the cards into the players decks
#ifdef _DEBUG
	mpSorceress->AssignFromFile("..\\Debug\\sorceress.txt");
	mpWizard->AssignFromFile("..\\Debug\\wizard.txt");
#else
	mpSorceress->AssignFromFile("sorceress.txt");
	mpWizard->AssignFromFile("wizard.txt");
#endif

	//get the mSeed
	mSeed = GetSeed();
	if (mSeed != -1) { srand(mSeed); }
	else { std::cerr << "Seed not found!"; }
}
CGame::~CGame()
{
	//delete pointers
	delete mpWizard;
	delete mpSorceress;
}

void CGame::GameManager()
{
	int gameResult = MainLoop();
	for (int i = 0; i < 3; ++i) { std::cout << std::endl; }
	if (gameResult == mGameDraw) { std::cout << std::endl << "Well played! Game drawn!" << std::endl; }
	if (gameResult == mGameWin) { std::cout << std::endl << "The Sorceress has been killed!" << std::endl; }
	if (gameResult == mGameLose) { std::cout << std::endl << "The Wizard has been killed!" << std::endl; }
	if (gameResult == mError) { std::cout << std::endl << "An error has occured!" << std::endl; }
}

int CGame::GetSeed()
{
#ifdef _DEBUG
	std::ifstream file("..\\Debug\\seed.txt");
#else
	std::ifstream file("seed.txt");
#endif
	std::string line;
	if (!file)
	{
		std::cout << "Unable to open file seed file" << std::endl;
		return -1;
	}
	std::getline(file, line);
	return std::stoi(line);
}
std::string CGame::DisplayType(int v)
{
	//switch to return the name for every type of card
	switch (v)
	{
	case 1:
		return "Basic Minion";
		break;
	case 2:
		return "Spell: Fireball";
		break;
	case 3:
		return "Spell: Lightning";
		break;
	case 4:
		return "Spell: Bless";
		break;
	case 5:
		return "Minion: Vampire";
		break;
	case 6:
		return "Minion: Wall";
		break;
	case 7:
		return "Minion: Horde";
		break;
	case 8:
		return "Minion: Trample";
		break;
	case 9:
		return "Minion: Leech";
		break;
	case 10:
		return "Equipment: Sword";
		break;
	case 11:
		return "Equipment: Armour";
		break;
	default:
		return "UNKNOWN TYPE!";
		break;
	}
}
int CGame::Random(const float n)
{
	//random function to generate a random value from 1..(n-1)
	//modified to n-1 to work correctly with arrays beginning with 0
	return static_cast<int>(static_cast<double> (rand()) / (RAND_MAX + 1) * (n + 1) - 1);
}
inline bool CGame::IsMinion(int type)
{
	//check if the card type is either a spell/equipment, if so, return false
	if (type == 2 || type == 3 || type == 4 || type == 10 || type == 11)
		return false;
	else
		return true;
}
int CGame::ControlPlayers(CPlayer*& pPlayerAttack, CPlayer*& pPlayerHit, bool playerControl)
{
	//pPlayerAttack draws card to mTable
	pPlayerAttack->SetHandCard(Random(pPlayerAttack->GetSizeOfDeck()));

	if (playerControl) std::cout << "Wizard ";
	else { std::cout << "Sorceress "; }
	std::cout << "draws " << pPlayerAttack->GetHandCard(pPlayerAttack->GetSizeOfHand() - 1).GetName() << std::endl;

	mDrawnCard = Random(pPlayerAttack->GetSizeOfHand());
	//check if the drawn card is a spell card
	if (!IsMinion(pPlayerAttack->GetHandCard(mDrawnCard).GetType()))
	{
		//if so, play the card
		if (playerControl) std::cout << "Wizard plays ";
		else { std::cout << "Sorceress plays "; }
		std::cout << pPlayerAttack->GetHandCard(mDrawnCard).GetName() << std::endl;
		pPlayerAttack->GetHandCard(mDrawnCard).Play(pPlayerAttack, pPlayerHit, mDrawnCard, playerControl);
	}
	else
	{
		//if not, add to the table
		pPlayerAttack->SetTableCard(mDrawnCard);
		if (playerControl) std::cout << "Wizard plays ";
		else { std::cout << "Sorceress plays "; }
		std::cout << pPlayerAttack->GetTableCard(pPlayerAttack->GetSizeOfTable() - 1).GetName() << std::endl;
	}
	//output cards on the table
	std::cout << "Card(s) on table: ";
	for (int i = 0; i < pPlayerAttack->GetSizeOfTable(); i++)
	{
		std::cout << pPlayerAttack->GetTableCard(i).GetName() << "(" << pPlayerAttack->GetTableCard(i).GetHealth() << ") ";
	}
	std::cout << std::endl;
	//check if the player has cards on the table
	if (pPlayerAttack->GetSizeOfTable() != 0)
	{
		//activate cards
		for (int i = 0; i < pPlayerAttack->GetSizeOfTable(); ++i)
		{
			pPlayerAttack->GetTableCard(i).Play(pPlayerAttack, pPlayerHit, i, playerControl);
			//check return condition for a win
			if (pPlayerHit->GetHealth() <= 0)
			{ 
				if (playerControl) { return mGameWin; }
				else { return mGameLose; }
			}
		}
	}
	else 
	{ 
		//output no cards to play
		if (playerControl) std::cout << "Wizard has no cards to play!" << std::endl;
		else { std::cout << "Sorcceress has no cards to play!" << std::endl; }
	}
	std::cout << std::endl;
	//return keep playing state
	return mGamePlay;
}
int CGame::MainLoop()
{
	//Header
	std::cout << "Firebrick <><" << std::endl << std::endl;

	//Shuffle the mDeck option
	
	std::cout << "Would you like to shuffle the decks?[y/n] ";
	char input = std::cin.get();
	//clear the buffer after usse
	std::cin.clear();
	std::cin.ignore();
	if (input == 'y') 
	{
		std::cout << "Shuffling cards!" << std::endl;
		int randCard;
		//generate a random number from 20 and 60
		for (int i = 0; i < 20 + Random(41); ++i)
		{
			randCard = Random(mpWizard->GetSizeOfDeck());
			mpWizard->ShuffleDeck(randCard);
			randCard = Random(mpSorceress->GetSizeOfDeck());
			mpSorceress->ShuffleDeck(randCard);
		}
	}

	//break between setup and game
	std::cout << std::endl;

	//draw Sorceress first card
	mpSorceress->SetHandCard(Random(mpSorceress->GetSizeOfDeck()));
	//mpSorceress->SetTableCard(0);
	std::cout << "Sorceress begins with " << mpSorceress->GetHandCard(0).GetName() << std::endl;

	//draw mpWizard first card
	mpWizard->SetHandCard(Random(mpWizard->GetSizeOfDeck()));
	//mpWizard->SetTableCard(0);
	std::cout << "Wizard begins with " << mpWizard->GetHandCard(0).GetName() << std::endl << std::endl;

	//game loop
	while (mPlaying)
	{
		//check exit conditions
		if (mRound >= ROUND_MAX) { return mGameDraw; }

		/* 
				STYLE GUIDE

		Round <round number>
		<Player name> draws <card name>
		Cards on mTable: <card name> (<health>)
		<card name>attacks <target>. <target> health now <health>
		Or if the target is killed:
		<card name>attacks <target>. <target> killed
		*/

		std::cout << "Round " << mRound + 1 << std::endl;

#ifdef _DEBUG
		std::cout << std::endl << "Wizard hand: " << std::endl << std::endl;
		for (int i = 0; i < mpWizard->GetSizeOfHand(); ++i)
		{
			std::cout << "Card Number: "  << i << std::endl;
			std::cout << "Card Type:	" << DisplayType(mpWizard->GetHandCard(i).GetType()) << " (" << mpWizard->GetHandCard(i).GetType() << ")" << std::endl;
			std::cout << "Card Name:	" << mpWizard->GetHandCard(i).GetName() << std::endl;
			std::cout << "Card Attack:	" << mpWizard->GetHandCard(i).GetAttack() << std::endl;
			std::cout << "Card Health:	" << mpWizard->GetHandCard(i).GetHealth() << std::endl << std::endl;
		}
		std::cout << std::endl << "Sorceress hand: " << std::endl << std::endl;
		for (int i = 0; i < mpWizard->GetSizeOfHand(); ++i)
		{
			std::cout << "Card Number: " << i << std::endl;
			std::cout << "Card Type:	" << DisplayType(mpSorceress->GetHandCard(i).GetType()) << " (" << mpSorceress->GetHandCard(i).GetType() << ")" << std::endl;
			std::cout << "Card Name:	" << mpSorceress->GetHandCard(i).GetName() << std::endl;
			std::cout << "Card Attack:	" << mpSorceress->GetHandCard(i).GetAttack() << std::endl;
			std::cout << "Card Health:	" << mpSorceress->GetHandCard(i).GetHealth() << std::endl << std::endl;
		}
#endif
		
		// ** Play cards ** \\

		if ((mGameState = ControlPlayers(mpSorceress, mpWizard, false)) != mGamePlay) { return mGameState; }
		if ((mGameState = ControlPlayers(mpWizard, mpSorceress, true)) != mGamePlay) { return mGameState; }

		//space between rounds
		std::cout << std::endl << std::endl;
		//increase round
		mRound++;
	}
}
