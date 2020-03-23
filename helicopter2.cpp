#include "stdafx.h"
#include "helicopter2.h"


helicopter2::helicopter2()
{
}


helicopter2::~helicopter2()
{
}

void helicopter2::move()
{
	if (_type == PHASEONE)
	{
		_rc.left -= 8;
		_rc.right -= 8;
	}
	else if (_type == PHASETWO)
	{
		_rc.left -= 10;
		_rc.right -= 10;
		if (_rc.left < WINSIZEX / 2 - 100)
		{
			_rc.top -= 7;
			_rc.bottom -= 7;
		}
	}
	else if (_type == PHASETHREE)
	{
		if (_rc.top > WINSIZEY / 2 + 30 && _direction == 0)
		{
			_rc.top -= 3;
			_rc.bottom -= 3;
		}
		if (_rc.top < WINSIZEY / 2 + 30 && _direction == 0)
		{
			_rc.left -= 13;
			_rc.right -= 13;
		}
		if (_rc.top > WINSIZEY / 2 + 120 && _direction == 1)
		{
			_rc.top -= 3;
			_rc.bottom -= 3;
		}
		if (_rc.top <= WINSIZEY / 2 + 120 && _direction == 1)
		{
			_rc.left -= 13;
			_rc.right -= 13;
		}
		if (_rc.top > WINSIZEY / 2 + 200 && _direction == 2)
		{
			_rc.top -= 3;
			_rc.bottom -= 3;
		}
		if (_rc.top < WINSIZEY / 2 + 200 && _direction == 2)
		{
			_rc.left -= 13;
			_rc.right -= 13;
		}
	}
}
