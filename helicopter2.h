#pragma once
#include "enemy.h"

class helicopter2 : public enemy
{
public:
	helicopter2();
	~helicopter2();

	virtual void move() override;
};

