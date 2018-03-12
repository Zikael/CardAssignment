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
