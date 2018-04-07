#include "stdafx.h"
#include "card.h"

CCard::CCard()
{

}
CCard::~CCard()
{

}

//setters
void CCard::SetAttack(int v)
{
	mAttack = v;
}
void CCard::SetName(std::string v)
{
	mName = v;
}
void CCard::SetHealth(int v)
{
	mHealth = v;
}
void CCard::SetType(int v)
{
	mType = v;
}
void CCard::SetArmour(bool b)
{
	mArmour = b;
}
void CCard::SetRemove(bool b)
{
	mRemove = b;
}

//getters
int CCard::GetAttack()
{
	return mAttack;
}
std::string CCard::GetName()
{
	return mName;
}
int CCard::GetHealth()
{
	return mHealth;
}
int CCard::GetType()
{
	return mType;
}
bool CCard::GetArmour()
{
	return mArmour;
}
bool CCard::GetRemove()
{
	return mRemove;
}