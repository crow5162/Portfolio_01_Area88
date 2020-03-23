#include "stdafx.h"
#include "BOSS.h"


BOSS::BOSS()
{
}


BOSS::~BOSS()
{
}

void BOSS::move()
{
	switch (_type)
	{
	case PHASEONE:
		break;
	case PHASETWO:
		break;
	case PHASETHREE:
		break;
	case PHASEBOSS:
		if (_rc.left > WINSIZEX - 500)
		{
			_rc.left -= 5;
			_rc.right -= 5;
		}
		if (!_turn)
		{
			_rc.top += 1;
			_rc.bottom += 1;
			if (_rc.bottom > WINSIZEY / 2 + 130) _turn = true;
		}
		if (_turn)
		{
			_rc.top -= 1;
			_rc.bottom -= 1;
			if (_rc.top < WINSIZEY / 2 - 130) _turn = false;
		}
		break;
	default:
		break;
	}
}
