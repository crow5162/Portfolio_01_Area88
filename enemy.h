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
	int _fireCount;			//총알발사용 까운트
	int _rndFireCount;		//랜덤하게 발사 할 변수

	int _currentFrameX;
	int _currentFrameY;

	bool _turn;	//적이 일정뒤치에 도달하면 true가되고 다른방향으로 가게하는 값

	float _mCurrentHP, _mMaxHP; //미니언의 현재체력과 최대체력

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

	bool bulletCountFire(); //랜덤한수를뽑아서 총알을 발사하라는 신호를 줍니다. 매니저에서 사용.
	inline RECT getRect() { return _rc; }
	
	float getmCurrHP() { return _mCurrentHP; }
	float getmMaxHP() { return _mMaxHP; }


	void minionDamage(float mDamage);
	void setHP(float inputcurhp, float inputmaxhp);
};

