#pragma once
#include "gameNode.h"

class progressBar : public gameNode
{
private:
	RECT _rcProgress;
	float _x, _y;
	float _width;

	image* _progressBarTop;			
	image* _progressBarBottom;		

	int currentGaugeX, maxGaugeX;

public:
	progressBar();
	~progressBar();

	HRESULT init(string name, float x, float y, int width, int height);
	void release();
	void update();
	void render();

	void setGauge(float currentGaugeX, float maxGaugeX);

	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }

	float getPBarWidth() { return _width; }
};

