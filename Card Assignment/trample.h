#ifndef _TRAMPLE_H
#define _TRAMPLE_H

#include "card.h"
#include <iostream>

#include "player.h"

class CTrample : public CCard
{
	void play(CPlayer*& playerAttack, CPlayer*& playerHit, int index, bool playerControl)
	{

		//TODO: DEBUG SECTION PROPERLY

		int leftoverDamage = playerAttack->getTableCard(index).getAttack();
		//loop until no damage left to be done
		while (leftoverDamage > 0)
		{
			if (playerHit->getSizeOfTable() > 0)
			{
				int randCard = 0;
				//Detect if the enemy has a wall, if so, only attack the wall
				int wallType = 6;
				for (int i = 0; i < playerHit->getSizeOfTable(); ++i)
				{
					if (playerHit->getTableCard(i).getType() == wallType)
					{
						randCard = i;
					}
					else
					{
						//Attack a random card in player1 table 
						//if the player1 has more than 1 card, randomly select a card to attack
						if (playerHit->getSizeOfTable() >= 2) { randCard = rand() % playerHit->getSizeOfTable(); }
					}
				}

				//hold the current leftover damage
				int tmpDamage = leftoverDamage;
				//set new leftoverdamage
				leftoverDamage -= playerHit->getTableCard(randCard).getHealth();
				//set the health of the attacked card
				playerHit->getTableCard(randCard).setHealth(playerHit->getTableCard(randCard).getHealth() - tmpDamage);
				std::cout << playerAttack->getTableCard(index).getName() << " attacks " << playerHit->getTableCard(randCard).getName() << ". ";
				if (playerHit->getTableCard(randCard).getArmour()) { playerHit->getTableCard(randCard).setHealth(playerHit->getTableCard(randCard).getHealth() + 1); }
				if (playerHit->getTableCard(randCard).getHealth() <= 0)
				{
					//Display which card is killed
					std::cout << playerHit->getTableCard(randCard).getName() << " killed." << std::endl;
					//REMOVE CARD FROM DECK
					playerHit->removeTableCard(randCard);
				}
				else { std::cout << playerHit->getTableCard(randCard).getName() << "'s health is now " << playerHit->getTableCard(randCard).getHealth() << std::endl; }

			}
			else
			{
				//hold the current leftover damage
				int tmpDamage = leftoverDamage;
				//set new leftoverdamage, negative values cause the effect to keep attacking until everything is dead
				leftoverDamage -= abs(playerHit->getHealth());
				if (leftoverDamage < 0) { leftoverDamage = 0; }
				//Attack player directly
				playerHit->setHealth(playerHit->getHealth() - tmpDamage);
				//display new health levels
				if (playerControl) { std::cout << playerAttack->getTableCard(index).getName() << " attacks Sorceress. Sorceress' health is now " << playerHit->getHealth() << std::endl; }
				else { std::cout << playerAttack->getTableCard(index).getName() << " attacks Wizard. Wizard's health is now " << playerHit->getHealth() << std::endl; }
			}
		}
	}
};
#endif