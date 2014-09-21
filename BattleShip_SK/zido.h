#pragma once
#include"Ship.h"
#include <windef.h>
//#include"AirCraft.h"
//#include"BattleShip.h"
//#include"Cruiser.h"
//#include"Destroyer.h"

class zido
{
public:
	zido();
	~zido();

	void SetZidoName(std::string name) { m_Name = name; }
	std::string GetZidoName(){ return m_Name; }
	int GetMapLength() {return m_width; }

	bool ShipOverlapCheck(int x,  int y); 
	bool AttackValidCheck(int x, int y);
	
	void ShowZido();
	void MarkShipPosition(int x, int y, int shipMarkType);
	void PrintZido(int Location_x, int Location_y);
	void ZidoMarkByGM(Position pos);
	void MarkMiss_EnemyZido(int x, int y);
	void MarkHit_EnemyZido(int x, int y);
		

private:
	std::string m_Name;
	int m_width;
	int m_height;
	int** m_zido;
	
};

