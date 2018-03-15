#include "stdafx.h"
#include <iostream>
#include <fstream>

#include "game.h"
#include "types.h"

CGame::CGame()
{
	mRound = 0;
	mMAX_ROUND = 30;
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
	if (gameResult == gameWin) { std::cout << std::endl << "\t\t\tSorceress Defeated! You win!" << std::endl; }
	if (gameResult == gameLose) { std::cout << std::endl << "\t\t\t\tYou died! Game over." << std::endl; }
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
int CGame::playCard()
{
	bool validInput = false;
	int cardNum;
	while (!validInput)
	{
		std::cout << "Select a card number to play: ";
		std::cin >> cardNum;
		if (cardNum >= 0 && cardNum < wizard->getSizeOfHand()) { validInput = true; }
		else
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout << std::endl << "Please select a card number between 0 and " << wizard->getSizeOfHand() -1 << "." << std::endl;
		}
	}
	std::cin.clear();
	std::cin.ignore();
	std::cout << std::endl;
	return cardNum;
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
	srand(getSeed());

	//Header
	std::cout << "Michael Oliva | Hearthpebble" << std::endl << std::endl;

	//draw Sorceress first card
	sorceress->setHandCard(rand() % sorceress->getSizeOfDeck());
	std::cout << "Sorceress begins with card: " << sorceress->getHandCard(0).getName() << std::endl;

	//draw wizard first card
	wizard->setHandCard(rand() % wizard->getSizeOfDeck());
	std::cout << "Wizard begins with card: " << wizard->getHandCard(0).getName() << std::endl;

	//game loop
	while (playing)
	{
		//check exit conditions
		if (mRound >= mMAX_ROUND) { return gameDraw; }

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
		sorceress->setHandCard(rand() % sorceress->getSizeOfDeck());
		wizard->setHandCard(rand() % wizard->getSizeOfDeck());


		std::cout << "Round: " << mRound + 1 << " begins." << std::endl;
		std::cout << std::endl << "Your hand: " << std::endl << std::endl;
		for (int i = 0; i < wizard->getSizeOfHand(); i++)
		{
			std::cout << "Card Number: "  << i << std::endl;
			std::cout << "Card Type:	" << displayType(wizard->getHandCard(i).getType()) << " (" << wizard->getHandCard(i).getType() << ")" << std::endl;
			std::cout << "Card Name:	" << wizard->getHandCard(i).getName() << std::endl;
			std::cout << "Card Attack:	" << wizard->getHandCard(i).getAttack() << std::endl;
			std::cout << "Card Health:	" << wizard->getHandCard(i).getHealth() << std::endl << std::endl;
		}
		//Players draws a card to the table
		wizard->setTableCard(playCard());
		//sorceress draws card to table
		sorceress->setTableCard(rand() % sorceress->getSizeOfHand());

		std::cout << "Wizard draws " << wizard->getTableCard(0).getName()
			<< " (" << wizard->getTableCard(0).getHealth() << " hp)" << std::endl;
		std::cout << "Card(s) on table: " << std::endl;
		for (int i = 0; i < wizard->getSizeOfTable(); i++)
		{
			std::cout << wizard->getTableCard(i).getName() << "	" << wizard->getTableCard(i).getHealth() 
				<< " (" << wizard->getTableCard(i).getHealth() << " hp)" << std::endl;
		}
		std::cout << std::endl;

		//ATTACK SORCERESS
		std::cout << "Your play: " << std::endl;
		for (int i = 0; i < wizard->getSizeOfTable(); ++i)
		{
			wizard->getTableCard(i).play(wizard, sorceress, i, true);
			//check return condition for a win
			if (sorceress->getHealth() <= 0) { return gameWin; }
		}

		std::cout << std::endl << "Sorcceress' play: " << std::endl;
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


#ifdef _DEBUG
		std::cout << std::endl << std::endl << "Sorceress cards: " << std::endl;
		for (int i = 0; i < sorceress->getSizeOfTable(); ++i)
		{
			std::cout << sorceress->getTableCard(i).getName() << std::endl;
		}
#endif

		//end of round wait
		pressToContinue();
		drawLine();
		//increase round
		mRound++;
	}
}