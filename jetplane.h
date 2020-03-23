#pragma once
#include "enemy.h"

class jetplane : public enemy
{
public:
	jetplane();
	~jetplane();

	virtual void move() override;
};

