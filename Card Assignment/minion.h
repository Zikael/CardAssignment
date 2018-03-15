#ifndef _MINION_H
#define _MINION_H

#include "card.h"
#include <iostream>

#include "player.h"

class CMinion : public CCard
{
	void play(CPlayer*& playerAttack, CPlayer*& playerHit, int index, bool playerControl)
	{
		if (playerHit->getSizeOfTable() > 0)
		{

			int randCard = 0;
			int wallType = 6;
			for (int i = 0; i < playerHit->getSizeOfTable(); ++i)
			{
				if (playerHit->getTableCard(i).getType() == wallType)
				{
					randCard = i;
				}
				else
				{
					//Attack a random card in player1 table 
					//if the player1 has more than 1 card, randomly select a card to attack
					if (playerHit->getSizeOfTable() >= 2) { randCard = rand() % playerHit->getSizeOfTable(); }
				}
			}


			//set the health of the attacked card
			playerHit->getTableCard(randCard).setHealth(playerHit->getTableCard(randCard).getHealth() - playerAttack->getTableCard(index).getAttack());
			if (playerHit->getTableCard(randCard).getArmour()) { playerHit->getTableCard(randCard).setHealth(playerHit->getTableCard(randCard).getHealth() + 1); }
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