#ifndef _PLAYER_H
#define _PLAYER_H

#include <vector>
#include <memory>
#include "card.h"

class CPlayer
{
private:
	int mHealth;	//Health of the player
	std::vector<std::unique_ptr<CCard>> mDeck;	//vector for cards in mDeck
	std::vector<std::unique_ptr<CCard>> mHand;	//vector for cards in mHand
	std::vector<std::unique_ptr<CCard>> mTable;	//vector for mTable cards
public:
	CPlayer();
	virtual ~CPlayer();

	//getters
	int GetHealth();				//returns the players health
	int GetSizeOfDeck();			//returns the size of the mDeck vector
	int GetSizeOfHand();			//returns the size of the mHand vector
	int GetSizeOfTable();			//returns the size of the tabke vector
	CCard& GetDeckCard(int v);		//returns a card in the mDeck vector at position v
	CCard& GetHandCard(int v);		//returns a card in the mHand vector at position v
	CCard& GetTableCard(int v);		//returns a card in the mTable vector at position v

	//setters
	void SetHealth(int v);			//set a new value for the players health
	void SetHandCard(int v);		//give a new mHand card from the mDeck vector
	void SetTableCard(int v);		//give a new mTable card from the mHand vector

	//functions
	void AssignFromFile(std::string filepath);	//Read the cards in from the file and assign to the mDeck vecotr
	void RemoveTableCard(int v);				//remove card item from vector
	void RemoveHandCard(int v);					//remove card item from hand vector (used in spells)
	void ShuffleDeck(int randCard);				//shuffle the mDeck
};

#endif