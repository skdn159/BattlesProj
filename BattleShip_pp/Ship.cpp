#include "stdafx.h"
#include "Ship.h"


Ship::Ship()
{
	m_Hp = 0;
	m_Length = 0;
	//m_ShipPos

}


Ship::~Ship()
{
}

HitResult Ship::HitCheck(Position attackPos) //ship�� �ִ� �Լ���� ��.
{

	return HitResult::RESULT_NULL;
}

HitResult Ship::HitCheck(int x, int y)
{
	Position hitpos = { x, y };
	HitCheck(hitpos);
}


void Ship::AddPosition(Position addpos)
{
	//if (m_Hp >= m_Length) return; //����ڵ�
	
	m_ShipPos[m_Hp++] = addpos; //����ü �̰� ��������?

}

void Ship::AddPosition(int x, int y)
{
	Position addpos = { x, y }; 
	AddPosition(addpos);
}

void Ship::PrintPos()
{
	printf_s("%s : ", m_Name.c_str());
	
	for (int i = 0; i < m_Length; i++){
		printf_s("%c%d ", 'A' + m_ShipPos[i].x, m_ShipPos[i].y + 1);

	}
	puts("");

}
