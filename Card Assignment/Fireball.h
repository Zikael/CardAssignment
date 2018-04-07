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
		//determine a card to hit
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