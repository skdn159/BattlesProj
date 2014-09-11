#include "stdafx.h"
#include "zido.h"
#include "Ship.h"



zido::zido()
{
	m_Name = "Unnamed Zido";
	m_width = 8;
	m_height = 8;
	
	m_zido = new int*[m_width];
	for (int i = 0; i < m_width; ++i){
		m_zido[i] = new int[m_height];
	}
	
	for (int i = 0; i < m_width; ++i){
		for (int j = 0; j < m_height; j++){
			m_zido[i][j] = 0;
		}
	}
}


zido::~zido()
{
}

bool zido::ShipOverlapCheck(int x, int y)
{
	if (m_zido[x][y] == 0){
		return true;
	}
	
	else 
	{ 
		return false;
	}
}

void zido::ShowZido()
{
	for (int i = 0; i < m_width; ++i){
		for (int j = 0; j < m_height; j++){
			printf_s("%d   ", m_zido[i][j]);
		}
		printf_s("\n");
	}
}

void zido::MarkShipPosition(int x, int y, int shipMarkType)
{
	m_zido[x][y] = shipMarkType;
}

void zido::PrintZido(POINT location)
{
	int i, j;
	printf_s("\n");
	printf_s("  ");
	for ( j = 0; j < m_height ; ++j){
		printf_s("%d ", j +1);
	}
	printf_s("\n");


	for ( i = 1; i < m_width + 1; ++i){
		printf_s("%c ", 'A' + (i - 1));
		for (j = 1; j < m_height + 1; ++j){
			printf_s("%d ", m_zido[i-1][j-1]);
		}
		printf_s("\n");

	}
}

bool zido::AttackValidCheck(int x, int y)
{
	if (x<0 || x > m_width || y<0 || y > m_height)
	{
		return false;
	}

	if (m_zido[x][y] < 0)
	{
		return false;
	}
			
		return true;
}

void zido::ZidoMarkByGM(Position pos)
{
	if (m_zido[pos.x][pos.y] == 0) //지도에 배가 없으면
	{
		m_zido[pos.x][pos.y] = -1;
	}
	else // 지도에 배가 있으면
	{
		m_zido[pos.x][pos.y] = -(m_zido[pos.x][pos.y]);
	}
}

void zido::MarkEnemyZido(int x, int y)
{
	if (m_zido[x][y] == 0){
		m_zido[x][y] = -1;
	}
	
	else{
		m_zido[x][y] = -(m_zido[x][y]);
	}
}



