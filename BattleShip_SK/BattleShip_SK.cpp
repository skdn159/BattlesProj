// BattleShip_pp.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.

#include "stdafx.h"
#include "player.h"
#include "zido.h"
#include "GameManager.h"
#include "Draw.h"

#define ToPlay 10000

int _tmain(int argc, _TCHAR* argv[])
{
	float AvgResult;

	system("mode con cols=140 lines=35");
	system("title BattleShip");
		
	GameManager GM;
	GM.StartGame(ToPlay);
	AvgResult= GM.GetAVG_TurnCount(ToPlay);
	std::cout << "������ �� �ϼ� = " << AvgResult << std::endl;

	//GM.Networking();
	
	getchar();
	
	return 0;
}



