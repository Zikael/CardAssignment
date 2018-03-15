#ifndef _LIGHTNING_H
#define _LIGHTNING_H

#include "card.h"
#include <iostream>

#include "player.h"

class CLightning: public CCard
{
	void play(CPlayer*& playerAttack, CPlayer*& playerHit, int index, bool playerControl)
	{
		//lightning attacks all card + player by 1
		if (playerHit->getSizeOfTable() > 0)
		{
			for (int i = 0; i < playerHit->getSizeOfTable(); ++i)
			{
				playerHit->getTableCard(i).setHealth(playerHit->getTableCard(i).getHealth() - playerAttack->getTableCard(index).getAttack());
				std::cout << playerAttack->getTableCard(index).getName() << " attacks " << playerHit->getTableCard(i).getName() << ". ";
				if (playerHit->getTableCard(i).getArmour()) { playerHit->getTableCard(i).setHealth(playerHit->getTableCard(i).getHealth() + 1); }
				if (playerHit->getTableCard(i).getHealth() <= 0)
				{
					//Display which card is killed
					std::cout << playerHit->getTableCard(i).getName() << " killed." << std::endl;
					//REMOVE CARD FROM DECK
					playerHit->removeTableCard(i);
				}
				else { std::cout << playerHit->getTableCard(i).getName() << "'s health is now " << playerHit->getTableCard(i).getHealth() << std::endl; }
			}
		}
		//Attack player directly
		playerHit->setHealth(playerHit->getHealth() - playerAttack->getTableCard(index).getAttack());
		//display new health levels
		if (playerControl) { std::cout << playerAttack->getTableCard(index).getName() << " attacks Sorceress. Sorceress' health is now " << playerHit->getHealth() << std::endl; }
		else { std::cout << playerAttack->getTableCard(index).getName() << " attacks Wizard. Wizard's health is now " << playerHit->getHealth() << std::endl; }

		//remove from deck
		playerAttack->removeTableCard(index);
	}
};
#endif