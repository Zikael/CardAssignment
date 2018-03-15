#ifndef _BLESS_H
#define _BLESS_H

#include "card.h"
#include <iostream>

#include "player.h"

class CBless : public CCard
{
	void play(CPlayer*& playerAttack, CPlayer*& playerHit, int index, bool playerControl)
	{

		int randChoice = rand() % 4;
		if (randChoice == 0)
		{
			//enemy minions
			int randCard = 0;
			if (playerHit->getSizeOfTable() != 0) { randCard = rand() % playerHit->getSizeOfTable(); }
			else 
			{ 
				std::cout << "No cards for Bless to attack." << std::endl;
				return;
			}
			playerHit->getTableCard(randCard).setHealth(playerHit->getTableCard(randCard).getHealth() - playerAttack->getTableCard(index).getAttack());
			std::cout << playerAttack->getTableCard(index).getName() << " attacks " << playerHit->getTableCard(randCard).getName() << ". "
				<< playerHit->getTableCard(randCard).getName() << "'s health is now " << playerHit->getTableCard(randCard).getHealth();
		}
		else if (randChoice == 1)
		{
			//enemy player
			if (playerControl) { std::cout << playerAttack->getTableCard(index).getName() << " attacks Sorceress. Sorceress' health is now " << playerHit->getHealth() << std::endl; }
			else { std::cout << playerAttack->getTableCard(index).getName() << " attacks Wizard. Wizard's health is now " << playerHit->getHealth() << std::endl; }
		}
		else if (randChoice == 2)
		{
			//friendly minion
			int randCard = 0;
			if (playerAttack->getSizeOfTable() != 0) { int randCard = rand() % playerAttack->getSizeOfTable(); }
			else
			{
				std::cout << "No cards for Bless to heal." << std::endl;
				return;
			}
			playerAttack->getTableCard(randCard).setHealth(playerAttack->getTableCard(randCard).getHealth() + playerAttack->getTableCard(index).getAttack());
			std::cout << playerAttack->getTableCard(index).getName() << " heals " << playerAttack->getTableCard(randCard).getName() << ". "
				<< playerAttack->getTableCard(randCard).getName() << "'s health is now " << playerAttack->getTableCard(randCard).getHealth();
		}
		else if (randChoice == 3)
		{
			//self
			if (playerControl) { std::cout << playerAttack->getTableCard(index).getName() << " heals Sorceress. Sorceress' health is now " << playerHit->getHealth() << std::endl; }
			else { std::cout << playerAttack->getTableCard(index).getName() << " heals Wizard. Wizard's health is now " << playerHit->getHealth() << std::endl; }
		}

		//remove from deck
		playerAttack->removeTableCard(index);
	}
};
#endif