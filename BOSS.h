#pragma once
#include "enemy.h"

class BOSS : public enemy
{

public:
	BOSS();
	~BOSS();

	virtual void move() override;
};

