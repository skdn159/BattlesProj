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
	bool ShipOverlapCheck(int x,  int y); // x, y ÁÂÇ¥/ ¹úÆ¼Ä® È£¸®Á¸Å» / 
	bool AttackValidCheck(int x, int y);
	
	void ShowZido();
	void MarkShipPosition(int x, int y, int shipMarkType);
	void PrintZido(POINT location);
	void ZidoMarkByGM(Position pos);
	void MarkEnemyZido(int x, int y);
		

private:
	std::string m_Name;
	int m_width;
	int m_height;
	int** m_zido;
	
};

