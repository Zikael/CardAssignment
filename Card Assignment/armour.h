#ifndef _ARMOUR_H
#define _ARMOUR_H

#include "card.h"
#include <iostream>

#include "player.h"

class CArmour : public CCard
{
	void Play(CPlayer*& playerAttack, CPlayer*& playerHit, int index, bool playerControl)
	{
		int minionType = 1;
		//look for a minion on the mTable
		for (int i = 0; i < playerAttack->GetSizeOfTable(); ++i)
		{
			if (playerAttack->GetTableCard(i).GetType() == minionType)
			{
				//if a minion is found, set armour flag to true
				playerAttack->GetTableCard(i).SetArmour(true);
				std::cout << "Armour has been given to " << playerAttack->GetTableCard(i).GetName() << "." << std::endl;
				//remove from mHand
				playerAttack->RemoveHandCard(index);
				return;
			}
		}
		std::cout << "No target for armour to be applied to!" << std::endl;
		//remove from mHand
		playerAttack->RemoveHandCard(index);
	}
};
#endif