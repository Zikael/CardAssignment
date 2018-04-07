#ifndef _BLESS_H
#define _BLESS_H

#include "card.h"
#include <iostream>

#include "player.h"

class CBless : public CCard
{
	void Play(CPlayer*& playerAttack, CPlayer*& playerHit, int index, bool playerControl)
	{

		int randChoice = rand() % 4;
		if (randChoice == 0)
		{
			//enemy minions
			int randCard = 0;
			if (playerHit->GetSizeOfTable() != 0) { randCard = rand() % playerHit->GetSizeOfTable(); }
			else 
			{ 
				std::cout << "No cards for Bless to attack." << std::endl;
				return;
			}
			playerHit->GetTableCard(randCard).SetHealth(playerHit->GetTableCard(randCard).GetHealth() - playerAttack->GetHandCard(index).GetAttack());
			if (playerHit->GetTableCard(randCard).GetArmour()) { playerHit->GetTableCard(randCard).SetHealth(playerHit->GetTableCard(randCard).GetHealth() + 1); }
			std::cout << playerAttack->GetHandCard(index).GetName() << " attacks " << playerHit->GetTableCard(randCard).GetName() << ". "
				<< playerHit->GetTableCard(randCard).GetName() << "'s health is now " << playerHit->GetTableCard(randCard).GetHealth() << std::endl;
		}
		else if (randChoice == 1)
		{
			//enemy player
			if (playerControl) { std::cout << playerAttack->GetHandCard(index).GetName() << " attacks Sorceress. Sorceress' health is now " << playerHit->GetHealth() << std::endl; }
			else { std::cout << playerAttack->GetHandCard(index).GetName() << " attacks Wizard. Wizard's health is now " << playerHit->GetHealth() << std::endl; }
		}
		else if (randChoice == 2)
		{
			//friendly minion
			int randCard = 0;
			if (playerAttack->GetSizeOfTable() != 0) { int randCard = rand() % playerAttack->GetSizeOfTable(); }
			else
			{
				std::cout << "No cards for Bless to heal." << std::endl;
				return;
			}
			playerAttack->GetTableCard(randCard).SetHealth(playerAttack->GetTableCard(randCard).GetHealth() + playerAttack->GetHandCard(index).GetAttack());
			std::cout << playerAttack->GetHandCard(index).GetName() << " heals " << playerAttack->GetTableCard(randCard).GetName() << ". "
				<< playerAttack->GetTableCard(randCard).GetName() << "'s health is now " << playerAttack->GetTableCard(randCard).GetHealth() << std::endl;
		}
		else if (randChoice == 3)
		{
			//self
			playerAttack->SetHealth(playerAttack->GetHealth() + 2);
			if (playerControl) { std::cout << playerAttack->GetHandCard(index).GetName() << " heals Wizard. Wizard's health is now " << playerAttack->GetHealth() << std::endl; }
			else { std::cout << playerAttack->GetHandCard(index).GetName() << " heals Sorceress. Sorceress' health is now " << playerAttack->GetHealth() << std::endl; }
		}

		//remove from mHand
		playerAttack->RemoveHandCard(index);
	}
};
#endif