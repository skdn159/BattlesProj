#pragma once
#include"stdafx.h"
class GameManager
{
public:
	GameManager();
	~GameManager();
	 
	GameStatus getStatus();
	
	void SetStatus(GameStatus status);

private: 
	GameStatus gameStatus;
};

