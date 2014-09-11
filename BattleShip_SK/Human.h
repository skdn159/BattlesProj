#pragma once
#include "Player.h"
class Human :
	public Player
{
public:
	Human();
	~Human();


	void HumanSetupShips();


private:
	std::string m_Name;
	zido* m_MyZido;
	zido* m_EnemyZido;

	std::vector<Ship*>m_ShipList;
	AirCraft* m_AirCraft;
	BattleShip* m_BattleShip;
	Cruiser* m_Cruiser;
	Destroyer* m_Destroyer[2];


};

