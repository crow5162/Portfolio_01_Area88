#include "stdafx.h"
#include "jetplane.h"


jetplane::jetplane()
{
}


jetplane::~jetplane()
{
}

void jetplane::move()
{
	switch (_type)
	{
	case PHASEONE:
		if (_rc.left > WINSIZEX / 2 - 200 && !_turn)
		{
			_rc.left -= 15;
			_rc.right -= 15;
		}
		if (_rc.left < WINSIZEX / 2 - 200) _turn = true;
		if (_turn)
		{
			_rc.left += 20;
			_rc.right += 20;
		}
		break;
	case PHASETWO:
		if (_rc.left > WINSIZEX / 2 - 200 && !_turn)
		{
			_rc.left -= 15;
			_rc.right -= 15;
		}
		if (_rc.left < WINSIZEX / 2 - 200) _turn = true;
		if (_turn)
		{
			if (_direction == 0)
			{
				_rc.left += 18;
				_rc.right += 18;
				_rc.top += 5;
				_rc.bottom += 5;
			}
			if (_direction == 1)
			{
				_rc.left += 18;
				_rc.right += 18;
				_rc.top -= 5;
				_rc.bottom -= 5;
			}
		}
		break;
	case PHASETHREE:
		if (_direction == 0 && !_turn)
		{
			_rc.left -= 20;
			_rc.right -= 20;
			_rc.top += 2;
			_rc.bottom += 2;
			if (_rc.left < 50) _turn = true;
		}
		if (_direction == 0 && _turn)
		{
			_rc.left += 28;
			_rc.right += 28;
			_rc.top += 4;
			_rc.bottom += 4;
		}
		if (_direction == 1 && !_turn)
		{
			_rc.left -= 20;
			_rc.right -= 20;
			_rc.top -= 2;
			_rc.bottom -= 2;
			if (_rc.left < 50) _turn = true;
		}
		if (_direction == 1 && _turn)
		{
			_rc.left += 28;
			_rc.right += 28;
			_rc.top -= 4;
			_rc.bottom -= 4;
		}
		break;
	default:
		break;
	}


	

}
