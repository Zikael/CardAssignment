#include "stdafx.h"
#include "game.h"
#include <iostream>
#include <ctime>


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
	if (gameResult == gameDraw) { std::cout << std::endl << "Well played! Game drawn!" << std::endl; }
	if (gameResult == gameWin) { std::cout << std::endl << "Sorceress Defeated! You win!" << std::endl; }
	if (gameResult == gameLose) { std::cout << std::endl << "You died! Game over." << std::endl; }
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
	sorceress->assignFromFile("..\\Debug\\sorceress.txt");
	wizard->assignFromFile("..\\Debug\\wizard.txt");

	/*
	The text outputted must use the following format :
	<Name> <Program name>
	Sorceress begins with <card name>
	Wizard begins with <card name>
	*/

	//TODO implement random feature using seed file instead
	srand(time(NULL));

	//Header
	std::cout << "Michael Oliva | Hearthpebble" << std::endl;

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
		if (mRound >= 30) { return gameDraw; }
		if (wizard->getHealth() <= 0) { return gameLose; }

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

		std::cout << "Wizard draws " << wizard->getTableCard(wizard->getSizeOfTable()-1).getName()
			<< " (" << wizard->getTableCard(wizard->getSizeOfTable()-1).getHealth() << " hp)" << std::endl;
		std::cout << "Card on table: " << std::endl;
		for (int i = 0; i < wizard->getSizeOfTable(); i++)
		{
			std::cout << wizard->getTableCard(i).getName() << "	" << wizard->getTableCard(i).getHealth() 
				<< " (" << wizard->getTableCard(i).getHealth() << " hp)" << std::endl;
		}
		std::cout << std::endl;

		//ATTACK SORCERESS
		for (int i = 0; i < wizard->getSizeOfTable(); i++)
		{
			if (wizard->getTableCard(i).getType() == 1)
			{
				if (sorceress->getSizeOfTable() > 0)
				{
					//Attack a random card in sorceress table 
					int randCard = 0;
					if (sorceress->getSizeOfTable() >= 2) { int randCard = rand() % sorceress->getSizeOfTable(); }
					//sorceress->getTableCard(randCard).getHealth() - wizard->getTableCard(i).getAttack()
					//set the health of the attacked card
					sorceress->getTableCard(randCard).setHealth(-1);
					std::cout << wizard->getTableCard(i).getName() << " attacks " << sorceress->getTableCard(randCard).getName() << ". ";
					if (sorceress->getTableCard(randCard).getHealth() <= 0)
					{
						//REMOVE CARD FROM DECK
						std::cout << sorceress->getTableCard(randCard).getName() << " killed." << std::endl;
					}
					else { std::cout << sorceress->getTableCard(randCard).getName() << "'s health is now " << sorceress->getTableCard(randCard).getHealth() << std::endl; }
				}
				else
				{
					//Attack sorceress directly
					sorceress->setHealth(sorceress->getHealth() - wizard->getTableCard(i).getAttack());
					std::cout << wizard->getTableCard(i).getName() << " attacks Sorceress. Sorceress health is now " << sorceress->getHealth() << std::endl;;
					//check return condition for a win
					if (sorceress->getHealth() <= 0) { return gameWin; }
				}
			}
		}

		//end of round wait
		pressToContinue();
		drawLine();
		//increase round
		mRound++;
	}
}