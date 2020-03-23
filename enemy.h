#pragma once
#include "gameNode.h"

enum PHASETYPE
{
	PHASEONE,
	PHASETWO,
	PHASETHREE,
	PHASEBOSS
};
class enemy : public gameNode
{
protected:

	image* _imageName;
	RECT _rc;
	PHASETYPE _type;
	POINT xy;

	int _direction;
	float _angle;
	float _speed;

	int _count;
	int _fireCount;			//�Ѿ˹߻�� ���Ʈ
	int _rndFireCount;		//�����ϰ� �߻� �� ����

	int _currentFrameX;
	int _currentFrameY;

	bool _turn;	//���� ������ġ�� �����ϸ� true���ǰ� �ٸ��������� �����ϴ� ��

	float _mCurrentHP, _mMaxHP; //�̴Ͼ��� ����ü�°� �ִ�ü��

public:

	enemy();
	~enemy();

	HRESULT init();
	HRESULT init(const char* imageName, POINT position);
	HRESULT init(const char* imageName, POINT position, PHASETYPE type);
	HRESULT init(const char* imageName, POINT position, PHASETYPE type, int direction);


	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	void draw();

	bool bulletCountFire(); //�����Ѽ����̾Ƽ� �Ѿ��� �߻��϶�� ��ȣ�� �ݴϴ�. �Ŵ������� ���.
	inline RECT getRect() { return _rc; }
	
	float getmCurrHP() { return _mCurrentHP; }
	float getmMaxHP() { return _mMaxHP; }


	void minionDamage(float mDamage);
	void setHP(float inputcurhp, float inputmaxhp);
};

