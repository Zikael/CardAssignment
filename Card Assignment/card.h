#ifndef _CARD_H
#define _CARD_H

#include <string>

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
};

#endif	