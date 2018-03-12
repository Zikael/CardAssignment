#include "stdafx.h"

#include "player.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

CPlayer::CPlayer()
{

	//Each player begins the game with 30 health points. 
	mHealth = 30;
}
CPlayer::~CPlayer()
{
	//delete pointer to card on player class temination
	for (std::vector<CCard*>::iterator it = deck.begin(); it != deck.end(); it++) {
		delete *it;
	}
	for (std::vector<CCard*>::iterator it = hand.begin(); it != hand.end(); it++) {
		delete *it;
	}
	for (std::vector<CCard*>::iterator it = table.begin(); it != table.end(); it++) {
		delete *it;
	}
}

//assign values from file
void CPlayer::assignFromFile(std::string filename)
{
	std::ifstream file(filename); 
	std::string line;
	std::string type, name, attack, health;
	if (!file)
	{
		std::cout << "Unable to open file " << filename << std::endl;
		return;
	}

#if _DEBUG
	std::cout << std::endl << "Loaded cards from: " << filename << std::endl;
#endif

	int count = 0;
	while (file.good())
	{
		//add new element to the array for each card
		deck.push_back(new CCard);

		//load the fline from the file and place into stringstream
		std::getline(file, line);
		std::stringstream ss(line);

		//parse the file by spaces and assign varibles accrodingly
		std::getline(ss, type, ' ');
		std::getline(ss, name, ' ');
		std::getline(ss, attack, ' ');
		std::getline(ss, health, '\n');

		//assign varibles to class
		deck[count]->setType(std::stoi(type));
		deck[count]->setName(name);
		deck[count]->setAttack(std::stoi(attack));
		deck[count]->setHealth(std::stoi(health));


#if _DEBUG
		std::cout
			<< "I: " << count << " "
			<< "T: " << deck[count]->getType() << "	"
			<< "N: " << deck[count]->getName() << "	"
			<< "A: " << deck[count]->getAttack() << "	"
			<< "H: " << deck[count]->getHealth() << "	"
			<< std::endl;
#endif
		//iterate for next card
		count++;
	}
	mSize = count;
}

//GETTERS
CCard& CPlayer::getDeckCard(int v)
{
	return *deck[v];
}
CCard& CPlayer::getHandCard(int v)
{
	return *hand[v];
}
CCard& CPlayer::getTableCard(int v)
{
	return *table[v];
}
int CPlayer::getSizeOfDeck()
{
	return deck.size();
}
int CPlayer::getSizeOfHand()
{
	return hand.size();
}
int CPlayer::getSizeOfTable()
{
	return table.size();
}
int CPlayer::getHealth()
{
	return mHealth;
}

//SETTERS
void CPlayer::setHealth(int v)
{
	mHealth = v;
}
void CPlayer::setHandCard(int v)
{
	hand.push_back(deck[v]);
	std::swap(deck[v], deck.back());
	deck.pop_back();
	mSize--;
}
void CPlayer::setTableCard(int v)
{
	table.push_back(hand[v]);
	std::swap(hand[v], hand.back());
	hand.pop_back();
}

