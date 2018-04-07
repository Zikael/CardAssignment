#ifndef _TRAMPLE_H
#define _TRAMPLE_H

#include "card.h"
#include <iostream>

#include "player.h"

class CTrample : public CCard
{
	void Play(CPlayer*& playerAttack, CPlayer*& playerHit, int index, bool playerControl)
	{
		int leftoverDamage = playerAttack->GetTableCard(index).GetAttack();
		//loop until no damage left to be done
		while (leftoverDamage > 0)
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

				//hold the current leftover damage
				int tmpDamage = leftoverDamage;
				//set new leftoverdamage
				leftoverDamage -= playerHit->GetTableCard(randCard).GetHealth();
				//set the health of the attacked card
				playerHit->GetTableCard(randCard).SetHealth(playerHit->GetTableCard(randCard).GetHealth() - tmpDamage);
				std::cout << playerAttack->GetTableCard(index).GetName() << " attacks " << playerHit->GetTableCard(randCard).GetName() << ". ";
				if (playerHit->GetTableCard(randCard).GetArmour()) { playerHit->GetTableCard(randCard).SetHealth(playerHit->GetTableCard(randCard).GetHealth() + 1); }
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
				//hold the current leftover damage
				int tmpDamage = leftoverDamage;
				//set new leftoverdamage, negative values cause the effect to keep attacking until everything is dead
				leftoverDamage -= abs(playerHit->GetHealth());
				if (leftoverDamage < 0) { leftoverDamage = 0; }
				//Attack player directly
				playerHit->SetHealth(playerHit->GetHealth() - tmpDamage);
				//display new health levels
				if (playerControl) { std::cout << playerAttack->GetTableCard(index).GetName() << " attacks Sorceress. Sorceress' health is now " << playerHit->GetHealth() << std::endl; }
				else { std::cout << playerAttack->GetTableCard(index).GetName() << " attacks Wizard. Wizard's health is now " << playerHit->GetHealth() << std::endl; }
			}
		}
	}
};
#endif