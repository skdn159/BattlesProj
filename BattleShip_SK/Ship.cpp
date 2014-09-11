#include "stdafx.h"
#include "Ship.h"
//#define  MAXSHIPSIZE=5;//������ٰ� �����ߴµ� cpp���� �� ���ؾ��ϳ�=> ����

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
		if (m_ShipPos[i].x == -1)//�ʱ�ȭ�� ����ü�ϰ��
		{
			m_ShipPos[i].x = addPos.x;
			m_ShipPos[i].y = addPos.y;
			break;
		}


	}
	//m_ShipPos[i++] = addPos; //for�� ������ AddPosition�� ������ ȣ���ؾ��� Q. IDX�� Hp�� ���� Length�� ����...Hp�� �ϳ��� ��
}


void Ship::AddPosition(int x, int y)  //���� ��ǥ�� ���� ��
{
	Position addPos = { x, y };
	AddPosition(addPos); //�ѹ� �� ȣ������!
}

void Ship::PrintPos()
{
	//std::cout << m_Name << std::endl; // �� ���� �Ǿ��ִٰ� ���� �ʴ°��ΰ�! =>�Լ��� SHip:: �̰� �Ⱥٿ��༭,,.=
	printf_s("%s : ", m_Name.c_str());
	

	for (int i = 0; i < m_Type; i++){
		printf_s("%c%d ", 'A'+m_ShipPos[i].x, m_ShipPos[i].y+1);
	}
	printf_s("\n");
}

HitResult Ship::Hitcheck(Position hitpos)
{
	int m_MaxHP = m_Type; // ���ذ� �� �� ������...
	printf_s("hitpos = (%d,%d)\n", hitpos.x, hitpos.y);
		
	for (int i = 0; i < m_MaxHP; ++i)
	{
		printf_s("%dth shipPos=(%d,%d)\n",i, m_ShipPos[i].x, m_ShipPos[i].y);
		//printf_s("���� �� i=%d\n", i);
		if (m_ShipPos[i].x == hitpos.x && m_ShipPos[i].y == hitpos.y)
		{
			m_ShipPos[i].x = -1; // -1�� ����ü �ʱ�ȭ
			m_ShipPos[i].y = -1;
			--m_Hp;
			printf_s("��hp:%d\n", m_Hp);
			
			//printf_s("\n�� Ÿ��:%d, ���� ��HP:%d\n",m_Type,m_Hp);
			
			if (m_Hp == 0)
			{
				return DESTROY;
			}

					
			return HIT;
			
		}
	}
	return MISS;

}

