// BattleShip_pp.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.

#include "stdafx.h"
#include "player.h"
#include "zido.h"
#include "GameManager.h"
//#include "Human.h"
#include "Draw.h"



int _tmain(int argc, _TCHAR* argv[])
{
	system("mode con cols=150 lines=40");
	system("title BattleShip");
	//Human Human;
	//Human.HumanSetupShips();
	
	//GameManager GM;
	//GM.StartGame();

	Draw_Zido(MY_ZIDO_X,MY_ZIDO_Y);

	



	//fflush(stdin);
	getchar();


	return 0;
}



