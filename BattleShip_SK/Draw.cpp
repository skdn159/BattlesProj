#include "stdafx.h"
#include "Draw.h"
//#include "windows.h"
//#include "Enums.h"
#include "DrawSetting.h"
#include "zido.h"
#include "GameManager.h"
void Draw_Intro()
{

}

void Print_Menu()
{

}

void Draw_Ending()
{

}
//
//
//
//╋
//
//┳
//
//┻
//
//┃
//
//┗
//┏
//┓
//┛
//━
//┫
//┣

void Draw_Zido(int Location_x, int Location_y)
{
	//Gotoxy(Location_x, Location_y);
	int ZidoMaxHeight = 8;
	int ZidoMaxWidth = ZidoMaxHeight;
 
	for (int Height = 0; Height < (2 * ZidoMaxHeight) + 2; ++Height){
				
		for (int Width = 0; Width < (2 * ZidoMaxWidth) + 2; ++Width){

			if (Width==0&&Height==0)
			{
				printf_s("  ");
			}
			if (Width == 0 && Height % 2 == 1){
			
				printf_s("  ");
			}

			if (Width == 0){ //좌표 알파벳 세팅
				if (Height>1 && Height % 2 == 0){
					printf_s("%c ", 'A'+((Height/2)-1));
				}
			}

			if (Height == 0){ // 좌표 숫자 세팅
				if (Width > 1 && Width % 2 == 0){
					printf_s("  %d ", (Width / 2));
				}
			}

			if (Height == 1 && Width == 1){
				printf_s("┏");
			}
			if (Height == 1 && Width == ((2 * ZidoMaxWidth) + 1)){
				printf_s("┓");
			}
			if (Width ==1  && Height == ((2 * ZidoMaxHeight) + 1)){
				printf_s("┗");
			}
			if (Width == ((2 * ZidoMaxWidth) + 1) && Height == ((2 * ZidoMaxHeight) + 1)){
				printf_s("┛");
			}
			if (Width > 0&&Width%2==1&& Height > 1 && Height % 2 == 0){
				printf_s("┃  ");  //왜 오버로딩이 안됨?? 완전 이해불가
			}
			if (Width > 0 && (Height % 2) == 1 && Width % 2 == 0){
				printf_s("━");
			}
			if (Width > 2 && Width % 2 == 1 && Height==1&&Width<16){
				printf_s("┳");
			}
			if (Height > 2 && Height < (2 * ZidoMaxHeight) && Height % 2 == 1 && Width == 1){
				printf_s("┣");
			}
			if (Width>2 && Width<(2 * ZidoMaxWidth) && Height>2 && Height < (2 * ZidoMaxHeight) && Width % 2 == 1 && Height % 2 == 1){
				printf_s("╋");
			}
			if (Width == (2 * ZidoMaxWidth) + 1 && Height>2 && Height < (2 * ZidoMaxHeight) && Height % 2 == 1){
				printf_s("┫");
			}
			if (Height == (2 * ZidoMaxHeight + 1) && Width>2 && Width < (2 * ZidoMaxWidth) && Width % 2 == 1){
				printf_s("┻");
			}

		}
		printf_s("\n");

	}




	//Gotoxy(20, 11);
	//Setcolor(GREEN, LIGHT_GRAY);
	//printf_s("heloo");
	//Setcolor(DARK_RED, SKY);
	//Gotoxy(10, 15);
	//printf_s("DA");



}
