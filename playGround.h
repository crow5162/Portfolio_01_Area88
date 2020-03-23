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
	
	int _currentFrameX, _currentFrameY;	//��Ʈ��, ĳ���� ����Ʈ ȭ�� �Ѱ��ٺ���.
	int _count;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ���� �Լ�
	virtual void render();	//�׸��� ���� �Լ�

	void StageSet();
	void collision();
	void ResetAircraft();
};

