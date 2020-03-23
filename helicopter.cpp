#include "stdafx.h"
#include "helicopter.h"


helicopter::helicopter()
{
}


helicopter::~helicopter()
{
}

void helicopter::move()
{
	switch (_type)
	{
	case PHASEONE:
		_rc.left -= 8;
		_rc.right -= 8;
		break;
	case PHASETWO:
		_rc.left -= 10;
		_rc.right -= 10;
		if (_rc.left < WINSIZEX / 2 - 100)
		{
			_rc.top += 7;
			_rc.bottom += 7;
		}
		break;
	case PHASETHREE:
		if (_rc.bottom < WINSIZEY / 2 - 20 && _direction == 0)
		{
			_rc.top += 3;
			_rc.bottom += 3;
		}
		if (_rc.bottom > WINSIZEY / 2 - 20 && _direction == 0)
		{
			_rc.left -= 13;
			_rc.right -= 13;
		}
		if (_rc.bottom < WINSIZEY / 2 - 120 && _direction == 1)
		{
			_rc.top += 3;
			_rc.bottom += 3;
		}
		if (_rc.bottom >= WINSIZEY / 2 - 120 && _direction == 1)
		{
			_rc.left -= 13;
			_rc.right -= 13;
		}
		if (_rc.bottom < WINSIZEY / 2 - 190 && _direction == 2)
		{
			_rc.top += 3;
			_rc.bottom += 3;
		}
		if (_rc.bottom > WINSIZEY / 2 - 190 && _direction == 2)
		{
			_rc.left -= 13;
			_rc.right -= 13;
		}
		break;
	default:
		break;
	}
	

}
