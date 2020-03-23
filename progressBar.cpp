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
	
	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	// ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	// (3) 이제 요 이닛 함수가 실행된다. 참고로 이 함수의 매개변수를 보면, string name 인자가 맨 앞에 추가되었다.
	// (4) 아래의 새로운 string형 변수 front, back에는 init함수에 인자로 넣어놓은 문자열과 'frontBar', 'backBar'가 이어붙여진다.

	string front, back;   // sting 자료형은 바로 초기화하면 위험!!!
	front = name + "frontBar";
	back = name + "backBar";
	
	//string temp;
	//temp = "ddd" + to_string(10);     *** 참고: to_string()은 변수를 string으로 바꿔준다. 왼쪽에서 temp는 "ddd10"이 나올 것.

	// (5) 그렇기 때문에 spaceship cpp 에서 키값 "spaceShipfrontBar"로 추가했던 이미지가 아래 findImage로 찾아진다.
	// 이제 이 문서 밑에 렌더로 가시오.
	_progressBarTop = IMAGEMANAGER->findImage(front);
	_progressBarBottom = IMAGEMANAGER->findImage(back);

	// ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■


	//뒤에 깔리는 게이지의 가로크기를 기준으로 삼는다
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
	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	// ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	// (6) 위에서 _progressBarTop과 _progressBarBottom 이미지를 찾아놓았으므로 그것을 바로 렌더한다.   끝!!! 

	_progressBarBottom->render(getMemDC(),
		_rcProgress.left,
		_y + _progressBarBottom->getHeight() / 2, 0, 0,
		_progressBarBottom->getWidth(), _progressBarBottom->getHeight());

	_progressBarTop->render( getMemDC(),
		_rcProgress.left ,
		_y + _progressBarBottom->getHeight() / 2, 0, 0,
		_width, _progressBarBottom->getHeight());

	// ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

}

void progressBar::setGauge(float currentGaugeX, float maxGaugeX)
{
	_width = (currentGaugeX / maxGaugeX) * _progressBarBottom->getWidth();
}

