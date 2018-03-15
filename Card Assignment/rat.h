#ifndef _RAT_H
#define _RAT_H

#include <iostream>
#include "card.h"
#include "player.h"

class CRat: public CCard
{
	void play(CPlayer*& playerAttack, CPlayer*& playerHit, int index, bool playerControl)
	{
		//set attack of rat to 0 initally
		playerAttack->getTableCard(index).setAttack(0);

		int ratType = 
		for (int i = 0; i < playerAttack->getSizeOfTable(); ++i)
		{
			if ()
		}
		if (playerHit->getSizeOfTable() > 0)
		{
			//TODO: make damage perminant

			//Attack a random card in player1 table 
			int randCard = 0;
			//if the player1 has more than 1 card, randomly select a card to attack
			if (playerHit->getSizeOfTable() >= 2) { randCard = rand() % playerHit->getSizeOfTable(); }

			//set the health of the attacked card
			playerHit->getTableCard(randCard).setHealth(playerHit->getTableCard(randCard).getHealth() - playerAttack->getTableCard(index).getAttack());
			std::cout << playerAttack->getTableCard(index).getName() << " attacks " << playerHit->getTableCard(randCard).getName() << ". ";
			if (playerHit->getTableCard(randCard).getHealth() <= 0)
			{
				//Display which card is killed
				std::cout << playerHit->getTableCard(randCard).getName() << " killed." << std::endl;
				//REMOVE CARD FROM DECK
				playerHit->removeTableCard(randCard);
			}
			else { std::cout << playerHit->getTableCard(randCard).getName() << "'s health is now " << playerHit->getTableCard(randCard).getHealth() << std::endl; }
		}
		else
		{
			//Attack player directly
			playerHit->setHealth(playerHit->getHealth() - playerAttack->getTableCard(index).getAttack());
			//display new health levels
			if (playerControl) { std::cout << playerAttack->getTableCard(index).getName() << " attacks Sorceress. Sorceress' health is now " << playerHit->getHealth() << std::endl; }
			else { std::cout << playerAttack->getTableCard(index).getName() << " attacks Wizard. Wizard's health is now " << playerHit->getHealth() << std::endl; }
		}
	}
};

#endif
