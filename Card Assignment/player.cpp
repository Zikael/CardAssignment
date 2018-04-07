#include "stdafx.h"

#include "player.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#ifndef _TYPES_H
	#include "types.h"
#endif

CPlayer::CPlayer()
{
	//Each player begins the game with 30 health points. 
	mHealth = 30;
}
CPlayer::~CPlayer()
{
	//empty body
}
//assign values from file
void CPlayer::AssignFromFile(std::string filename)
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
	/*
	*This function is used to assign the type, name, attack, and health of each variable to an instance of the appropriate class
	*The lines are read in and the type is taken
	*The type dictates which class is emplaced back onto the class
	*/
	while (file.good())
	{
		//load the fline from the file and place into stringstream
		std::getline(file, line);
		std::stringstream ss(line);

		//parse the file by spaces and assign varibles accrodingly
		std::getline(ss, type, ' ');
		std::getline(ss, name, ' ');
		std::getline(ss, attack, ' ');
		if (std::stoi(type) != 3)
		{
			//lightning does't have a specified health
			std::getline(ss, health, '\n');
		}
		else
		{
			//read to end of line and ignore the values
			std::string ignore;
			std::getline(ss, ignore, '\n');
			health = "0";
		}
		//shouldn't be reached, possible bug if health is null across multiple cards
		if (type == "") { return; }

		//add new element to the array for each card (dependant of card type)
		switch (std::stoi(type))
		{
		case 1:
			mDeck.emplace_back(new CMinion);
			break;
		case 2:
			mDeck.emplace_back(new CFireball);
			break;
		case 3:
			mDeck.emplace_back(new CLightning);
			break;
		case 4:
			mDeck.emplace_back(new CBless);
			break;
		case 5:
			mDeck.emplace_back(new CVampire);
			break;
		case 6: //Wall type is not a special class, just uses generic type
			mDeck.emplace_back(new CCard);
			break;
		case 7:
			mDeck.emplace_back(new CHorde);
			break;
		case 8:
			mDeck.emplace_back(new CTrample);
			break;
		case 9:
			mDeck.emplace_back(new CLeech);
			break;
		case 10:
			mDeck.emplace_back(new CSword);
			break;
		case 11:
			mDeck.emplace_back(new CArmour);
			break;
		default: //generic card -- should not be used, just in case.
			mDeck.emplace_back(new CCard);
			break;
		}

		//assign varibles to class
		mDeck[mDeck.size()-1]->SetType(std::stoi(type));
		mDeck[mDeck.size() - 1]->SetName(name);
		mDeck[mDeck.size() - 1]->SetAttack(std::stoi(attack));
		if (health != "") { mDeck[mDeck.size() - 1]->SetHealth(std::stoi(health)); }	//catch cards with no defined health value (i.e. lightning)
		else { mDeck[mDeck.size() - 1]->SetHealth(0); }									//assign the card 0 health
		mDeck[mDeck.size() - 1]->SetArmour(false);										//by default no minion should have armour
		mDeck[mDeck.size() - 1]->SetRemove(false);

#if _DEBUG
		std::cout
			<< "I: " << count << " "
			<< "T: " << mDeck[count]->GetType() << "	"
			<< "N: " << mDeck[count]->GetName() << "	"
			<< "A: " << mDeck[count]->GetAttack() << "	"
			<< "H: " << mDeck[count]->GetHealth() << "	"
			<< std::endl;
#endif
	}
}

void CPlayer::RemoveTableCard(int v)
{
	std::swap(mTable[v], mTable.back());
	mTable.pop_back();
}
void CPlayer::RemoveHandCard(int v)
{
	std::swap(mHand[v], mHand.back());
	mHand.pop_back();
}

//GETTERS
CCard& CPlayer::GetDeckCard(int v)
{
	return *mDeck[v];
}
CCard& CPlayer::GetHandCard(int v)
{
	return *mHand[v];
}
CCard& CPlayer::GetTableCard(int v)
{
	return *mTable[v];
}
int CPlayer::GetSizeOfDeck()
{
	return mDeck.size();
}
int CPlayer::GetSizeOfHand()
{
	return mHand.size();
}
int CPlayer::GetSizeOfTable()
{
	return mTable.size();
}
int CPlayer::GetHealth()
{
	return mHealth;
}

//SETTERS
void CPlayer::SetHealth(int v)
{
	mHealth = v;
}
void CPlayer::SetHandCard(int v)
{
	mHand.push_back(std::move(mDeck[v]));
	//remove card from mDeck
	std::swap(mDeck[v], mDeck.back());
	mDeck.pop_back();
}
void CPlayer::SetTableCard(int v)
{
	mTable.push_back(std::move(mHand[v]));
	//remove card from mHand
	std::swap(mHand[v], mHand.back());
	mHand.pop_back();
}
void CPlayer::ShuffleDeck(int randCard)
{
	//shuffle the mDeck by swapping a random card a random number of times, with 10 being the minimum and 50 the max.
	std::swap(mDeck[randCard], mDeck[0]);
}

