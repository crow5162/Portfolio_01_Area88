#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init(true);

	_gameState = GAME_INTRO;

	//에너미 프레임이미지 일단 여기서 초기화 시켜둠, 나중에 변경할것
	IMAGEMANAGER->addFrameImage("적헬기1", "Enemy_01_Final.bmp", 0, 0, 250, 95, 2, 2, true, RGB(255, 0, 255)); 
	IMAGEMANAGER->addFrameImage("적헬기2", "Enemy_02_Final.bmp", 0, 0, 250, 95, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("전투기", "Enemy_03_New.bmp", 0, 0, 3979, 85, 23, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스", "BOSS_01.bmp", 0, 0, 1200, 200, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("적탄환", "bullet.bmp", 25, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("적총알", "Enemy_Base_Bullet.bmp",0,0, 100, 50, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("힐템", "Item_PowerUp_Y.bmp",0,0,80,37, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("공템", "Item_Heal.bmp",0,0,80,37, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("진보스", "BOSS_Final.bmp", 0, 0, 1140, 184, 3, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("배경", "BackGround_Sky.bmp", WINSIZEX, WINSIZEY, false, RGB(0,0, 0));
	IMAGEMANAGER->addImage("언더", "Under_Cloud_Final.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("탑클", "Top_Cloud_Final.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_introimg = IMAGEMANAGER->addFrameImage("인트로", "Title.bmp", 10800, 800, 9, 1, false, RGB(255, 0, 255));
	_characterSelectimg = IMAGEMANAGER->addFrameImage("캐릭터 선택", "Player_Start.bmp",7600, 800, 19, 1, false, RGB(255, 0, 255));
	_characterSelectimg->setX(400);
	_characterSelectimg->setY(0);
	IMAGEMANAGER->addImage("Left_character", "Player_select_kajama.bmp", 400, 400, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Right_character", "player_select_whois.bmp", 400, 400, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Kajama_Ship", "Kajama_Aircraft.bmp", 350, 327, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Right_Ship", "Whois_Aircraft.bmp", 350, 336, true, RGB(255, 0, 255));
	_selectbutton = IMAGEMANAGER->addImage("SelectButton", "player_select_bottom.bmp", 130, 130, true, RGB(255, 0, 255));
	_selectbutton->setX(270);
	_selectbutton->setY(400);

	IMAGEMANAGER->addImage("UI", "Player_Status(Test).bmp", 626, 100, true, RGB(255, 0, 255)); //전투화면에서 떠있는 UI이미지.
	_pushButton = IMAGEMANAGER->addFrameImage("푸시버튼", "PUSH_BUTTON.bmp",1000,46, 2, 1, true, RGB(255, 0, 255));
	_pushButton->setX(WINSIZEX / 2 + 50);
	_pushButton->setY(WINSIZEY - 60);
	
	_loopX = _loopY = 0;
	_loopX2 = _loopY2 = 0;

	_currentFrameX = _currentFrameY = 0;
	_count = 0;

	_kajama = new PlayerManager;
	_kajama->init();

	_em = new EnemyManager;
	_em->init();

	_sm = new ScoreManager;
	_sm->init();

	_sm->setPlayerManagerMemoryAddressLink(_kajama);

	_kajama->setMemoryAddressLink(_em);
	_em->setPlayerManagerMemoryAddressLink(_kajama);


	_kajama->getBullet()->syncKajamaForPBulletWithKajama(_kajama);



	return S_OK;
}

void playGround::release()
{
	gameNode::release();

	SAFE_DELETE(_kajama);

}

void playGround::update()
{
	gameNode::update();

	if (KEYMANAGER->isOnceKeyDown(VK_DELETE)) this->init();

	if (_gameState == GAME_INTRO)
	{
		if (KEYMANAGER->isOnceKeyDown('Z')) _gameState = GAME_CHARSELECT;
	}

	if (_gameState == GAME_CHARSELECT)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			_selectbutton->setX(270);
			_selectbutton->setY(400);
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			_selectbutton->setX(800);
			_selectbutton->setY(400);
		}
		if (KEYMANAGER->isOnceKeyDown('Z')) 
		{
			_pushZ = true;
		}
		if (_currentFrameX >= _characterSelectimg->getMaxFrameX())
		{
			_gameState = GAME_BATTLESTAGE;
		}
	}

	if (_gameState == GAME_BATTLESTAGE)
	{
		_loopX += 10;
		_loopX2 += 20;
		_kajama->update();
		_em->update();
		_sm->update();
	}
	StageSet();
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//==================================================

	if (_gameState == GAME_INTRO)
	{
		_introimg->frameRender(getMemDC(), _introimg->getX(), _introimg->getY(), _currentFrameX, _currentFrameY);
	}
	if (_gameState == GAME_CHARSELECT)
	{
		IMAGEMANAGER->render("Kajama_Ship", getMemDC(), 25, 450);
		IMAGEMANAGER->render("Right_Ship", getMemDC(), 825, 450);
		IMAGEMANAGER->render("Right_character", getMemDC(), 800, 0);
		IMAGEMANAGER->render("Left_character", getMemDC(), 0, 0);
		_characterSelectimg->frameRender(getMemDC(), _characterSelectimg->getX(), _characterSelectimg->getY(), _currentFrameX, _currentFrameY);
		_selectbutton->render(getMemDC());
	}
	if (_gameState == GAME_BATTLESTAGE)
	{
		IMAGEMANAGER->findImage("배경")->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _loopX, _loopY);
		IMAGEMANAGER->findImage("언더")->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _loopX2, _loopY2);
		IMAGEMANAGER->findImage("탑클")->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _loopX2, _loopY2);
		IMAGEMANAGER->findImage("UI")->render(getMemDC());
		_pushButton->frameRender(getMemDC(), _pushButton->getX(),_pushButton->getY(), _currentFrameX, _currentFrameY);
		_kajama->render();
		_em->render();
		_sm->render();
	}
	//===================================================
	_backBuffer->render(getHDC(), 0, 0);
}

void playGround::StageSet()
{
	_count++;

	if (_count % 8 == 0)
	{
		if (_gameState == GAME_INTRO)
		{
			if (_currentFrameX >= _introimg->getMaxFrameX())
				_currentFrameX = 0;
			_introimg->setFrameX(_currentFrameX);
			_currentFrameX++;
			_count = 0;
		}

		if (_gameState == GAME_CHARSELECT)
		{
			if (_pushZ)
			{

				_characterSelectimg->setFrameX(_currentFrameX);
				_currentFrameX++;
				_count = 0;

			}
		}
	}
	if (_count % 50 == 0)
	{
		if (_gameState == GAME_BATTLESTAGE)
		{
			_pushButton->setFrameX(_currentFrameX);
			_currentFrameX++;
			_count = 0;
			if (_currentFrameX > _pushButton->getMaxFrameX()) _currentFrameX = 0;
		}
	}
	

}

void playGround::collision()
{
	
}

void playGround::ResetAircraft()
{
}
