#include "stdafx.h"
#include "card.h"

CCard::CCard()
{

}
CCard::~CCard()
{

}

//setters
void CCard::setAttack(int v)
{
	mAttack = v;
}
void CCard::setName(std::string v)
{
	mName = v;
}
void CCard::setHealth(int v)
{
	mHealth = v;
}
void CCard::setType(int v)
{
	mType = v;
}
void CCard::setArmour(bool b)
{
	mArmour = b;
}
void CCard::setRemove(bool b)
{
	mRemove = b;
}

//getters
int CCard::getAttack()
{
	return mAttack;
}
std::string CCard::getName()
{
	return mName;
}
int CCard::getHealth()
{
	return mHealth;
}
int CCard::getType()
{
	return mType;
}
bool CCard::getArmour()
{
	return mArmour;
}
bool CCard::getRemove()
{
	return mRemove;
}