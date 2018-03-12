#ifndef _PLAYER_H
#define _PLAYER_H

#include <vector>
#include "card.h"

class CPlayer
{
private:
	int mHealth;
	int mSize;
	//vector for cards in deck
	std::vector<CCard*> deck;
	//vector for cards in hand
	std::vector<CCard*> hand;
	//vector for table cards
	std::vector<CCard*> table;
public:
	CPlayer();
	~CPlayer();

	//getters
	int getHealth();
	int getSizeOfDeck();
	int getSizeOfHand();
	int getSizeOfTable();
	CCard& getDeckCard(int v);
	CCard& getHandCard(int v);
	CCard& getTableCard(int v);

	//setters
	void setHealth(int v);
	void setHandCard(int v);
	void setTableCard(int v);

	//functions
	//assign cards from file
	void assignFromFile(std::string filepath);
	//remove card item from vector
	void removeTableCard(int v);
};

#endif