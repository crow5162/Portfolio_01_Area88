#pragma once
#include "gameNode.h"
#include <vector>

struct tagItem
{
	image* ItemImage;
	float x, y;
	bool isDrop;
	RECT rc;
	int count;
};

class HealItem : public gameNode
{
private:
	vector<tagItem>				_vItem;
	vector<tagItem>::iterator	_viItem;

	const char* _imageName;
	int _itemMax;			//화면상에 존재할수있는 최대 아이템 갯수
	int _fireCount;
	int _rndFireCount;

	bool _light;
public:
	HealItem() {};
	~HealItem() {};

	virtual HRESULT init(const char * imageName,int itemMax);
	virtual void release();
	virtual void update();
	virtual void render();

	void DropItem(float x, float y); //아이템이 어디에서 떨어질건지.
	void removeItem(int arrNum);	 //아이템이 지워질때 들어감. 이 함수넣어줌.
	void collision();				 //아이템과 충돌했을때 여기에 넣어보려고했다.(근데 여기서 안하고 플레이어매니저에서 전부다함...
	bool ItemCountDrop();			 //아이템이 떨어지는 확률.
	void move();

	vector<tagItem>			  getVItem()  { return _vItem; }
	vector<tagItem>::iterator getViItem() { return _viItem; }
};

class bulletSizeUpItem : public gameNode
{
private:
	vector<tagItem>				_vItem;
	vector<tagItem>::iterator	_viItem;

	const char* _imageName;
	int _itemMax;			//화면상에 존재할수있는 최대 아이템 갯수
	int _fireCount;
	int _rndFireCount;

	bool _light;
public:
	bulletSizeUpItem() {};
	~bulletSizeUpItem() {};

	virtual HRESULT init(const char * imageName, int itemMax);
	virtual void release();
	virtual void update();
	virtual void render();

	void DropItem(float x, float y); //아이템이 어디에서 떨어질건지.
	void removeItem(int arrNum);	 //아이템이 지워질때 들어감.
	bool ItemCountDrop();			 //아이템이 떨어지는 확률.
	void move();

	vector<tagItem>			  getVItem() { return _vItem; }
	vector<tagItem>::iterator getViItem() { return _viItem; }
};

