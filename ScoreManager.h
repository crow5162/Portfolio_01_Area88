#pragma once
#include "gameNode.h"
#include "PlayerManager.h"

class PlayerManager;

class ScoreManager
{
private:

	PlayerManager* _pm;
	image* ins ;
	vector<int> _playerScore;

public:
	HRESULT init();
	vector<int> changeVectorFromInt(int num, vector<int> count);
	ScoreManager() {};
	~ScoreManager() {};
	void settingNumber(vector<int> _playerScore, float xPosition, float yPosition);
	void update();
	void render();
	void setPlayerManagerMemoryAddressLink(PlayerManager* pm) { _pm = pm; }
};

