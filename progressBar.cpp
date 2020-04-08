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
	

	string front, back;   
	front = name + "frontBar";
	back = name + "backBar";
	
	_progressBarTop = IMAGEMANAGER->findImage(front);
	_progressBarBottom = IMAGEMANAGER->findImage(back);

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

	_progressBarBottom->render(getMemDC(),
		_rcProgress.left,
		_y + _progressBarBottom->getHeight() / 2, 0, 0,
		_progressBarBottom->getWidth(), _progressBarBottom->getHeight());

	_progressBarTop->render( getMemDC(),
		_rcProgress.left ,
		_y + _progressBarBottom->getHeight() / 2, 0, 0,
		_width, _progressBarBottom->getHeight());

}

void progressBar::setGauge(float currentGaugeX, float maxGaugeX)
{
	_width = (currentGaugeX / maxGaugeX) * _progressBarBottom->getWidth();
}

