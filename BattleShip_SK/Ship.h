#pragma once
#include "Enums.h"
#define  MAXSHIPSIZE 5

struct Position 
{
	int x;
	int y;
	
	Position()
	{
		x = -1;
		y = -1;
	}

	Position(int _x, int _y)
	{
		x = _x;
		y = _y;

	}

};



class Ship
{
public:
		
	Ship();
	~Ship();
	int GetHP(){ return m_Hp; }
	int GetShipMaxHP(){ return m_Type; }
	int GetShipType(){ return m_MapMark_ShipType; }
	virtual HitResult Hitcheck(Position hitpos);
	void AddPosition(Position addpos); //for random
	void AddPosition(int x, int y);
	void PrintPos();

protected: 
	int m_Hp;
	//int m_Length;
	int m_Type;
	int m_MapMark_ShipType; //���� ǥ�ÿ�
	std::string m_Name;
	struct Position m_ShipPos[MAXSHIPSIZE]; // ���� position�� �迭�� ǥ��
		
};

