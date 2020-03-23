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

	int _setCount;	 //�����ð����� ���Ͱ� �����Ǵ� ī��Ʈ
	int _typeCount;	 //�����ð����� �������̳��� �Ѱ��ִ� ī��Ʈ
	int _Bbulletcnt; //������ �����ϸ� ������ �� ī��Ʈ�� ���� ź�� �߻��մϴ�.
	bool _goRight;   //���� ������2 ���� �ð�������� ������ �Ѿ��� �����ֱ� ���ؼ� ��������ϴ�.

	char buf[256];	 //������ ���ɶ� ������ �þ�� ������ ���ܼ�
	int _bossCount;	 //bool�����༭ �ѹ� �����Ǹ� true�Ǹ鼭 ���̻� ���ܳ����ʰ� 
	bool _setBoss;	 //���ҽ��ϴ�., bossī��Ʈ�� ������ ��� �������� Ȯ���߽��ϴ�.
	RECT _bulletHit; //���� �Ѿ˰� ī�ڸ��� �浹�ҽ� üũ�ϴ� ��Ʈ.
	RECT _planeCrash;//���� ī�ڸ��� �浹�� �� üũ�ϴ� ��Ʈ.

public:
	EnemyManager();
	~EnemyManager();

	HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setAircraft();									//�������1 ����

	void setAircraft(PHASETYPE type);					//�������1 ����
	void removeAircraft(int arrNum);					

	void setRedAircraft(PHASETYPE type);				//�������2 ����
	void removeRedAircraft(int arrNum);
			
	void setJet(PHASETYPE type);						//�� ������ ����
	void removeJet(int arrNum);

	void setBoss(PHASETYPE type);						//���� ����
	void removeBoss(int arrNum);

	void collision();									//������ü�� �߻��� �Ѿ˿� �÷��̾ �ǰݽ� ü�°��� �Լ�.
	void AircraftReset();
	void EnemyBulletfire();

	void DeleteMonster();								

	void setPlayerManagerMemoryAddressLink(PlayerManager* kajama) { _kajama = kajama; }

	vector<enemy*> getVAircraft() { return _vAircraft; }
	vector<enemy*>::iterator getViAircraft() { return _viAircraft; }

};

