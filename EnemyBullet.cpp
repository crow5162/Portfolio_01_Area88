#include "stdafx.h"
#include "EnemyBullet.h"

HRESULT EnemyBullet::init(const char * imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void EnemyBullet::release()
{
}

void EnemyBullet::update()
{
	bulletMove();
}

void EnemyBullet::render()
{
	for (_viEnemyBullet = _vEnemyBullet.begin(); _viEnemyBullet != _vEnemyBullet.end(); ++_viEnemyBullet)
	{
		_viEnemyBullet->bulletImage->render(getMemDC(), _viEnemyBullet->rc.left, _viEnemyBullet->rc.top);
	}
}

void EnemyBullet::bulletFire(float x, float y, float angle, float speed)
{
	if (_bulletMax < _vEnemyBullet.size()) return;

	tagEnemyBullet bullet;
	ZeroMemory(&bullet, sizeof(tagEnemyBullet));
	bullet.bulletImage = IMAGEMANAGER->findImage(_imageName);
	bullet.speed = speed;
	bullet.radius = bullet.bulletImage->getWidth() / 2;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.angle = angle;

	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());

	_vEnemyBullet.push_back(bullet);
}

void EnemyBullet::bulletMove()
{
	for (_viEnemyBullet = _vEnemyBullet.begin(); _viEnemyBullet != _vEnemyBullet.end();)
	{
		_viEnemyBullet->x += cosf(_viEnemyBullet->angle) * _viEnemyBullet->speed;
		_viEnemyBullet->y += -sinf(_viEnemyBullet->angle) * _viEnemyBullet->speed;

		_viEnemyBullet->rc = RectMakeCenter(_viEnemyBullet->x, _viEnemyBullet->y,
			_viEnemyBullet->bulletImage->getWidth(),
			_viEnemyBullet->bulletImage->getHeight());

		if (_range < getDistance(_viEnemyBullet->x, _viEnemyBullet->y, _viEnemyBullet->fireX, _viEnemyBullet->fireY))
		{
			_viEnemyBullet = _vEnemyBullet.erase(_viEnemyBullet);
		}
		else ++_viEnemyBullet;

	}
}

void EnemyBullet::removeBullet(int arrNum)
{
	_vEnemyBullet.erase(_vEnemyBullet.begin() + arrNum);
}
