#pragma once
#include "gameNode.h"
#include <vector>

enum Bullettype
{
	BULLET_SMALL,
	BULLET_MIDDLE,
	BULLET_BIG
};

struct tagBullet
{
	image* bulletImage;
	RECT rc;
	float x, y;
	float angle;
	float radius;
	float speed;
	float fireX, fireY;
	bool isFire;
	int count;
};

class PlayerManager;
class PlayerBullet : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator	_viBullet;

	PlayerManager* _kajama;

	float _range;
	int _bulletMax;
	Bullettype _btype;


public:

	PlayerBullet() {};
	~PlayerBullet() {};

	virtual HRESULT init(int bulletMax, float range);
	virtual void release();
	virtual void update();
	virtual void render();

	void fire(float x, float y);
	void move();
	void removeBullet(int arrNum);

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getViBullet() { return _viBullet; }

	void syncKajamaForPBulletWithKajama(PlayerManager* pm) { _kajama = pm; }

};

