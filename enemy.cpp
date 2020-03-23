#include "stdafx.h"
#include "enemy.h"


enemy::enemy()
{

}

enemy::~enemy()
{

}

HRESULT enemy::init()
{
	return S_OK;
}

HRESULT enemy::init(const char * imageName, POINT position)
{
	_currentFrameX = _currentFrameY = 0;
	_count = _fireCount = 0;

	_imageName = IMAGEMANAGER->findImage(imageName);

	_rndFireCount = RND->getFromIntTo(1, 10);

	if (_type != 3)
	{
		_rc = RectMakeCenter(position.x, position.y,
			_imageName->getFrameWidth(), _imageName->getFrameHeight());
	}
	if (_type == 3)
	{
		_rc = RectMakeCenter(position.x, position.y,
			_imageName->getFrameWidth(), _imageName->getFrameHeight());
	}
	_speed = 5.0f;
	_angle = 0;

	_mCurrentHP = _mMaxHP = 50;

	return S_OK;
}

HRESULT enemy::init(const char * imageName, POINT position, PHASETYPE type)
{
	_currentFrameX = _currentFrameY = 0;
	_count = _fireCount = 0;

	_imageName = IMAGEMANAGER->findImage(imageName);

	_rndFireCount = RND->getFromIntTo(1, 10);


	if (type != PHASEBOSS)
	{
		_rc = RectMakeCenter(position.x, position.y,
			_imageName->getFrameWidth(), _imageName->getFrameHeight());
	}
	else if (type == PHASEBOSS)
	{
		_rc = RectMakeCenter(position.x, position.y,
			_imageName->getFrameWidth(), _imageName->getFrameHeight());
	}
	_type = type;

	_mCurrentHP = _mMaxHP = 50;

	return S_OK;
}

HRESULT enemy::init(const char * imageName, POINT position, PHASETYPE type, int direction)
{
	_currentFrameX = _currentFrameY = 0;
	_count = _fireCount = 0;
	_rndFireCount = RND->getFromIntTo(1, 10);

	_imageName = IMAGEMANAGER->findImage(imageName);

	_rndFireCount = RND->getFromIntTo(1, 10);


	if (type != PHASEBOSS)
	{
		_rc = RectMakeCenter(position.x, position.y,
			_imageName->getFrameWidth(), _imageName->getFrameHeight());
	}
	if (type == PHASEBOSS)
	{
		_rc = RectMakeCenter(position.x, position.y,
			_imageName->getCenterX(), _imageName->getCenterY());
	}
	
	_type = type;
	_direction = direction;

	_mCurrentHP = _mMaxHP = 50;

	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	move();

	_count++;

	if (_count % 4 == 0)
	{
		_imageName->setFrameX(_currentFrameX);

		_currentFrameX++;
		if (_currentFrameX > _imageName->getMaxFrameX()) _currentFrameX = 0;
	}
}

void enemy::render()
{

	draw();
}

void enemy::move()
{

}

void enemy::draw()
{
	_imageName->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
}

bool enemy::bulletCountFire()
{
	_fireCount++;

	if (_fireCount % _rndFireCount == 0)
	{
		_fireCount = 0;
		_rndFireCount = RND->getFromIntTo(1, 500);
		return true;
	}

	return false;
}

void enemy::minionDamage(float mDamage)
{
	_mCurrentHP -= mDamage;
}

void enemy::setHP(float inputcurhp, float inputmaxhp)
{
	_mCurrentHP = inputcurhp;
	_mMaxHP = inputmaxhp;
}
