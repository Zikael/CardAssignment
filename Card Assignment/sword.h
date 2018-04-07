#ifndef _SWORD_H
#define _SWORD_H

#include "card.h"
#include <iostream>

#include "player.h"

class CSword : public CCard
{
	void Play(CPlayer*& playerAttack, CPlayer*& playerHit, int index, bool playerControl)
	{
		int minionType = 1;
		//look for a minion on the mTable
		for (int i = 0; i < playerAttack->GetSizeOfTable(); ++i)
		{
			if (playerAttack->GetTableCard(i).GetType() == minionType)
			{
				//if a minion is found, increase it's attack by 2
				playerAttack->GetTableCard(i).SetAttack(playerAttack->GetTableCard(i).GetAttack() + 2);
				std::cout << "Sword has increased " << playerAttack->GetTableCard(i).GetName() << "'s attack by 2." << std::endl;
				//remove from mHand
				playerAttack->RemoveHandCard(index);
				return;
			}
		}
		//assume no minion card found
		//increase player health by 2
		playerAttack->SetHealth(playerAttack->GetHealth() + 2);
		if (playerControl) { std::cout << "Sword has increased the health of the Sorceress. Sorceress' health is now " << playerHit->GetHealth() << std::endl; }
		else { std::cout << "Sword has increased the health of the Wizard. Wizard's health is now " << playerHit->GetHealth() << std::endl; }
		//remove from mHand
		playerAttack->RemoveHandCard(index);
	}
};
#endif