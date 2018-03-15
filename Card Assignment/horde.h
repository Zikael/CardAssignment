#ifndef _HORDE_H
#define _HORDE_H

#include <iostream>
#include "card.h"
#include "player.h"

class CHorde : public CCard
{
	void play(CPlayer*& playerAttack, CPlayer*& playerHit, int index, bool playerControl)
	{
		//set attack of horde to 0 initally
		playerAttack->getTableCard(index).setAttack(0);

		//search the table vector for every instance of a horde type card
		//increase the attack of the current card by 1 for every other horde card
		int hordeType = 7;
		for (int i = 0; i < playerAttack->getSizeOfTable(); ++i)
		{
			if (playerAttack->getTableCard(i).getType() == hordeType)
			{
				playerAttack->getTableCard(index).setAttack(playerAttack->getTableCard(index).getAttack()+1);
			}
		}
		if (playerHit->getSizeOfTable() > 0)
		{
			//Attack a random card in player1 table 
			int randCard = 0;
			//if the player1 has more than 1 card, randomly select a card to attack
			if (playerHit->getSizeOfTable() >= 2) { randCard = rand() % playerHit->getSizeOfTable(); }

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

