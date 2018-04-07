#ifndef _HORDE_H
#define _HORDE_H

#include <iostream>
#include "card.h"
#include "player.h"

class CHorde : public CCard
{
	void Play(CPlayer*& playerAttack, CPlayer*& playerHit, int index, bool playerControl)
	{
		//set attack of horde to 0 initally
		playerAttack->GetTableCard(index).SetAttack(0);

		//search the mTable vector for every instance of a horde type card
		//increase the attack of the current card by 1 for every other horde card
		int hordeType = 7;
		for (int i = 0; i < playerAttack->GetSizeOfTable(); ++i)
		{
			if (playerAttack->GetTableCard(i).GetType() == hordeType)
			{
				playerAttack->GetTableCard(index).SetAttack(playerAttack->GetTableCard(index).GetAttack()+1);
			}
		}
		if (playerHit->GetSizeOfTable() > 0)
		{
			//Attack a random card in player1 mTable 
			int randCard = 0;
			//if the player1 has more than 1 card, randomly select a card to attack
			if (playerHit->GetSizeOfTable() >= 2) { randCard = rand() % playerHit->GetSizeOfTable(); }

			//set the health of the attacked card
			playerHit->GetTableCard(randCard).SetHealth(playerHit->GetTableCard(randCard).GetHealth() - playerAttack->GetTableCard(index).GetAttack());
			if (playerHit->GetTableCard(randCard).GetArmour()) { playerHit->GetTableCard(randCard).SetHealth(playerHit->GetTableCard(randCard).GetHealth() + 1); }
			std::cout << playerAttack->GetTableCard(index).GetName() << " attacks " << playerHit->GetTableCard(randCard).GetName() << ". ";
			if (playerHit->GetTableCard(randCard).GetHealth() <= 0)
			{
				//Display which card is killed
				std::cout << playerHit->GetTableCard(randCard).GetName() << " killed." << std::endl;
				//REMOVE CARD FROM DECK
				playerHit->RemoveTableCard(randCard);
			}
			else { std::cout << playerHit->GetTableCard(randCard).GetName() << "'s health is now " << playerHit->GetTableCard(randCard).GetHealth() << std::endl; }
		}
		else
		{
			//Attack player directly
			playerHit->SetHealth(playerHit->GetHealth() - playerAttack->GetTableCard(index).GetAttack());
			//display new health levels
			if (playerControl) { std::cout << playerAttack->GetTableCard(index).GetName() << " attacks Sorceress. Sorceress' health is now " << playerHit->GetHealth() << std::endl; }
			else { std::cout << playerAttack->GetTableCard(index).GetName() << " attacks Wizard. Wizard's health is now " << playerHit->GetHealth() << std::endl; }
		}
	}
};

#endif

