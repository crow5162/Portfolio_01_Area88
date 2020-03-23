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
	_bullet->init("��źȯ", 1000, 1400);

	IMAGEMANAGER->addFrameImage("�ǰ�", "�� �Ѿ� �ı�.bmp", 220, 55, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�浹", "Bullet_Atype_Distroy.bmp", 768, 120, 5, 1, true, RGB(255, 0, 255));

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
	

	_setCount++;		//���͵��� �����ð����� ����ֱ����ؼ� ���� Count
	_typeCount++;		//�����ð����� ������ �Ѿ�� �ϱ����� ���� Count

	switch (_type) //�ð��� ������ ���� �ڵ����� ������ �Ѿ�����ִ� ����ġ �Դϴ�.
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
			heli->init("�����1", PointMake(WINSIZEX + 200 * i, WINSIZEY / 2 - 200));
			break;
		case PHASETWO:
			heli->init("�����1", PointMake(WINSIZEX + 200 * i, WINSIZEY / 2 + 200));
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
			heli->init("�����1", PointMake(WINSIZEX + 150 * i, WINSIZEY / 2 - 200), type);
			break;
		case PHASETWO:
			heli->init("�����1", PointMake(WINSIZEX + 80 * i, WINSIZEY / 2 - 200), type);
			break;
		case PHASETHREE:
			heli->init("�����1", PointMake((WINSIZEX - 300) + 100 * i,(-200) - 100 * i), type, i);
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
			redheli->init("�����2", PointMake(WINSIZEX + 150 * i, WINSIZEY / 2 + 200), type);
			break;
		case PHASETWO:
			redheli->init("�����2", PointMake(WINSIZEX + 80 * i, WINSIZEY / 2 + 200), type);
			break;
		case PHASETHREE:
			redheli->init("�����2", PointMake((WINSIZEX - 300) + 100 * i, (WINSIZEY + 200) + 100 * i), type, i);
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
			jet->init("������", PointMake(WINSIZEX, WINSIZEY / 2), type);
			break;
		case PHASETWO:
			jet->init("������", PointMake(WINSIZEX,300 + (200 * i)), type, i);
			break;
		case PHASETHREE:
			jet->init("������", PointMake(WINSIZEX,50 + (700 * i)), type, i);
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
		TITAN->init("������", PointMake(WINSIZEX + 200, WINSIZEY / 2), type);
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

//�浹ó�� �κ�
void EnemyManager::collision()
{
	//���ʹ��� �Ѿ��� ī�ڸ��� �浹������ ó��.
	//�浹������ ī�ڸ��� ü�� ����.
	for (int i = 0; i < _bullet->getVEnemyBullet().size(); i++)
	{
		RECT rc = RectMakeCenter(_kajama->getKajamaImage()->getCenterX(),
			_kajama->getKajamaImage()->getCenterY(),
			_kajama->getKajamaImage()->getFrameWidth()- 80,
			_kajama->getKajamaImage()->getFrameHeight()- 20);
		if (IntersectRect(&_bulletHit, &_bullet->getVEnemyBullet()[i].rc, &rc))
		{
			_kajama->hitDamage(10);

			eExplosion *eExp = new eExplosion;	//Enemy�� �Ѿ˰� kajama�� �浹������ ����Ʈ�� ��ġ��, �̹�����
												//���Ϳ� �����մϴ�.
			eExp->timeCount = 0;
			eExp->_explosion = IMAGEMANAGER->findImage("�ǰ�");
			eExp->_explosion->setX(_bullet->getVEnemyBullet()[i].rc.left);
			eExp->_explosion->setY(_bullet->getVEnemyBullet()[i].rc.top);
			eExp->frameX = 0;

			_vexplosion.push_back(eExp);

			_bullet->removeBullet(i);
			break;
		}
	}
	
	//�÷��̾�� ������ü�� �浹������ �� �����.
	//�浹������ ī�ڸ��� ü�� ����.
	for (int i = 0; i < _vAircraft.size(); i++)
	{
		RECT _rc = RectMakeCenter(_kajama->getKajamaImage()->getCenterX(),
			_kajama->getKajamaImage()->getCenterY(),
			_kajama->getKajamaImage()->getFrameWidth() - 80,
			_kajama->getKajamaImage()->getFrameHeight() - 20);

		if (IntersectRect(&_planeCrash, &getVAircraft()[i]->getRect(), &_rc))
		{
			eExplosion *cExp = new eExplosion;					//Enemy�� Kajama�� �浹������ �̹����� ��ǥ���� 
			cExp->_explosion = IMAGEMANAGER->findImage("�浹"); //���Ϳ� �����մϴ�.
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

//Enemy �Ѿ� �߻� 
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
						if( getVAircraft()[i]->getmCurrHP() < 5001) //������ 1 �Ϲ� �߻� (�ӵ�����)
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

//ȭ������� ������ ���ʹ� Delete
void EnemyManager::DeleteMonster()
{
	//������ü���� ���ͷ� �ٷ�Ʈ���ͼ� ȭ������� ������ Erase�ǰ� ������ݴϴ�.
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
