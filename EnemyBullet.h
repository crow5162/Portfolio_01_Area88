#pragma once
#include "gameNode.h"
#include <vector>

struct tagEnemyBullet
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

class EnemyBullet : public gameNode
{
private:
	vector<tagEnemyBullet>			 _vEnemyBullet;
	vector<tagEnemyBullet>::iterator _viEnemyBullet;

	const char* _imageName;
	float _range;
	int _bulletMax;

public:
	EnemyBullet() {};
	~EnemyBullet() {};

	HRESULT init(const char* imageName, int bulletMax, float range);
	void release();
	void update();
	void render();

	//총알 발사 함수
	void bulletFire(float x, float y, float angle, float range);

	void bulletMove();

	void removeBullet(int arrNum);

	vector<tagEnemyBullet>			 getVEnemyBullet()  { return _vEnemyBullet; }
	vector<tagEnemyBullet>::iterator getViEnemyBullet() { return _viEnemyBullet; }

};

