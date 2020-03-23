#include "stdafx.h"
#include "PlayerManager.h"
#include "EnemyManager.h"

PlayerManager::PlayerManager()
{

}

PlayerManager::~PlayerManager()
{

}

HRESULT PlayerManager::init()
{
	_kajama = IMAGEMANAGER->addFrameImage("RIGHT", "player right.bmp", 400, 41, 3, 1, true, RGB(255, 0, 255));
	_kajama->setX(WINSIZEX / 2 - 400);
	_kajama->setY(WINSIZEY / 2);
	_kajamaState = PLAYER_RIGHT;//카자마의 처음 상태.
	
	IMAGEMANAGER->addFrameImage("UP", "player up.bmp", 532, 45, 4, 1, true, RGB(255, 0, 255)); //카자마의 상태별 이미지
	IMAGEMANAGER->addFrameImage("DOWN", "player down.bmp", 532, 45, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RIGHTFIRE", "Player_Right_Fire_RE.bmp", 786, 35, 6, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("kajamafrontBar", "Front_HP.bmp", 200, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("kajamabackBar", "Back_HP.bmp", 200, 24, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("폭발이펙", "Enemy_Death.bmp", 495, 120, 4, 1, true, RGB(255, 0, 255));

	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ SCREEN ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	_screen = IMAGEMANAGER->addImage("NORMAL", "Player_state_Normal.bmp", 168, 96, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("HIT", "Player_state_Hit.bmp", 336, 97, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("DANGER", "Player_state_Danger.bmp", 504, 96, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("DEATH", "Player_state_ShotDown.bmp", 2184, 96, 13, 1, true, RGB(255, 0, 255));
	_screen->setX(255);
	_screen->setY(0);
	_ps = NORMAL;
	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	_hpBar = new progressBar; //카자마의 체력바 세팅.
	_hpBar->init("kajama", 50, 725, 200, 24);
	_currentHP = _maxHP = 300;

	_currentFrameX = _currentFrameY = 0;
	_currentFrameX2 = _currentFrameY2 = 0;
	_currentFrameX4 = _currentFrameY4 = 0;
	_currentFrameX5 = _currentFrameY5 = 0;
	_count = 0;
	_count2 = 0;
	_count3 = 0;
	_count4 = 0;
	_returnCount = 0;

	_fireCount = 0;


	_rc = RectMakeCenter(_kajama->getX(), _kajama->getY(), 120, 30);	//카자마이미지 따라다닐 렉트 선언.

	_bullet = new PlayerBullet;
	_bullet->init(30, 1200);

	_healItem = new HealItem;
	_healItem->init("힐템", 10);
	_bcount = 0;
	_playerScore = 0;

	_sizeupItem = new bulletSizeUpItem;
	_sizeupItem->init("공템", 5);

	return S_OK;
}

HRESULT PlayerManager::init(const char * imageName, POINT position)
{

	return S_OK;
}

void PlayerManager::release()
{

}

void PlayerManager::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _kajama->getX() + _kajama->getFrameWidth() < WINSIZEX)
	{
		_kajamaState = PLAYER_RIGHT;
		_rc.left += 6;
		_rc.right += 6;
		_kajama->setFrameY(0);
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _kajama->getX() > 0)
	{
		_kajamaState = PLAYER_LEFT;
		_rc.left -= 6;
		_rc.right -= 6;

	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _kajama->getY() > 0)
	{
		_kajamaState = PLAYER_UP;
		_rc.top -= 6;
		_rc.bottom -= 6;
		_kajama->setFrameY(0);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _kajama->getY() + _kajama->getFrameHeight() < WINSIZEY)
	{
		_kajamaState = PLAYER_DOWN;
		_rc.top += 6;
		_rc.bottom += 6;
		_kajama->setFrameY(0);
	}
	if (KEYMANAGER->isStayKeyDown(VK_SPACE))
	{
		_kajamaState = PLAYER_RIGHTFIRE;
		_kajama->setFrameY(0);

		if (!_isFire)
		{
			_bullet->fire(_kajama->getCenterX() + 50, _kajama->getCenterY());
			_isFire = true;
			//_kajamaState = PLAYER_RIGHTFIRE;
		}
		_fireCount++;
		if (_fireCount == 10)
		{
			_isFire = false;
			_fireCount = 0;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_SPACE))
	{
		_kajamaState = PLAYER_RIGHT;
	}

	_bullet->update();
	MoveMotion();
	_kajama->setX(_rc.left);	
	_kajama->setY(_rc.top);
	collision();
	_hpBar->update();
	_hpBar->setGauge(_currentHP, _maxHP);

	_healItem->update();	//아이템들 업데이트 입니다.
	_sizeupItem->update();
	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	
	KajamaScreen();

}

void PlayerManager::render()
{
	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 카자마의 움직임 렌더
	if (_kajamaState == PLAYER_LEFT || _kajamaState == PLAYER_RIGHT || _kajamaState == PLAYER_RIGHTFIRE)	//레프트, 라이트 상태 이미지 렌더.
	{
		_kajama->frameRender(getMemDC(), _kajama->getX(), _kajama->getY(), _currentFrameX, _currentFrameY);
	}
	if (_kajamaState == PLAYER_UP || _kajamaState == PLAYER_DOWN)		//옵, 다운 상태 이미지 렌더.
	{
		_kajama->frameRender(getMemDC(), _kajama->getX(), _kajama->getY(), _currentFrameX2, _currentFrameY2);
	}
	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 카자마 스크린의 렌더
	if (_ps == NORMAL)
	{
		_screen->render(getMemDC());
	}
	if (_ps == HIT || _ps != DEATH)
	{
		_screen->frameRender(getMemDC(), _screen->getX(), _screen->getY(), _currentFrameX3, _currentFrameY3);
	}
	if (_ps == DANGER)
	{
		_screen->frameRender(getMemDC(), _screen->getX(), _screen->getY(), _currentFrameX4, _currentFrameY4);
	}
	if (_ps == DEATH)
	{
		const char aaa[100] = "민욱이는 똥싸개";
			_screen->frameRender(getMemDC(), _screen->getX(), _screen->getY(), _currentFrameX5, _currentFrameY5);
			/*_screen->setFrameX(_screen->getFrameX() + 1);*/
			if (_currentFrameX5 < _screen->getMaxFrameX()) {
				_currentFrameX5++;
			}
	}

	_bullet->render();

	_hpBar->render();

	_healItem->render();
	_sizeupItem->render();

	for (int i = 0; i < _vexplosion.size(); i++)
	{
		_vexplosion[i]->explosion->frameRender(getMemDC(), _vexplosion[i]->explosion->getX(), _vexplosion[i]->explosion->getY(),
			_vexplosion[i]->frameX, 0);

		_vexplosion[i]->timecount++;

		if (_vexplosion[i]->frameX < _vexplosion[i]->explosion->getMaxFrameX() && _vexplosion[i]->timecount % 5 == 0)
		{
			_vexplosion[i]->frameX++;
		}
		else if (_vexplosion[i]->frameX == _vexplosion[i]->explosion->getMaxFrameX())
		{
			_vexplosion.erase(_vexplosion.begin() + i);
		}
	}
}

void PlayerManager::KajamaScreen()
{
	switch (_ps)
	{
	case NORMAL:
		_screen = IMAGEMANAGER->findImage("NORMAL");
		break;
	case HIT:
		_screen = IMAGEMANAGER->findImage("HIT");
		_screen->setX(255);
		_screen->setY(0);
		break;
	case DANGER:
		_screen = IMAGEMANAGER->findImage("DANGER");
		_screen->setX(255);
		_screen->setY(0);
		break;
	case DEATH:
		_screen = IMAGEMANAGER->findImage("DEATH");
		_screen->setX(255);
		_screen->setY(0);
		break;
	default:
		break;
	}
}

void PlayerManager::collision()
{
	for (int i = 0; i < _em->getVAircraft().size(); i++)
	{
		for (int j = 0; j < _bullet->getVBullet().size(); j++)
		{
			RECT temp;
			if (IntersectRect(&temp, &_bullet->getVBullet()[j].rc, &_em->getVAircraft()[i]->getRect()))
			{
				_em->getVAircraft()[i]->minionDamage(50);

				if (_em->getVAircraft()[i]->getmCurrHP() <= 0)
				{

					EXPLOSION *Ro = new EXPLOSION;

					Ro->timecount = 0;
					Ro->explosion = IMAGEMANAGER->findImage("폭발이펙");
					Ro->explosion->setX(_em->getVAircraft()[i]->getRect().left);
					Ro->explosion->setY(_em->getVAircraft()[i]->getRect().top);
					Ro->frameX = 0;

					_vexplosion.push_back(Ro);

					_em->removeAircraft(i);
					
					if (_healItem->ItemCountDrop())		//적비행체를 부수고 item 카운트에 걸리면 힐링아이템을 생성합니다.
					{
						_healItem->DropItem(temp.left, temp.top); //힐 아이템 드랍 (temp위치에
					}
					if (_sizeupItem->ItemCountDrop())
					{
						_sizeupItem->DropItem(temp.left, temp.top); //불릿업그레이드 아이템 드랍 (temp 위치에
					}

					_playerScore += 750;
				}
				_bullet->removeBullet(j);
				break;
			}
		}
	}

	//■■■■■■■■■■■■■■■■■■■■■아이템과 충돌부분■■■■■■■■■■■■■■■■■■■■■■■■■

	for (int i = 0; i < _healItem->getVItem().size(); i++) 
	{
		RECT _temp2;
		if (IntersectRect(&_temp2, &_healItem->getVItem()[i].rc, &_rc))
		{
			_healItem->removeItem(i);
			
			_bcount++;
		}
	}

	for (int i = 0; i < _sizeupItem->getVItem().size(); i++)
	{
		RECT _temp3;
		if (IntersectRect(&_temp3, &_sizeupItem->getVItem()[i].rc, &_rc))
		{
			_sizeupItem->removeItem(i);

			if (_currentHP < _maxHP)
			{
				_currentHP += 100;
			}
			if (_currentHP > _maxHP)
			{
				_currentHP = _maxHP;
			}
		}
	}
}

void PlayerManager::MoveMotion()
{
	switch (_kajamaState)		//플레이어의 상태에 따른 이미지를 불러옵니다.
	{
	case PLAYER_RIGHT:	case PLAYER_LEFT:

		_kajama = IMAGEMANAGER->findImage("RIGHT");

		break;

	case PLAYER_UP:

		_kajama = IMAGEMANAGER->findImage("UP");

		break;

	case PLAYER_DOWN:

		_kajama = IMAGEMANAGER->findImage("DOWN");

		break;
	case PLAYER_RIGHTFIRE:

		_kajama = IMAGEMANAGER->findImage("RIGHTFIRE");

		break;
	}
	_count++;
	_count2++;
	_count4++;
	if (_ps == HIT)
	{
		_count3++;
	}

	if (_count % 4 == 0)
	{
		if (_kajamaState == PLAYER_LEFT || _kajamaState == PLAYER_RIGHT || _kajamaState == PLAYER_RIGHTFIRE)
		{
			if (_currentFrameX >= _kajama->getMaxFrameX())
				_currentFrameX = 0;
			_kajama->setFrameX(_currentFrameX);
			_currentFrameX++;
			_count = 0;
			_currentFrameX2 = 0;
			_currentFrameY2 = 0;
		}
	}
	if(_count2 % 10 == 0)
	{

		if(_kajamaState == PLAYER_UP || _kajamaState == PLAYER_DOWN)
		{

			_kajama->setFrameX(_currentFrameX2);
			_currentFrameX2++;
			_count = 0;
			if (_currentFrameX2 >= _kajama->getMaxFrameX())
			{
				_currentFrameX2 = 3;
			}
		}
	}
	if (_count3 % 10 == 0)
	{
		if (_ps == HIT)
		{
			_screen->setFrameX(_currentFrameX3);
			_currentFrameX3++;


			if (_currentFrameX3 > _screen->getMaxFrameX())
			{
				_currentFrameX3 = 0;
			}
			if (_count3 > 100) //일정카운트 지나면 다시 NORMAL상태로 돌아온다.
			{
				_ps = NORMAL;
				_count3 = 0;
			}
		}
	}
	if (_count4 % 10 == 0)
	{
		if (_ps == DANGER && _ps !=DEATH)
		{
			_screen->setFrameX(_currentFrameX4);
			_currentFrameX4++;
			_count4 = 0;
			if (_currentFrameX4 >= _screen->getMaxFrameX())
			{
				_currentFrameX4 = 0;
			}
		}
		
	}

	if (_currentHP > 0 && _currentHP < 50 && _ps != DEATH && !_isDead)
	{
		_ps = DANGER;
	}
	else if (_currentHP > 50 && _ps != HIT && _ps !=DEATH && !_isDead)
	{
		_ps = NORMAL;
	}
	if (_currentHP <= 0 && _ps != DEATH && !_isDead)
	{
		_ps = DEATH;
	}
	
}

void PlayerManager::hitDamage(float damage)
{
	_currentHP -= damage;
	if (_currentHP < 0) _currentHP = 0;
	if(_ps!=DEATH)_ps = HIT;
	_returnCount++;
}
