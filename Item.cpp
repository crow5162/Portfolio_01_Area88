#include "stdafx.h"
#include "Item.h"

HRESULT HealItem::init(const char * imageName, int itemMax)
{
	_imageName = imageName;
	_itemMax = itemMax;
	_fireCount = 0;
	_rndFireCount = RND->getFromIntTo(1, 10);

	return S_OK;
}

void HealItem::release()
{
}

void HealItem::update()
{
	move();
}

void HealItem::render()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		_viItem->ItemImage->frameRender(getMemDC(), _viItem->rc.left,_viItem->rc.top,
											_light, 0);
		_light = !_light;
		_viItem->count++;

		if (_viItem->count % 20 == 0)
		{
			_viItem->ItemImage->setFrameX(_viItem->ItemImage->getFrameX() + 1);
			if (_viItem->ItemImage->getFrameX() >= _viItem->ItemImage->getMaxFrameX())
			{
				_viItem->ItemImage->setFrameX(0);
			}

			_viItem->count = 0;
		}
	}
}

void HealItem::DropItem(float x, float y)
{
	if (_itemMax < _vItem.size()) return;

	tagItem healItem;
	ZeroMemory(&healItem, sizeof(tagItem));
	healItem.ItemImage = IMAGEMANAGER->findImage(_imageName);
	healItem.x = x;
	healItem.y = y;

	healItem.rc = RectMakeCenter(healItem.x, healItem.y,
		healItem.ItemImage->getFrameWidth(),
		healItem.ItemImage->getFrameHeight());

	_vItem.push_back(healItem);
}

void HealItem::removeItem(int arrNum)
{
	_vItem.erase(_vItem.begin() + arrNum);
}

void HealItem::collision()
{
}

bool HealItem::ItemCountDrop()
{
	_fireCount++;

	if (_fireCount % _rndFireCount == 0)
	{
		_fireCount = 0;
		_rndFireCount = RND->getFromIntTo(1, 10);

		return true;
	}

	return false;
}

void HealItem::move()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end();)
	{
		_viItem->x -= 4;

		_viItem->rc = RectMakeCenter(_viItem->x, _viItem->y,
			_viItem->ItemImage->getFrameWidth(),
			_viItem->ItemImage->getFrameHeight());

		++_viItem;
	}
}

HRESULT bulletSizeUpItem::init(const char * imageName, int itemMax)
{
	_imageName = imageName;
	_itemMax = itemMax;
	_fireCount = 0;
	_rndFireCount = RND->getFromIntTo(1, 10);

	return S_OK;
}

void bulletSizeUpItem::release()
{
}

void bulletSizeUpItem::update()
{
	move();
}

void bulletSizeUpItem::render()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		_viItem->ItemImage->frameRender(getMemDC(),
			_viItem->rc.left,
			_viItem->rc.top,
			_light, 0);

		_light = !_light;
		_viItem->count++;

		if (_viItem->count % 20 == 0)
		{
			_viItem->ItemImage->setFrameX(_viItem->ItemImage->getFrameX() + 1);

			if (_viItem->ItemImage->getFrameX() >= _viItem->ItemImage->getMaxFrameX())
			{
				_viItem->ItemImage->setFrameX(0);
			}
			_viItem->count = 0;
		}
	}
}

void bulletSizeUpItem::DropItem(float x, float y)
{
	if (_itemMax < _vItem.size()) return;

	tagItem sizeupItem;
	ZeroMemory(&sizeupItem, sizeof(tagItem));
	sizeupItem.ItemImage = IMAGEMANAGER->findImage(_imageName);
	sizeupItem.x = x;
	sizeupItem.y = y;

	sizeupItem.rc = RectMakeCenter(sizeupItem.x, sizeupItem.y,
		sizeupItem.ItemImage->getFrameWidth(),
		sizeupItem.ItemImage->getFrameHeight());

	_vItem.push_back(sizeupItem);
}

void bulletSizeUpItem::removeItem(int arrNum)
{
	_vItem.erase(_vItem.begin() + arrNum);
}

bool bulletSizeUpItem::ItemCountDrop()
{
	_fireCount++;

	if (_fireCount % _rndFireCount == 0)
	{
		_fireCount = 0;
		_rndFireCount = RND->getFromIntTo(1, 30);

		return true;
	}
	return false;
}

void bulletSizeUpItem::move()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end();)
	{
		_viItem->x -= 4;

		_viItem->rc = RectMakeCenter(_viItem->x, _viItem->y,
			_viItem->ItemImage->getFrameWidth(),
			_viItem->ItemImage->getFrameHeight());

		++_viItem;
	}
}
