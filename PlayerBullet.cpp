#include "stdafx.h"
#include "PlayerBullet.h"
#include "PlayerManager.h"


HRESULT PlayerBullet::init(int bulletMax, float range)
{
	_bulletMax = bulletMax;
	_range = range;
	_btype = BULLET_SMALL;
	return S_OK;
}

void PlayerBullet::release()
{
}

void PlayerBullet::update()
{
	if (_kajama->getBulletTypecount() == 0)
	{
		_btype = BULLET_SMALL;
	}
	if (_kajama->getBulletTypecount() == 1)
	{
		_btype = BULLET_MIDDLE;
	}
	if (_kajama->getBulletTypecount() == 2)
	{
		_btype = BULLET_BIG;
	}

	move();

}

void PlayerBullet::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->render(getMemDC(),
			_viBullet->rc.left,
			_viBullet->rc.top, 0, 0,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());
	}

}

void PlayerBullet::fire(float x, float y)
{
	if (_bulletMax < _vBullet.size()) return;
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(bullet));

	bullet.bulletImage = new image;
	//충돌을하면 상태정의해서 
	if (_btype == BULLET_MIDDLE)	//중간단계 총알
	{ 
		bullet.bulletImage->init("Player_Bullet_04.bmp", 100, 59, true, RGB(255, 0, 255));
	}
	else if (_btype == BULLET_BIG)	//커다란 총알
	{ 
		bullet.bulletImage->init("Player_Bullet_06.bmp", 120, 70, true, RGB(255, 0, 255));
	}
	else //기본 총알
	{
		bullet.bulletImage->init("Player_Bullet_02.bmp", 80, 40, true, RGB(255, 0, 255));
	}

	bullet.speed = 20.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());

	_vBullet.push_back(bullet);
	
}

void PlayerBullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());
		if (_range < getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY))
		{
			SAFE_RELEASE(_viBullet->bulletImage);
			SAFE_DELETE(_viBullet->bulletImage);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void PlayerBullet::removeBullet(int arrNum)
{
	_vBullet[arrNum].bulletImage->release();
	_vBullet.erase(_vBullet.begin() + arrNum);
}
