#include "stdafx.h"
#include "zido.h"
#include "Ship.h"
#include "DrawSetting.h"
#include "Draw.h"


zido::zido()
{
	m_Name = "Unnamed Zido";
	m_width = 8;
	m_height = 8;
	
	//할당
	m_zido = new int*[m_width];
	for (int i = 0; i < m_width; ++i){
		m_zido[i] = new int[m_height];
	}
	
	//초기화
	for (int i = 0; i < m_width; ++i){
		for (int j = 0; j < m_height; j++){
			m_zido[i][j] = 0;
		}
	}
}


zido::~zido()
{
	for (int i = 0; i < m_height; ++i){

		delete m_zido[i];
	}
	delete m_zido;
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

void zido::PrintZido(int Location_x, int Location_y)
{
	Gotoxy(Location_x, Location_y);
	int ZidoMaxHeight = m_height;
	int ZidoMaxWidth = m_width;

	for (int Height = 0; Height < (2 * ZidoMaxHeight) + 2; ++Height){

		for (int Width = 0; Width < (2 * ZidoMaxWidth) + 2; ++Width){

			if (Width == 0 && Height == 0)
			{
				Gotoxy(Location_x, Location_y);
				printf_s("  ");//2칸
			}
			if (Width == 0 && Height % 2 == 1){
				Gotoxy(Location_x, Location_y);
				printf_s("  ");
			}

			if (Width == 0){ //좌표 알파벳 세팅
				if (Height > 1 && Height % 2 == 0){
					Gotoxy(Location_x + 1, Location_y + Height + 1);
					Setcolor(WHITE, BLACK);
					printf_s("%c", 'A' + ((Height / 2) - 1));
				}
			}


			if (Height == 0){ // 좌표 숫자 세팅
				if (Width > 1 && Width % 2 == 0){
					Gotoxy(Location_x + 2 * Width + 1, Location_y + 1); //간격수정 요망
					Setcolor(WHITE, BLACK);
					printf_s("%d", (Width / 2));
				}
			}
			if (Height<m_height&&Width<m_width){
				int Wide = 2*Width;
				Gotoxy(Location_x + 2*Wide +5, Location_y + 2 * Height + 3);
				Setcolor(GREEN, BLACK);
				printf_s("%d", m_zido[Height][Width]);
			}

		}
	}
	//Draw_Zido(MY_ZIDO_X, MY_ZIDO_Y);
	//Draw_Zido(ENEMY_ZIDO_X, ENEMY_ZIDO_Y);
}

bool zido::AttackValidCheck(int x, int y)
{
	
	if (x<0 || x > m_width-1 || y<0 || y > m_height-1)
	{ //지도 밖의 좌표가 나오면
		return false;
	}
	if (m_zido[x][y] == -1){//음수(MISS한 곳)이나오면 F
		return false;
	}

	if (m_zido[x][y] ==1)
	{//1(HIT했던곳)이 나오면 F
		return false;
	}
	if (m_zido[x][y] == 7){ // destroy는 7로 표시

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

void zido::MarkMiss_EnemyZido(int x, int y)
{
	if (m_zido[x][y] != 0){
		return;
	}
	m_zido[x][y] = -1; // -1이 찍히면 miss
}

void zido::MarkHit_EnemyZido(int x, int y)
{
	
	m_zido[x][y] = 1;
}





