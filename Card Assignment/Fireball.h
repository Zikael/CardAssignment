#ifndef _FIREBALL_H
#define _FIREBALL_H

#include "card.h"
#include <iostream>

#include "player.h"

class CFireball : public CCard
{
	void Play(CPlayer*& playerAttack, CPlayer*& playerHit, int index, bool playerControl)
	{
		//print out all the card on enemies mTable & summoner
		int cardNum = 0;

		//deprecated code -- removed because player has no control.
		/*
		if (playerControl)
		{
			int i;
			for (i = 0; i < playerHit->getSizeOfTable(); ++i)
			{
				std::cout << i << ": " << playerHit->GetTableCard(i).getName() << " (" << playerHit->GetTableCard(i).getHealth() << " hp)." << std::endl;
			}
			std::cout << i << ": Summoner." << std::endl;

			//validate input
			bool validInput = false;
			while (!validInput)
			{
				std::cout << "Choose target for " << playerAttack->GetHandCard(index).getName() << " to attack: ";
				std::cin >> cardNum;
				if (cardNum >= 0 && cardNum <= i) { validInput = true; }
				else
				{
					std::cin.clear();
					std::cin.ignore();
					std::cout << std::endl << "Please select a card number between 0 and " << i << "." << std::endl;
				}
			}
			std::cin.clear();
			std::cin.ignore();
			std::cout << std::endl;
		}
		else { if (cardNum != 0) {cardNum = rand() % playerHit->getSizeOfTable(); } } 
		*/

		//determine a card to hit for the AI
		if (playerHit->GetSizeOfTable() != 0) { cardNum = rand() % playerHit->GetSizeOfTable(); }
		if (cardNum == playerHit->GetSizeOfTable())
		{
			//attack summoner
			playerHit->SetHealth(playerHit->GetHealth() - playerAttack->GetHandCard(index).GetAttack());
			if (playerControl) { std::cout << playerAttack->GetHandCard(index).GetName() << " attacks Sorceress. Sorceress' health is now " << playerHit->GetHealth() << std::endl; }
			else { std::cout << playerAttack->GetHandCard(index).GetName() << " attacks Wizard. Wizard's health is now " << playerHit->GetHealth() << std::endl; }
		}
		else
		{
			playerHit->GetTableCard(cardNum).SetHealth(playerHit->GetTableCard(cardNum).GetHealth() - playerAttack->GetHandCard(index).GetAttack());
			if (playerHit->GetTableCard(cardNum).GetArmour()) { playerHit->GetTableCard(cardNum).SetHealth(playerHit->GetTableCard(cardNum).GetHealth() + 1); }
			std::cout << playerAttack->GetHandCard(index).GetName() << " attacks " << playerHit->GetTableCard(cardNum).GetName() << ". ";
			if (playerHit->GetTableCard(cardNum).GetHealth() <= 0)
			{
				//Display which card is killed
				std::cout << playerHit->GetTableCard(cardNum).GetName() << " killed." << std::endl;
				//REMOVE CARD FROM DECK
				playerHit->RemoveTableCard(cardNum);
			}
			else { std::cout << playerHit->GetTableCard(cardNum).GetName() << "'s health is now " << playerHit->GetTableCard(cardNum).GetHealth() << std::endl; }
		}

		//remove from mHand
		playerAttack->RemoveHandCard(index);
	}
};
#endif