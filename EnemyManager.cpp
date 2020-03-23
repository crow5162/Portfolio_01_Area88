#include "stdafx.h"
#include "EnemyManager.h"
#include "PlayerManager.h"

EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
}

HRESULT EnemyManager::init()
{
	_type = PHASEONE;
	_setCount = 0;
	_typeCount = 0;
	_bossCount = 0;
	_Bbulletcnt = 0;
	_angle = PI;

	_bullet = new EnemyBullet;
	_bullet->init("적탄환", 1000, 1400);

	IMAGEMANAGER->addFrameImage("피격", "적 총알 파괴.bmp", 220, 55, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("충돌", "Bullet_Atype_Distroy.bmp", 768, 120, 5, 1, true, RGB(255, 0, 255));

	return S_OK;

}

void EnemyManager::release()
{
}

void EnemyManager::update()
{
	for (_viAircraft = _vAircraft.begin(); _viAircraft != _vAircraft.end(); ++_viAircraft)
	{
		(*_viAircraft)->update();
	}
	

	_setCount++;		//몬스터들을 일정시간마다 깔아주기위해서 만든 Count
	_typeCount++;		//일정시간마다 페이즈 넘어가게 하기위해 만든 Count

	switch (_type) //시간이 지남에 따라 자동으로 페이즈 넘어가게해주는 스위치 입니다.
	{
	case PHASEONE:
		if (_setCount % 200 == 0)
		{
			setAircraft(PHASEONE);
			setRedAircraft(PHASEONE);
		}
		if (_setCount % 250 == 0)
		{
			setJet(PHASEONE);
		}
		if (_typeCount > 1000 && _typeCount < 2200) _type = PHASETWO;
		break;
	case PHASETWO:
		if (_setCount % 200 == 0)
		{
			setAircraft(PHASETWO);
			setRedAircraft(PHASETWO);
		}
		if (_setCount % 250 == 0)
		{
			setJet(PHASETWO);
		if (_typeCount > 2200 && _typeCount < 3300) _type = PHASETHREE;
		}
		break;
	case PHASETHREE:
		if (_setCount % 200 == 0 && _typeCount < 3100)
		{
			setAircraft(PHASETHREE);
			setRedAircraft(PHASETHREE);
		}
		if (_setCount % 250 == 0 && _typeCount < 3100)
		{
			setJet(PHASETHREE);
		}
		if (_typeCount > 3300) _type = PHASEBOSS;
		break;
	case PHASEBOSS:
		if (!_setBoss)
		{
			setBoss(PHASEBOSS);
			_setBoss = true;
			
		}
		break;
	default:
		break;
	}

	_bullet->update();
	EnemyBulletfire();
	collision();
	DeleteMonster();
}

void EnemyManager::render()
{
	for (_viAircraft = _vAircraft.begin(); _viAircraft != _vAircraft.end(); ++_viAircraft)
	{
		(*_viAircraft)->render();
	}

	_bullet->render();
	

	for (int i = 0; i < _vexplosion.size(); i++)
	{
		_vexplosion[i]->_explosion->frameRender(getMemDC(), _vexplosion[i]->_explosion->getX(), _vexplosion[i]->_explosion->getY(),
			_vexplosion[i]->frameX, 0);
		_vexplosion[i]->timeCount++;
		if (_vexplosion[i]->frameX < _vexplosion[i]->_explosion->getMaxFrameX() && _vexplosion[i]->timeCount % 5 == 0)
		{
			_vexplosion[i]->frameX++;
		}
		else if (_vexplosion[i]->frameX == _vexplosion[i]->_explosion->getMaxFrameX())
		{
			_vexplosion.erase(_vexplosion.begin() + i);
		}
	}
}

void EnemyManager::setAircraft()
{

	for (int i = 0; i < 3; i++)
	{
		enemy* heli;
		heli = new helicopter;
		switch (_type)
		{
		case PHASEONE:
			heli->init("적헬기1", PointMake(WINSIZEX + 200 * i, WINSIZEY / 2 - 200));
			break;
		case PHASETWO:
			heli->init("적헬기1", PointMake(WINSIZEX + 200 * i, WINSIZEY / 2 + 200));
			break;
		case PHASETHREE:
			break;
		default:
			break;
		}
		_vAircraft.push_back(heli);
	}
	
}

void EnemyManager::setAircraft(PHASETYPE type)
{
	for (int i = 0; i < 3; i++)
	{
		enemy* heli;
		heli = new helicopter;
		switch (_type)
		{
		case PHASEONE:
			heli->init("적헬기1", PointMake(WINSIZEX + 150 * i, WINSIZEY / 2 - 200), type);
			break;
		case PHASETWO:
			heli->init("적헬기1", PointMake(WINSIZEX + 80 * i, WINSIZEY / 2 - 200), type);
			break;
		case PHASETHREE:
			heli->init("적헬기1", PointMake((WINSIZEX - 300) + 100 * i,(-200) - 100 * i), type, i);
			break;
		default:
			break;
		}

		_vAircraft.push_back(heli);
	}

}

void EnemyManager::removeAircraft(int arrNum)
{
	_vAircraft.erase(_vAircraft.begin() + arrNum);
}

void EnemyManager::setRedAircraft(PHASETYPE type)
{

	for (int i = 0; i < 3; i++)
	{
		enemy* redheli;
		redheli = new helicopter2;
		switch (_type)
		{
		case PHASEONE:
			redheli->init("적헬기2", PointMake(WINSIZEX + 150 * i, WINSIZEY / 2 + 200), type);
			break;
		case PHASETWO:
			redheli->init("적헬기2", PointMake(WINSIZEX + 80 * i, WINSIZEY / 2 + 200), type);
			break;
		case PHASETHREE:
			redheli->init("적헬기2", PointMake((WINSIZEX - 300) + 100 * i, (WINSIZEY + 200) + 100 * i), type, i);
			break;
		default:
			break;
		}
		
		_vAircraft.push_back(redheli);
	}


}

void EnemyManager::removeRedAircraft(int arrNum)
{
	_vAircraft.erase(_vAircraft.begin() + arrNum);
}

void EnemyManager::setJet(PHASETYPE type)
{
	for (int i = 0; i < 2; i++)
	{
		enemy* jet;
		jet = new jetplane;
		switch (_type)
		{
		case PHASEONE:
			i = 2; 
			jet->init("전투기", PointMake(WINSIZEX, WINSIZEY / 2), type);
			break;
		case PHASETWO:
			jet->init("전투기", PointMake(WINSIZEX,300 + (200 * i)), type, i);
			break;
		case PHASETHREE:
			jet->init("전투기", PointMake(WINSIZEX,50 + (700 * i)), type, i);
			break;
		default:
			break;
		}
		_vAircraft.push_back(jet);
	}
}

void EnemyManager::removeJet(int arrNum)
{
	_vAircraft.erase(_vAircraft.begin() + arrNum);
}

void EnemyManager::setBoss(PHASETYPE type)
{
	enemy* TITAN;
	TITAN = new BOSS;

	switch (_type)
	{
	case PHASEONE:

		break;
	case PHASETWO:

		break;
	case PHASETHREE:

		break;
	case PHASEBOSS:
		TITAN->init("진보스", PointMake(WINSIZEX + 200, WINSIZEY / 2), type);
		TITAN->setHP(5000,5000); 
		_bossCount += 1;
		break;
	default:
		break;
	}
	
	_vAircraft.push_back(TITAN);
	sprintf_s(buf, "BOSS COUNT : %d", _bossCount);

}

void EnemyManager::removeBoss(int arrNum)
{
	_vAircraft.erase(_vAircraft.begin() + arrNum);
}

//충돌처리 부분
void EnemyManager::collision()
{
	//에너미의 총알이 카자마와 충돌했을시 처리.
	//충돌했을시 카자마의 체력 감소.
	for (int i = 0; i < _bullet->getVEnemyBullet().size(); i++)
	{
		RECT rc = RectMakeCenter(_kajama->getKajamaImage()->getCenterX(),
			_kajama->getKajamaImage()->getCenterY(),
			_kajama->getKajamaImage()->getFrameWidth()- 80,
			_kajama->getKajamaImage()->getFrameHeight()- 20);
		if (IntersectRect(&_bulletHit, &_bullet->getVEnemyBullet()[i].rc, &rc))
		{
			_kajama->hitDamage(10);

			eExplosion *eExp = new eExplosion;	//Enemy의 총알과 kajama가 충돌했을시 이펙트의 위치와, 이미지를
												//벡터에 저장합니다.
			eExp->timeCount = 0;
			eExp->_explosion = IMAGEMANAGER->findImage("피격");
			eExp->_explosion->setX(_bullet->getVEnemyBullet()[i].rc.left);
			eExp->_explosion->setY(_bullet->getVEnemyBullet()[i].rc.top);
			eExp->frameX = 0;

			_vexplosion.push_back(eExp);

			_bullet->removeBullet(i);
			break;
		}
	}
	
	//플레이어와 적비행체와 충돌했을때 적 사라짐.
	//충돌했을시 카자마의 체력 감소.
	for (int i = 0; i < _vAircraft.size(); i++)
	{
		RECT _rc = RectMakeCenter(_kajama->getKajamaImage()->getCenterX(),
			_kajama->getKajamaImage()->getCenterY(),
			_kajama->getKajamaImage()->getFrameWidth() - 80,
			_kajama->getKajamaImage()->getFrameHeight() - 20);

		if (IntersectRect(&_planeCrash, &getVAircraft()[i]->getRect(), &_rc))
		{
			eExplosion *cExp = new eExplosion;					//Enemy와 Kajama가 충돌했을시 이미지와 좌표값을 
			cExp->_explosion = IMAGEMANAGER->findImage("충돌"); //벡터에 저장합니다.
			cExp->_explosion->setX(_kajama->getRect().left);
			cExp->_explosion->setY(_kajama->getRect().top);
			cExp->frameX = 0;
			_vexplosion.push_back(cExp);

			_vAircraft.erase(_vAircraft.begin() + i);
			_kajama->hitDamage(30);
			break;
		}
	}
}

void EnemyManager::AircraftReset()
{
	if (_vAircraft.size() == 0)
	{
		setAircraft();
	}
}

//Enemy 총알 발사 
void EnemyManager::EnemyBulletfire()
{
	for (_viAircraft = _vAircraft.begin(); _viAircraft != _vAircraft.end(); ++_viAircraft)
	{
			RECT rc = (*_viAircraft)->getRect();
		if ((*_viAircraft)->bulletCountFire()) 
		{

			if (_type <= 2)		
			{
				_bullet->bulletFire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + 5,
					getAngle((rc.left + rc.right) / 2,
							(rc.top + rc.bottom) / 2,
						_kajama->getKajamaImage()->getCenterX(),
						_kajama->getKajamaImage()->getCenterY() - 30),
					15.0f);
			}
		}
		_Bbulletcnt++;
			float _bAngle = 0; 
			for (int i = 0; i < getVAircraft().size(); i++)		
			{
				if (_type == 3)
				{
					if (_Bbulletcnt >= 15) 
					{
						if (getVAircraft()[i]->getmCurrHP() < 1800)
						{
							for (int j = 0; j < 25; j++)
							{
								_bAngle += PI * 2 / 25;
								_bullet->bulletFire(rc.left + (rc.right - rc.left) / 2,
									rc.bottom - 50,
									_bAngle,
									20.0f);
							}
						}
						if (getVAircraft()[i]->getmCurrHP() < 3200)	
						{
							if (_angle <  PI*( 4/ 3))	_goRight = true;
							else if (_angle > PI*(8/5)) _goRight = false;
							if (_Bbulletcnt >= 5)
							{
								if (!_goRight)
								{
									_angle -= 0.2f;
								}
								else _angle += 0.2f;
								_bullet->bulletFire(rc.left + (rc.right - rc.left) / 2,
									rc.bottom - 50,
									_angle,
									3.0f);
							}
						}
						if( getVAircraft()[i]->getmCurrHP() < 5001) //페이즈 1 일반 발사 (속도빠름)
						{
							_bullet->bulletFire(rc.left + (rc.right - rc.left) / 2,
								rc.bottom - 50,
								getAngle((rc.left + rc.right) / 2,
								(rc.top + rc.bottom) / 2,
									_kajama->getKajamaImage()->getCenterX(),
									_kajama->getKajamaImage()->getCenterY() - 40),
								25.0f);
						}
						_Bbulletcnt = 0;
					}
					
				}
			}
	}
}

//화면밖으로 나가면 에너미 Delete
void EnemyManager::DeleteMonster()
{
	//적비행체들의 벡터로 겟렉트얻어와서 화면밖으로 나가면 Erase되게 만들어줍니다.
	for (_viAircraft = _vAircraft.begin(); _viAircraft != _vAircraft.end();)
	{
		if ((*_viAircraft)->getRect().right < -100 || (*_viAircraft)->getRect().left > WINSIZEX + 100)
		{
			_viAircraft = _vAircraft.erase(_viAircraft);
		}
		else
		{
			_viAircraft++;
		}
	}
	
}
