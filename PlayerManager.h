#pragma once
#include "gameNode.h"
#include "PlayerBullet.h"
#include "progressBar.h"
#include "Item.h"

class EnemyManager;
class HealItem;
class bulletSizeUpItem;

struct EXPLOSION
{
	image* explosion;
	int frameX;
	int timecount;
};

enum PLAYERSTATE
{
	PLAYER_RIGHT,
	PLAYER_LEFT,
	PLAYER_UP,
	PLAYER_DOWN,
	PLAYER_RIGHTFIRE,
	PLAYER_UPFIRE,
	PLAYER_DOWNFIRE
};

enum PLAYERSCREEN
{
	NORMAL,
	HIT,
	DANGER,
	DEATH,
	NONE
};

class PlayerManager : public gameNode
{
private:
	vector<EXPLOSION*>		_vexplosion;

	image* _kajama;
	PLAYERSTATE _kajamaState;
	PlayerBullet* _bullet;
	EnemyManager* _em;
	progressBar* _hpBar;
	image* _screen;
	PLAYERSCREEN _ps;

	HealItem* _healItem;
	bulletSizeUpItem* _sizeupItem;

	RECT _rc;
	 //플레이어의 총알과 적의 충돌 체크 렉트.

	int _currentFrameX; 
	int _currentFrameY;

	int _currentFrameX2; 
	int _currentFrameY2;

	int _count;
	int _count2;
	int _returnCount;

	int _currentFrameX3, _currentFrameY3;
	int _currentFrameX4, _currentFrameY4;
	int _currentFrameX5, _currentFrameY5;
	int _count3;
	int _count4;
	bool _isDead;

	int _moveIndex;

	bool _isFire;
	int _fireCount;

	float _currentHP, _maxHP;

	char buffer[128];
	int _bcount;
	int _playerScore;

public:
	PlayerManager();
	~PlayerManager();

	virtual HRESULT init();
	virtual HRESULT init(const char * imageName, POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	void KajamaScreen();

	void collision();

	void MoveMotion();

	void hitDamage(float damage);

	image* getKajamaImage() { return _kajama; }
	int getBulletTypecount() { return _bcount; }

	void setMemoryAddressLink(EnemyManager* em) { _em = em; }

	PlayerBullet* getBullet() { return _bullet; }
	inline RECT getRect() { return _rc; }
	int getScore() { return _playerScore; }
};

