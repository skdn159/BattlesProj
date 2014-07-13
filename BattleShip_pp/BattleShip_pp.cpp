// BattleShip_pp.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>


int _tmain(int argc, _TCHAR* argv[])
{
	srand((unsigned int)time(NULL)); //time을 이용한 seed값 생성

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

