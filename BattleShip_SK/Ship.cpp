#include "stdafx.h"
#include "Ship.h"
//#define  MAXSHIPSIZE=5;//헤더에다가 선언했는데 cpp에도 또 말해야하나=> ㄴㄴ

Ship::Ship()
{
	//m_Hp = 0;
	//m_Length = 0;
	//m_Type = COMMON;
	//m_MapMark_ShipType = 1;
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
	//m_ShipPos[i++] = addPos; //for문 등으로 AddPosition을 여러번 호출해야함 Q. IDX를 Hp로 할지 Length로 할지...Hp가 하나씩 참
}


void Ship::AddPosition(int x, int y)  //직접 좌표를 찍을 때
{
	Position addPos = { x, y };
	AddPosition(addPos); //한번 더 호출해줌!
}

void Ship::PrintPos()
{
	//std::cout << m_Name << std::endl; // 왜 정의 되어있다고 하지 않는것인가! =>함수에 SHip:: 이걸 안붙여줘서,,.=
	printf_s("%s : ", m_Name.c_str());
	

	for (int i = 0; i < m_Type; i++){
		printf_s("%c%d ", 'A'+m_ShipPos[i].x, m_ShipPos[i].y+1);
	}
	printf_s("\n");
}

HitResult Ship::Hitcheck(Position hitpos)
{
	int m_MaxHP = m_Type; // 이해가 더 잘 가도록...
	printf_s("hitpos = (%d,%d)\n", hitpos.x, hitpos.y);
		
	for (int i = 0; i < m_MaxHP; ++i)
	{
		printf_s("%dth shipPos=(%d,%d)\n",i, m_ShipPos[i].x, m_ShipPos[i].y);
		//printf_s("지금 내 i=%d\n", i);
		if (m_ShipPos[i].x == hitpos.x && m_ShipPos[i].y == hitpos.y)
		{
			m_ShipPos[i].x = -1; // -1로 구조체 초기화
			m_ShipPos[i].y = -1;
			--m_Hp;
			printf_s("내hp:%d\n", m_Hp);
			
			//printf_s("\n내 타입:%d, 지금 내HP:%d\n",m_Type,m_Hp);
			
			if (m_Hp == 0)
			{
				return DESTROY;
			}

					
			return HIT;
			
		}
	}
	return MISS;

}

