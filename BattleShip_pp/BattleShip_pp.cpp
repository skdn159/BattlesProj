// BattleShip_pp.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>


int _tmain(int argc, _TCHAR* argv[])
{
	srand((unsigned int)time(NULL)); //time�� �̿��� seed�� ����

	std::string strInput;
	std::cin >> strInput;

	std::string strResult[] = { "Hit", "MISS", "DESTROY" };



	int result= rand() % _countof(strResult);
	std::cout << result << std::endl;

	std::cout << strResult[(result)]; 

	fflush(stdin);
	getchar();


	return 0;
}

