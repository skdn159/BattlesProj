// BattleShip_pp.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.

#include "stdafx.h"
#include<iostream>
#include<string>
#include<vector>
#include <time.h>
#include<ctime>
#include<cstdlib>
#include<list>
#include"Destroyer.h"
#include"GameManager.h"
#include"player.h"


int _tmain(int argc, _TCHAR* argv[])
{
	/*
	srand((unsigned int)time(NULL)); //time을 이용한 seed값 생성
	std::string strResult[] = { "Hit", "MISS", "DESTROY" };
	std::vector<std::string>ships;

	ships.push_back("Aircraft Carrier");
	ships.push_back("Battle Ship");
	ships.push_back("Cruiser");
	ships.push_back("Destroyer 1");
	ships.push_back("Destroyer 2");

	std::string strGuess;

	int resultpicked;
	int pickedDestroyedShips;
	Ship myship;
	Destroyer destroyer1, destroyer2;
	destroyer1.HitCheck();

	GameManager gm;
	gm.SetStatus(gamestarted);
	std::cout << gm.getStatus()<< std::endl;




	while (!ships.empty())
	{
		resultpicked = rand() % _countof(strResult);
		std::cin >> strGuess;
		std::cout << strResult[(resultpicked)] << std::endl;

		if (resultpicked == 2){     //문제가 있음. 어케하면 좋게 구현 가능한지?

			pickedDestroyedShips = rand() % ships.size();
			std::cout << ships[pickedDestroyedShips] << std::endl;
			ships.erase(ships.begin() + pickedDestroyedShips); 

			std::cout << "남은 배 : ";
			for ( int i = 0; i < ships.size(); i++){
				std::cout << ships[i] << "  /"; //보여지나?? ㅇㅇ 된다. vector의 특징
			}
			std::cout << std::endl;
		}
	}
	std::cout << "====== GameOver ======" << std::endl;

	

	fflush(stdin);*/

	srand((unsigned int)time(NULL));
	Player player;
	player.SetupShips();
	player.PrintShips();


	getchar();


	return 0;
}



