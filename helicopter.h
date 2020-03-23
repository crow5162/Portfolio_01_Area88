#pragma once
#include "enemy.h"

class helicopter : public enemy
{
private:
	PHASETYPE type;
public:
	helicopter();
	~helicopter();

	virtual void move() override;

}; 

