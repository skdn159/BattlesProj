#include "stdafx.h"
#include "Ship.h"

Ship::Ship()
{	
}


Ship::~Ship()
{
}

void Ship::AddPosition(Position addPos) //for random
{
	for (int i = 0; i < m_Hp; ++i)
	{
		if (m_ShipPos[i].x == -1)//초기화된 구조체일경우
		{
			m_ShipPos[i].x = addPos.x;
			m_ShipPos[i].y = addPos.y;
			break;
		}
	}
	//m_ShipPos[i++] = addPos; //for문 등으로 AddPosition을 여러번 호출해야함
}


void Ship::AddPosition(int x, int y)  //직접 좌표를 찍을 때
{
	Position addPos = { x, y };
	AddPosition(addPos); //한번 더 호출해줌!
}

void Ship::PrintPos()
{
	printf_s("%s : ", m_Name.c_str());
	

	for (int i = 0; i < m_Type; i++){
		printf_s("%c%d ", 'A'+m_ShipPos[i].x, m_ShipPos[i].y+1);
	}
	printf_s("\n");
}

HitResult Ship::Hitcheck(Position hitpos)
{
	int m_MaxHP = m_Type; // 이해가 더 잘 가도록...
	
		
	for (int i = 0; i < m_MaxHP; ++i)
	{
				
		if (m_ShipPos[i].x == hitpos.x && m_ShipPos[i].y == hitpos.y)
		{
			m_ShipPos[i].x = -1; // 맞은 것은 -1로 구조체 초기화
			m_ShipPos[i].y = -1;
			--m_Hp;
					
			if (m_Hp == 0)
			{
				return DESTROY;
			}
				
			return HIT;
		}
	}
	return MISS;

}

