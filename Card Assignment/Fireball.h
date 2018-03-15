#ifndef _FIREBALL_H
#define _FIREBALL_H

#include "card.h"
#include <iostream>

#include "player.h"

class CFireball : public CCard
{
	void play(CPlayer*& playerAttack, CPlayer*& playerHit, int index, bool playerControl)
	{
		//print out all the card on enemies table & summoner
		int cardNum = 0;
		if (playerControl)
		{
			int i;
			for (i = 0; i < playerHit->getSizeOfTable(); ++i)
			{
				std::cout << i << ": " << playerHit->getTableCard(i).getName() << " (" << playerHit->getTableCard(i).getHealth() << " hp)." << std::endl;
			}
			std::cout << i << ": Summoner." << std::endl;

			//validate input
			bool validInput = false;
			while (!validInput)
			{
				std::cout << "Choose target for " << playerAttack->getTableCard(index).getName() << " to attack: ";
				std::cin >> cardNum;
				if (cardNum >= 0 && cardNum <= i) { validInput = true; }
				else
				{
					std::cin.clear();
					std::cin.ignore();
					std::cout << std::endl << "Please select a card number between 0 and " << i << "." << std::endl;
				}
			}
			std::cin.clear();
			std::cin.ignore();
			std::cout << std::endl;
		}
		else { if (cardNum != 0) {cardNum = rand() % playerHit->getSizeOfTable(); } } //determine a card to hit for the AI

		if (cardNum == playerHit->getSizeOfTable())
		{
			//attack summoner
			playerHit->setHealth(playerHit->getHealth() - playerAttack->getTableCard(index).getAttack());
			if (playerControl) { std::cout << playerAttack->getTableCard(index).getName() << " attacks Sorceress. Sorceress' health is now " << playerHit->getHealth() << std::endl; }
			else { std::cout << playerAttack->getTableCard(index).getName() << " attacks Wizard. Wizard's health is now " << playerHit->getHealth() << std::endl; }
		}
		else
		{
			playerHit->getTableCard(cardNum).setHealth(playerHit->getTableCard(cardNum).getHealth() - playerAttack->getTableCard(index).getAttack());
			std::cout << playerAttack->getTableCard(index).getName() << " attacks " << playerHit->getTableCard(cardNum).getName() << ". ";
			if (playerHit->getTableCard(cardNum).getHealth() <= 0)
			{
				//Display which card is killed
				std::cout << playerHit->getTableCard(cardNum).getName() << " killed." << std::endl;
				//REMOVE CARD FROM DECK
				playerHit->removeTableCard(cardNum);
			}
			else { std::cout << playerHit->getTableCard(cardNum).getName() << "'s health is now " << playerHit->getTableCard(cardNum).getHealth() << std::endl; }
		}

		//remove from deck
		playerAttack->removeTableCard(index);
	}
};
#endif