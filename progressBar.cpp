#include "stdafx.h"
#include "progressBar.h"

#include <string>

progressBar::progressBar()
{
}

progressBar::~progressBar()
{
}

HRESULT progressBar::init(string name, float x, float y, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMake(x, y, width, height);
	
	// ����������������������������������������������������
	// ����������������������������������������������������
	// ����������������������������������������������������
	// (3) ���� �� �̴� �Լ��� ����ȴ�. ����� �� �Լ��� �Ű������� ����, string name ���ڰ� �� �տ� �߰��Ǿ���.
	// (4) �Ʒ��� ���ο� string�� ���� front, back���� init�Լ��� ���ڷ� �־���� ���ڿ��� 'frontBar', 'backBar'�� �̾�ٿ�����.

	string front, back;   // sting �ڷ����� �ٷ� �ʱ�ȭ�ϸ� ����!!!
	front = name + "frontBar";
	back = name + "backBar";
	
	//string temp;
	//temp = "ddd" + to_string(10);     *** ����: to_string()�� ������ string���� �ٲ��ش�. ���ʿ��� temp�� "ddd10"�� ���� ��.

	// (5) �׷��� ������ spaceship cpp ���� Ű�� "spaceShipfrontBar"�� �߰��ߴ� �̹����� �Ʒ� findImage�� ã������.
	// ���� �� ���� �ؿ� ������ ���ÿ�.
	_progressBarTop = IMAGEMANAGER->findImage(front);
	_progressBarBottom = IMAGEMANAGER->findImage(back);

	// ����������������������������������������������������
	// ����������������������������������������������������
	// ����������������������������������������������������


	//�ڿ� �򸮴� �������� ����ũ�⸦ �������� ��´�
	_width = _progressBarBottom->getWidth();

	return S_OK;
}

void progressBar::release()
{
}

void progressBar::update()
{
	_rcProgress = RectMake(_x, _y, _progressBarTop->getWidth(), _progressBarBottom->getHeight());
}

void progressBar::render()
{
	// ����������������������������������������������������
	// ����������������������������������������������������
	// ����������������������������������������������������
	// (6) ������ _progressBarTop�� _progressBarBottom �̹����� ã�Ƴ������Ƿ� �װ��� �ٷ� �����Ѵ�.   ��!!! 

	_progressBarBottom->render(getMemDC(),
		_rcProgress.left,
		_y + _progressBarBottom->getHeight() / 2, 0, 0,
		_progressBarBottom->getWidth(), _progressBarBottom->getHeight());

	_progressBarTop->render( getMemDC(),
		_rcProgress.left ,
		_y + _progressBarBottom->getHeight() / 2, 0, 0,
		_width, _progressBarBottom->getHeight());

	// ����������������������������������������������������
	// ����������������������������������������������������
	// ����������������������������������������������������

}

void progressBar::setGauge(float currentGaugeX, float maxGaugeX)
{
	_width = (currentGaugeX / maxGaugeX) * _progressBarBottom->getWidth();
}

