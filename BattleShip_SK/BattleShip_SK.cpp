// BattleShip_SK.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	srand((unsigned int)time(NULL)); //time�� �̿��� seed�� ����

	std::string strInput;
	std::cin >> strInput;

	std::string strResult[] = { "Hit", "MISS", "DESTROY" };



	int result = rand() % _countof(strResult);
	std::cout << result << std::endl;

	std::cout << strResult[(result)];

	fflush(stdin);
	getchar();


	return 0;
}
