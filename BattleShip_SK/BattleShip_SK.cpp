// BattleShip_SK.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<vector>
#include <time.h>
#include<ctime>
#include<cstdlib>
#include<list>




int _tmain(int argc, _TCHAR* argv[])
{
	srand((unsigned int)time(NULL)); //time�� �̿��� seed�� ����
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
	//std::cout << result << std::endl;


	while (!ships.empty())
	{
		resultpicked = rand() % _countof(strResult);
		std::cin >> strGuess; 
		std::cout << strResult[(resultpicked)] << std::endl;

		if (resultpicked ==2){     //������ ����. �����ϸ� ���� ���� ��������?
		
			pickedDestroyedShips = rand() % ships.size();
			std::cout << pickedDestroyedShips << std::endl;
			ships.erase(ships.begin()+pickedDestroyedShips);

			std::cout << "���� �� : ";
			for (unsigned int i = 0; i < ships.size(); i++){
				std::cout << ships[i] << "  /"; //��������?? ���� �ȴ�. vector�� Ư¡
			}
			std::cout << std::endl;
		}
	}
	std::cout << "====== GameOver ======" << std::endl;

	fflush(stdin);
	getchar();


	return 0;
}
