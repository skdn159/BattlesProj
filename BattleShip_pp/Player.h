#pragma once
#include"AirCraft.h"
#include"BattleShip.h"
#include"Cruiser.h"
#include"Destroyer.h"



class Player
{
public:
	Player();
	~Player();
	void SetupShips();
	void PrintShips();

protected:
	AirCraft m_Aircraft;
	BattleShip m_BattleShip;
	Cruiser m_Cruiser;
	Destroyer m_Destroyer[2];

};

