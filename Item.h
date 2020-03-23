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
	int _itemMax;			//ȭ��� �����Ҽ��ִ� �ִ� ������ ����
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

	void DropItem(float x, float y); //�������� ��𿡼� ����������.
	void removeItem(int arrNum);	 //�������� �������� ��. �� �Լ��־���.
	void collision();				 //�����۰� �浹������ ���⿡ �־�����ߴ�.(�ٵ� ���⼭ ���ϰ� �÷��̾�Ŵ������� ���δ���...
	bool ItemCountDrop();			 //�������� �������� Ȯ��.
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
	int _itemMax;			//ȭ��� �����Ҽ��ִ� �ִ� ������ ����
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

	void DropItem(float x, float y); //�������� ��𿡼� ����������.
	void removeItem(int arrNum);	 //�������� �������� ��.
	bool ItemCountDrop();			 //�������� �������� Ȯ��.
	void move();

	vector<tagItem>			  getVItem() { return _vItem; }
	vector<tagItem>::iterator getViItem() { return _viItem; }
};

