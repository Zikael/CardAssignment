#ifndef _TABLE_H
#define _TABLE_H

#include "card.h"
#include <vector>

class CTable
{
private:
	std::vector<CCard*> table;
public:
	CTable();
	~CTable();

	//getters
	CCard getCard(int v);

	//setters
	CCard setCard(CCard c);

};

#endif	