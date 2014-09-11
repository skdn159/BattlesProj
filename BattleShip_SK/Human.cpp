#include "stdafx.h"
#include "Human.h"
#include "DrawSetting.h"


Human::Human()
{
	m_Name = "Anonymous";
	m_AirCraft = new AirCraft();
	m_BattleShip = new BattleShip();
	m_Cruiser = new Cruiser();
	m_Destroyer[0] = new Destroyer();
	m_Destroyer[1] = new Destroyer();

	//m_ShipList.reserve(5);
	m_ShipList.push_back(m_AirCraft);
	m_ShipList.push_back(m_BattleShip);
	m_ShipList.push_back(m_Cruiser);
	m_ShipList.push_back(m_Destroyer[0]);
	m_ShipList.push_back(m_Destroyer[1]);

	m_MyZido = new zido();
	m_EnemyZido = new zido();


}


Human::~Human()
{
	for (auto& i : m_ShipList){
		delete i;
	}
	delete m_MyZido;
	delete m_EnemyZido;

}
// random auto 배치 + 직접 배치

void Human::HumanSetupShips()
{





	//m_MyZido->PrintZido({ MY_ZIDO_X, MY_ZIDO_Y });//새로??
	int maxSizeOfMap=8;
	int gotoX =30;

	for (int j = 0; j < maxSizeOfMap*2 + 2; j++)
	{
		for (int k = 0; k < gotoX; k++)
		{
			printf_s(" ");
		}
		for (int i = 0; i < maxSizeOfMap + 2; i++)
		{
			if (j == 0)
			{
				if (i == 0)
					printf_s("   ");
				else if (i == maxSizeOfMap + 1)
					printf_s("");
				else
					printf_s("   %c", '1' + i - 1);
			}
			else if (j == 1)
			{
				if (i == 0)
					printf_s("   ");
				else if (i == 1)
					printf_s("┌");
				else if (i == maxSizeOfMap + 1)
					printf_s("─┐");
				else if (i >= 2)
					printf_s("─┬");
			}
			else if (j == maxSizeOfMap * 2 + 1)
			{
				if (i == 0)
					printf_s("   ");
				else if (i == 1)
					printf_s("└");
				else if (i == maxSizeOfMap + 1)
					printf_s("─┘");
				else if (i >= 2)
					printf_s("─┴");
			}
			else if (j % 2 == 0)
			{
				if (i == 0)
					printf_s(" %c ", 'A' + (j / 2) - 1);
				else
					printf_s("│  ");
			}
			else // j % 2 == 1
			{
				if (i == 0)
					printf_s("   ");
				else if (i == 1)
					printf_s("├");
				else if (i == maxSizeOfMap + 1)
					printf_s("─┤");
				else if (i >= 2)
					printf_s("─┼");
			}
		}
		printf_s("\n");
	}
}



	//_getch(); 로 입력
	
	//스페이스 누르면 돌아가게
	// 각 좌표의 숫자합으로 어케 해보자


