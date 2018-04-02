#include "stdafx.h"
#include <iostream>
#include <fstream>

#include "game.h"
#include "types.h"

CGame::CGame()
{
	mRound = 0;
	mRoundMax = 30;
}
CGame::~CGame()
{
	//delete pointers
	delete wizard;
	delete sorceress;
}

void CGame::gameManager()
{
	/*
	const int gameDraw = 0;
	const int gameWin = 1;
	const int gameLose = 2;
	*/
	int gameResult = MainLoop();
	drawLine();
	for (int i = 0; i < 8; ++i) { std::cout << std::endl; }
	if (gameResult == gameDraw) { std::cout << std::endl << "\t\t\t\tWell played! Game drawn!" << std::endl; }
	if (gameResult == gameWin) { std::cout << std::endl << "\t\t\tSorceress Defeated!" << std::endl; }
	if (gameResult == gameLose) { std::cout << std::endl << "\t\t\t\tWizard died!" << std::endl; }
	if (gameResult == error) { std::cout << std::endl << "\t\t\tAn error has occured!" << std::endl; }
	for (int i = 0; i < 10; ++i) { std::cout << std::endl; }
	drawLine();
}

int CGame::getSeed()
{
#ifdef _DEBUG
	std::ifstream file("..\\Debug\\seed.txt");
#else
	std::ifstream file("..\\Release\\seed.txt");
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
std::string CGame::displayType(int v)
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
void CGame::pressToContinue()
{
	std::cout << std::endl << "End of round " << mRound + 1 << ". Press ENTER to play next round." << std::endl;
	//wait for ENTER to be pressed
	std::cin.get();
}
void CGame::drawLine()
{
	const int screenX = 80; //size os console window
	for (int i = 0; i < screenX; i++) { std::cout << "="; }
	std::cout << std::endl;
}
int CGame::Random(const float n)
{
	//random function to generate a random value from 1..(n-1)
	//modified to n-1 to work correctly with arrays beginning with 0
	return static_cast<int>(static_cast<double> (rand()) / (RAND_MAX + 1) * (n + 1) - 1);
}
int CGame::MainLoop()
{
	//load the cards into the players decks
#ifdef _DEBUG
	sorceress->assignFromFile("..\\Debug\\sorceress.txt");
	wizard->assignFromFile("..\\Debug\\wizard.txt");
#else
	sorceress->assignFromFile("..\\Release\\sorceress.txt");
	wizard->assignFromFile("..\\Release\\wizard.txt");
#endif
	/*
	The text outputted must use the following format :
	<Name> <Program name>
	Sorceress begins with <card name>
	Wizard begins with <card name>
	*/

	//TODO use provided random function
	seed = getSeed();
	if (seed != -1) { srand(4); }
	else { return error; }
	

	//Header
	std::cout << "Michael Oliva | G20676646 | Firebrick" << std::endl << std::endl;

	//draw Sorceress first card
	sorceress->setHandCard(Random(sorceress->getSizeOfDeck()));
	sorceress->setTableCard(0);
	std::cout << "Sorceress begins with " << sorceress->getTableCard(0).getName() << std::endl;

	//draw wizard first card
	wizard->setHandCard(Random(wizard->getSizeOfDeck()));
	wizard->setTableCard(0);
	std::cout << "Wizard begins with " << wizard->getTableCard(0).getName() << std::endl << std::endl;

	//add card to hand 2 there is always 2 to choose from
	sorceress->setHandCard(Random(sorceress->getSizeOfDeck()));
	wizard->setHandCard(Random(wizard->getSizeOfDeck()));


	//game loop
	while (playing)
	{
		//check exit conditions
		if (mRound >= mRoundMax) { return gameDraw; }

		/* 
				STYLE GUIDE

		Round <round number>
		<Player name> draws <card name>
		Cards on table: <card name> (<health>)
		<card name>attacks <target>. <target> health now <health>
		Or if the target is killed:
		<card name>attacks <target>. <target> killed
		*/

		//Add a random card to each players hand
		sorceress->setHandCard(Random(sorceress->getSizeOfDeck()));
		wizard->setHandCard(Random(wizard->getSizeOfDeck()));


		std::cout << "Round " << mRound + 1 << std::endl;

#ifdef _DEBUG
		std::cout << std::endl << "Wizard hand: " << std::endl << std::endl;
		for (int i = 0; i < wizard->getSizeOfHand(); i++)
		{
			std::cout << "Card Number: "  << i << std::endl;
			std::cout << "Card Type:	" << displayType(wizard->getHandCard(i).getType()) << " (" << wizard->getHandCard(i).getType() << ")" << std::endl;
			std::cout << "Card Name:	" << wizard->getHandCard(i).getName() << std::endl;
			std::cout << "Card Attack:	" << wizard->getHandCard(i).getAttack() << std::endl;
			std::cout << "Card Health:	" << wizard->getHandCard(i).getHealth() << std::endl << std::endl;
		}
		std::cout << std::endl << "Sorceress hand: " << std::endl << std::endl;
		for (int i = 0; i < wizard->getSizeOfHand(); i++)
		{
			std::cout << "Card Number: " << i << std::endl;
			std::cout << "Card Type:	" << displayType(sorceress->getHandCard(i).getType()) << " (" << sorceress->getHandCard(i).getType() << ")" << std::endl;
			std::cout << "Card Name:	" << sorceress->getHandCard(i).getName() << std::endl;
			std::cout << "Card Attack:	" << sorceress->getHandCard(i).getAttack() << std::endl;
			std::cout << "Card Health:	" << sorceress->getHandCard(i).getHealth() << std::endl << std::endl;
		}
#endif

		//TODO: play spell cards

		//sorceress draws card to table
		sorceress->setTableCard(Random(sorceress->getSizeOfHand()));
		std::cout << "Sorceress draws " << sorceress->getTableCard(sorceress->getSizeOfTable()-1).getName() << std::endl;

		//wizard draws a card to the table
		wizard->setTableCard(Random(wizard->getSizeOfHand()));
		std::cout << "Wizard draws " << wizard->getTableCard(wizard->getSizeOfTable()-1).getName() << std::endl;

		// ** SORCERESS PLAY ** \\

		std::cout << "Card(s) on table: ";
		for (int i = 0; i < sorceress->getSizeOfTable(); i++)
		{
			std::cout << sorceress->getTableCard(i).getName() << "(" << sorceress->getTableCard(i).getHealth() << ") ";
		}
		std::cout << std::endl;
		if (sorceress->getSizeOfTable() != 0)
		{
			for (int i = 0; i < sorceress->getSizeOfTable(); ++i)
			{
				sorceress->getTableCard(i).play(sorceress, wizard, i, false);
				//check return condition for a win
				if (wizard->getHealth() <= 0) { return gameLose; }
			}
		}
		else { std::cout << "Sorcceress has no cards to play!" << std::endl; }
		std::cout << std::endl;

		// ** WIZARD PLAY ** \\

		std::cout << "Card(s) on table: ";
		for (int i = 0; i < wizard->getSizeOfTable(); ++i)
		{
			std::cout << wizard->getTableCard(i).getName() << "(" << wizard->getTableCard(i).getHealth() << ") ";
		}
		std::cout << std::endl;

		//ATTACK SORCERESS
		if (wizard->getSizeOfTable() != 0)
		{
			for (int i = 0; i < wizard->getSizeOfTable(); ++i)
			{
				wizard->getTableCard(i).play(wizard, sorceress, i, true);
				//check return condition for a win
				if (sorceress->getHealth() <= 0) { return gameWin; }
			}
		} else { std::cout << "Wizard has no cards to play!" << std::endl; }

		//end of round wait
		pressToContinue();
		drawLine();
		//increase round
		mRound++;
	}
}