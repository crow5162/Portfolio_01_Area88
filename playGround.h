#pragma once
#include "gameNode.h"
#include "PlayerManager.h"
#include "EnemyManager.h"
#include "ScoreManager.h"

enum GAMESTATUS
{
	GAME_INTRO,
	GAME_CHARSELECT,
	GAME_BATTLESTAGE
};

class playGround : public gameNode
{
private:
	PlayerManager* _kajama;
	EnemyManager* _em;
	ScoreManager* _sm;

	image* _introimg;
	image* _playerStatusimg;
	image* _characterSelectimg;
	image* _selectbutton;
	image* _backGround;
	image* _underCloud;
	image* _enemy1;
	image* _pushButton;

	int _loopX, _loopY;
	int _loopX2, _loopY2;
	bool _pushZ;

	GAMESTATUS _gameState;
	
	int _currentFrameX, _currentFrameY;	//인트로, 캐릭터 셀렉트 화면 넘겨줄변수.
	int _count;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용 함수
	virtual void render();	//그리기 전용 함수

	void StageSet();
	void collision();
	void ResetAircraft();
};

