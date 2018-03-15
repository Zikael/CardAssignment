#ifndef _CARD_H
#define _CARD_H

#include <string>

class CPlayer;
class CCard 
{
private:
	int mType;
	std::string mName;
	int mAttack;
	int mHealth;
public:
	CCard();
	~CCard();

	//setters
	void setType(int v);
	void setName(std::string v);
	void setAttack(int v);
	void setHealth(int v);

	//getters
	int getType();
	std::string getName();
	int getAttack();
	int getHealth();

	virtual void play(CPlayer*& player1, CPlayer*& player2, int index, bool playerControl) { return; };
};

#endif	