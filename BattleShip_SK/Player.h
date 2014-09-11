#pragma once
#include"Ship.h"
#include"AirCraft.h"
#include"BattleShip.h"
#include"Cruiser.h"
#include"Destroyer.h"
#include "zido.h"
#include "Enums.h"
#include <vector>

class Player
{
public:
	Player();
	~Player();
	void SetPlayerName(std::string name) { m_Name = name; }
	std::string	GetPlayerName()	{ return m_Name; }
	void See_initial_Ships();
	void RandomSetupShips();
	bool PlaceValidCheck(int rndDirection, int shipMaxHP, Position rndPos);
	bool IsAllSunK();
	zido* GetMyZido(){ return m_MyZido; }
	zido* GetEnemyZido() { return m_EnemyZido; }
	
	Position RandomAttack();
	HitResult HitCheck(Position hitpos);
	HitResult HitCheck(int x, int y);
	
private:
	void UpdateEnemyZido(int x, int y);
	

protected:
	
private:

	std::string m_Name;
	
	zido* m_MyZido;
	zido* m_EnemyZido;

	std::vector<Ship*> m_ShipList;
	AirCraft* m_AirCraft;
	BattleShip* m_BattleShip;
	Cruiser* m_Cruiser;
	Destroyer* m_Destroyer[2];

};

