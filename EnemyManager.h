#pragma once
#include "gameNode.h"
#include "helicopter.h"
#include "helicopter2.h"
#include "jetplane.h"
#include "BOSS.h"
#include <vector>
#include "EnemyBullet.h"

class PlayerManager;

struct eExplosion
{
	image* _explosion;
	int frameX;
	int timeCount;
};

class EnemyManager : public gameNode
{
private:
	typedef vector<enemy*>				vEnemy;
	typedef vector<enemy*>::iterator	viEnemy;
private:
	vector<eExplosion*>			_vexplosion;

	vEnemy  _vAircraft;
	viEnemy _viAircraft;

	PlayerManager* _kajama;
	EnemyBullet* _bullet;

	PHASETYPE _type;

	float _angle;

	int _setCount;	 //일정시간마다 몬스터가 생성되는 카운트
	int _typeCount;	 //일정시간마다 페이즈이넘을 넘겨주는 카운트
	int _Bbulletcnt; //보스가 등장하면 보스는 이 카운트에 따가 탄을 발사합니다.
	bool _goRight;   //보스 페이즈2 에서 시계방향으로 나가는 총알을 꺾어주기 위해서 만들었습니다.

	char buf[256];	 //보스가 젠될때 무한정 늘어나는 현상이 생겨서
	int _bossCount;	 //bool값을줘서 한번 생성되면 true되면서 더이상 생겨나지않게 
	bool _setBoss;	 //막았습니다., boss카운트로 보스가 몇마리 나오는지 확인했습니다.
	RECT _bulletHit; //적의 총알과 카자마가 충돌할시 체크하는 렉트.
	RECT _planeCrash;//적과 카자마가 충돌할 시 체크하는 렉트.

public:
	EnemyManager();
	~EnemyManager();

	HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setAircraft();									//적비행기1 생성

	void setAircraft(PHASETYPE type);					//적비행기1 생성
	void removeAircraft(int arrNum);					

	void setRedAircraft(PHASETYPE type);				//적비행기2 생성
	void removeRedAircraft(int arrNum);
			
	void setJet(PHASETYPE type);						//적 전투기 생성
	void removeJet(int arrNum);

	void setBoss(PHASETYPE type);						//보스 생성
	void removeBoss(int arrNum);

	void collision();									//적비행체가 발사한 총알에 플레이어가 피격시 체력감소 함수.
	void AircraftReset();
	void EnemyBulletfire();

	void DeleteMonster();								

	void setPlayerManagerMemoryAddressLink(PlayerManager* kajama) { _kajama = kajama; }

	vector<enemy*> getVAircraft() { return _vAircraft; }
	vector<enemy*>::iterator getViAircraft() { return _viAircraft; }

};

