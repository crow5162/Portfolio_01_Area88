#include "stdafx.h"
#include "ScoreManager.h"
#include"PlayerManager.h"

HRESULT ScoreManager::init()
{
	IMAGEMANAGER->addImage("0", "g_0.bmp", 30, 26 ,true, RGB(255,0,255));
										   	   
	IMAGEMANAGER->addImage("1", "g_1.bmp", 30, 26, true, RGB(255, 0, 255));
										   	   
	IMAGEMANAGER->addImage("2", "g_2.bmp", 30, 26, true, RGB(255, 0, 255));
										   	   
	IMAGEMANAGER->addImage("3", "g_3.bmp", 30, 26, true, RGB(255, 0, 255));
										   	   
	IMAGEMANAGER->addImage("4", "g_4.bmp", 30, 26, true, RGB(255, 0, 255));
										   	   
	IMAGEMANAGER->addImage("5", "g_5.bmp", 30, 26, true, RGB(255, 0, 255));
										   	   
	IMAGEMANAGER->addImage("6", "g_6.bmp", 30, 26, true, RGB(255, 0, 255));
										   	   
	IMAGEMANAGER->addImage("7", "g_7.bmp", 30, 26, true, RGB(255, 0, 255));
										   	   
	IMAGEMANAGER->addImage("8", "g_8.bmp", 30, 26, true, RGB(255, 0, 255));
										   	   
	IMAGEMANAGER->addImage("9", "g_9.bmp", 30, 26, true, RGB(255, 0, 255));

	_playerScore.push_back(0);
	return S_OK;
}

vector<int> ScoreManager::changeVectorFromInt(int num, vector<int> count)
{
	int j = num, i = 0;
	while (j)
	{
		if (count.size() > i)
		{
			if (count[i] != j % 10)
			{
				count[i] = j % 10;
			}
		}
		else
		{
			count.push_back(j % 10);
		}

		j /= 10;
		i++;
	}
	return count;
}



void ScoreManager::settingNumber(vector<int> _playerScore,float xPosition,float yPosition)
{
	for (int i = 0; i < _playerScore.size(); i++)
	{
		image* ins = new image;
		switch (_playerScore[i])
		{
		case 0:
			ins = IMAGEMANAGER->findImage("0");
			break;

		case 1:
			ins = IMAGEMANAGER->findImage("1");
			break;

		case 2:
			ins = IMAGEMANAGER->findImage("2");
			break;

		case 3:
			ins = IMAGEMANAGER->findImage("3");
			break;

		case 4:
			ins = IMAGEMANAGER->findImage("4");
			break;

		case 5:
			ins = IMAGEMANAGER->findImage("5");
			break;

		case 6:
			ins = IMAGEMANAGER->findImage("6");
			break;

		case 7:
			ins = IMAGEMANAGER->findImage("7");
			break;

		case 8:
			ins = IMAGEMANAGER->findImage("8");
			break;

		case 9:
			ins = IMAGEMANAGER->findImage("9");
			break;

		}
		ins->render(_backBuffer->getMemDC(), xPosition - ins->getWidth()*i, yPosition, 0, 0, ins->getWidth(), ins->getHeight());
	}
}

void ScoreManager::update()
{
	_playerScore = changeVectorFromInt(_pm->getScore(), _playerScore);
	
}

void ScoreManager::render()
{
	settingNumber(_playerScore,600,40);

}
