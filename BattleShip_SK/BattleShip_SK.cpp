// BattleShip_pp.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.

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
	std::cout << "게임의 총 턴수 = " << AvgResult << std::endl;

	//GM.Networking();
	
	getchar();
	
	return 0;
}



