#pragma once


struct Position
{
	int x, y;
	Position()
	{
		x = 0;
		y = 0;
	}

	Position(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
};
enum HitResult{
	
	RESULT_NULL,
	HIT,
	MISS,
	DESTROY,
};

class Ship
{
public:
	Ship();
	~Ship();
public:

	HitResult HitCheck(Position attackpos); // ship.cpp에 구현
	HitResult HitCheck(int x, int y);
	int GetHP(){ return m_Hp; } //인라인함수. 간단하고 자주 호출되서 인라인함수로 만든 것
	int GetLength(){ return m_Length; }
	
	void AddPosition(Position addpos);
	void AddPosition(int x, int y);
	void PrintPos();

protected:
	int m_Hp; 
	int m_Length; 
	Position m_ShipPos[5];
	std::string m_Name;
	
};

