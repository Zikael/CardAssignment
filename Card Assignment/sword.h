#ifndef _SWORD_H
#define _SWORD_H

#include "card.h"
#include <iostream>

#include "player.h"

class CSword : public CCard
{
	void play(CPlayer*& playerAttack, CPlayer*& playerHit, int index, bool playerControl)
	{
		int minionType = 1;
		//look for a minion on the table
		for (int i = 0; i < playerAttack->getSizeOfTable(); ++i)
		{
			if (playerAttack->getTableCard(i).getType() == minionType)
			{
				//if a minion is found, increase it's attack by 2
				playerAttack->getTableCard(i).setAttack(playerAttack->getTableCard(i).getAttack() + 2);
				std::cout << "Sword has increased " << playerAttack->getTableCard(i).getName() << "'s attack by 2." << std::endl;
				//remove from deck
				playerAttack->removeTableCard(index);
				return;
			}
		}
		//assume no minion card found
		//increase player health by 2
		playerAttack->setHealth(playerAttack->getHealth() + 2);
		if (playerControl) { std::cout << "Sword has increased the health of the Sorceress. Sorceress' health is now " << playerHit->getHealth() << std::endl; }
		else { std::cout << "Sword has increased the health of the Wizard. Wizard's health is now " << playerHit->getHealth() << std::endl; }
		//remove from deck
		playerAttack->removeTableCard(index);
	}
};
#endif