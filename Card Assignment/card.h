#ifndef _CARD_H
#define _CARD_H

#include <string>

class CPlayer;
class CCard 
{
private:
	int mType;				//type of card
	std::string mName;		//name of the card
	int mAttack;			//attack value of the card
	int mHealth;			//health of the card
	bool mArmour;			//does the card have armour
	bool mRemove;			//flag to be removed from the mTable vector
public:
	CCard();
	virtual ~CCard();

	//setters
	void SetType(int v);			//set the type of the card
	void SetName(std::string v);	//set the name of the card
	void SetAttack(int v);			//set the attack of the card
	void SetHealth(int v);			//set the health of the card
	void SetArmour(bool b);			//set the armour state of the card
	void SetRemove(bool b);			//flag if the card should be remove (i.e. dead)

	//getters
	int GetType();			//return the tpye of the card
	std::string GetName();	//return the game of the card
	int GetAttack();		//return the attack of the card
	int GetHealth();		//return the health of the card
	bool GetArmour();		//return if the card has armour
	bool GetRemove();		//return if the card should be removed
	
	//polymorphic sollution for every card to play.
	//most card types (all but wall) have their own implementation of the play function
	//this function is overwritten by the other cards so that their special attack is carried out 
	//the wall does not carry out an attack so it returns nothing.
	virtual void Play(CPlayer*& player1, CPlayer*& player2, int index, bool playerControl) { return; };
};

#endif	