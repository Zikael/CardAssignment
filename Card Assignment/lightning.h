#ifndef _LIGHTNING_H
#define _LIGHTNING_H

#include "card.h"
#include <iostream>

#include "player.h"

class CLightning: public CCard
{
	void Play(CPlayer*& playerAttack, CPlayer*& playerHit, int index, bool playerControl)
	{
		//lightning attacks all card + player by 1
		if (playerHit->GetSizeOfTable() > 0)
		{
			//TODO: fix non attacking player if previous one is killed.
			for (int i = 0; i < playerHit->GetSizeOfTable(); ++i)
			{
				playerHit->GetTableCard(i).SetHealth(playerHit->GetTableCard(i).GetHealth() - playerAttack->GetHandCard(index).GetAttack());
				std::cout << playerAttack->GetHandCard(index).GetName() << " attacks " << playerHit->GetTableCard(i).GetName() << ". ";
				if (playerHit->GetTableCard(i).GetArmour()) { playerHit->GetTableCard(i).SetHealth(playerHit->GetTableCard(i).GetHealth() + 1); }
				if (playerHit->GetTableCard(i).GetHealth() <= 0)
				{
					//Display which card is killed
					std::cout << playerHit->GetTableCard(i).GetName() << " killed." << std::endl;
					//flag to remove
					playerHit->GetTableCard(i).SetRemove(true);
				}
				else { std::cout << playerHit->GetTableCard(i).GetName() << "'s health is now " << playerHit->GetTableCard(i).GetHealth() << std::endl; }
			}
		}
		//Attack player directly
		playerHit->SetHealth(playerHit->GetHealth() - playerAttack->GetHandCard(index).GetAttack());
		//display new health levels
		if (playerControl) { std::cout << playerAttack->GetHandCard(index).GetName() << " attacks Sorceress. Sorceress' health is now " << playerHit->GetHealth() << std::endl; }
		else { std::cout << playerAttack->GetHandCard(index).GetName() << " attacks Wizard. Wizard's health is now " << playerHit->GetHealth() << std::endl; }
		for (int i = 0; i < playerHit->GetSizeOfTable(); ++i)
		{
			//REMOVE CARD FROM DECK
			if (playerHit->GetTableCard(i).GetRemove()) 
			{
				playerHit->RemoveTableCard(i); 
				i = 0; //restart to loop.
			}
		}
		//remove from mHand
		playerAttack->RemoveHandCard(index);
	}
};
#endif