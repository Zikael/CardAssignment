#ifndef _VAMPIRE_H
#define  _VAMPIRE_H

#include "card.h"
#include <iostream>

#include "player.h"

class CVampire: public CCard
{
	void Play(CPlayer*& playerAttack, CPlayer*& playerHit, int index, bool playerControl)
	{
		if (playerHit->GetSizeOfTable() > 0)
		{
			int randCard = 0;
			//Detect if the enemy has a wall, if so, only attack the wall
			int wallType = 6;
			for (int i = 0; i < playerHit->GetSizeOfTable(); ++i)
			{
				if (playerHit->GetTableCard(i).GetType() == wallType)
				{
					randCard = i;
				}
				else
				{
					//Attack a random card in player1 mTable 
					//if the player1 has more than 1 card, randomly select a card to attack
					if (playerHit->GetSizeOfTable() >= 2) { randCard = rand() % playerHit->GetSizeOfTable(); }
				}
			}

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
		//vampire has the ability to gain 1 health after each attack.
		playerAttack->GetTableCard(index).SetHealth(playerAttack->GetTableCard(index).GetHealth() + 1);
	}
};
#endif