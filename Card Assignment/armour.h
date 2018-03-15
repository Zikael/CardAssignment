#ifndef _ARMOUR_H
#define _ARMOUR_H

#include "card.h"
#include <iostream>

#include "player.h"

class CArmour : public CCard
{
	void play(CPlayer*& playerAttack, CPlayer*& playerHit, int index, bool playerControl)
	{
		int minionType = 1;
		//look for a minion on the table
		for (int i = 0; i < playerAttack->getSizeOfTable(); ++i)
		{
			if (playerAttack->getTableCard(i).getType() == minionType)
			{
				//if a minion is found, set armour flag to true
				playerAttack->getTableCard(i).setArmour(true);
				std::cout << "Armour has been given to " << playerAttack->getTableCard(i).getName() << "." << std::endl;
				//remove from deck
				playerAttack->removeTableCard(index);
				return;
			}
		}
		std::cout << "No targets for armour to be applied to!" << std::endl;
		//remove from deck
		playerAttack->removeTableCard(index);
	}
};
#endif