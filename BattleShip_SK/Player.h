#pragma once
#include "zido.h"
#include"Ship.h"
#include"AirCraft.h"
#include"BattleShip.h"
#include"Cruiser.h"
#include"Destroyer.h"
#include <vector>

class Player
{
public:
	Player();
	~Player();

	std::string	GetPlayerName()	{ return m_Name; }
	zido* GetMyZido(){ return m_MyZido; }
	zido* GetEnemyZido() { return m_EnemyZido; }
	HitResult HitCheck(Position hitpos);

	void SetPlayerName(std::string name) { m_Name = name; }
	void See_initial_Ships();
	void RandomSetupShips();
	bool PlaceValidCheck(int rndDirection, int shipMaxHP, Position rndPos);
	bool IsAllSunK();
		
	Position RandomAttack();
	
	
	//for Ai
	void LoadSearchList();
	void SetAImodeSearch(){ m_AImode = SEARCH_MODE; }
	void ReceiveHitResult(Position attackPos, HitResult hitResult);
	void FindDestroyedShip(HitResult hitResult, Position tempAttackpos);
	
	Position AI_Attack();
	
	//For NetWork
	std::vector<Ship*>*	GetShipList(){ return &m_ShipList; }

private:

	//for AI
	void UpdateEnemyZido(MarkHitResult markType, Position attackPos);
	Position MakeNextDestroyPos(Direction_MY chaseDir, Position tempPos);
	Position GenerateNextattackPos(Direction_MY dir, Position attackPos);
	Position GenerateSurroundPos(Position attackPos);
	Position GeneratePosByManual(Position tempPos);

	Direction_MY ReverseAttackDir(Direction_MY tempDir);
	Direction_MY TurnRightAttackDir(Direction_MY tempDir);
	Direction_MY FindDirectionOfDestroyedShip(Direction_MY tempAttackDir);


	
private:

	std::string m_Name;
	
	zido* m_MyZido;
	zido* m_EnemyZido;

	std::vector<Ship*> m_ShipList;
	AirCraft* m_AirCraft;
	BattleShip* m_BattleShip;
	Cruiser* m_Cruiser;
	Destroyer* m_Destroyer[2];

	//For AI
	AImode m_AImode;

	std::vector<Position> m_SearchList_First;
	std::vector<Position> m_SearchList_Second;
	std::vector<Position> m_SearchList_Third;
	
	Position m_PrevAttackPos;
	Position m_FirstHitPos;
	Position m_NextoFindPos; 
	Direction_MY m_AttackDir;
	
	int m_HitCount; // destroy 통보 이전에 맞춘 hit 수
	int m_HavetoFind; // hitcount > destroy ship hp
};

