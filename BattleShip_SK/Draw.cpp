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
//��
//
//��
//
//��
//
//��
//
//��
//��
//��
//��
//��
//��
//��

void Draw_Zido(int Location_x, int Location_y)
{
	Gotoxy(Location_x, Location_y);
	int ZidoMaxHeight = 8;
	int ZidoMaxWidth = ZidoMaxHeight;
 
	for (int Height = 0; Height < (2 * ZidoMaxHeight) + 2; ++Height){
				
		for (int Width = 0; Width < (2 * ZidoMaxWidth) + 2; ++Width){

			if (Width==0&&Height==0)
			{
				Gotoxy(Location_x, Location_y);
				printf_s("  ");//2ĭ
			}
			if (Width == 0 && Height % 2 == 1){
				Gotoxy(Location_x, Location_y);
				printf_s("  ");
			}

			if (Width == 0){ //��ǥ ���ĺ� ����
				if (Height>1 && Height % 2 == 0){
					Gotoxy(Location_x+1, Location_y+Height+1);
					printf_s("%c", 'A'+((Height/2)-1));
				}
			}

			if (Height == 0){ // ��ǥ ���� ����
				if (Width > 1 && Width % 2 == 0){
					Gotoxy(Location_x + 2*Width+1, Location_y+1); //���ݼ��� ���
					printf_s("%d", (Width / 2));
				}
			}

			if (Height == 1 && Width == 1){
				Gotoxy(Location_x + 2, Location_y + 2);
				printf_s("��");
			}
			if (Height == 1 && Width == ((2 * ZidoMaxWidth) + 1)){
				Gotoxy(Location_x+(2*(ZidoMaxWidth+1)), Location_y+2);
				Gotoxy(Location_x+34, Location_y+2); //why?
				printf_s("��");
			}
			if (Width ==1  && Height == ((2 * ZidoMaxHeight) + 1)){
				Gotoxy(Location_x+2, Location_y+(2*ZidoMaxHeight+2));
				printf_s("��");
			}
			if (Width == ((2 * ZidoMaxWidth) + 1) && Height == ((2 * ZidoMaxHeight) + 1)){
				Gotoxy(Location_x + (2 * ZidoMaxWidth + 2), Location_y + (2 * ZidoMaxHeight + 2));
				Gotoxy(Location_x + 34, Location_y + (2 * ZidoMaxHeight + 2));//why?
				printf_s("��");
			}
			if (Width > 0&&Width%2==1&& Height > 1 && Height % 2 == 0){//�� �����ε��� �ȵ�?? ���� ���غҰ�
				Gotoxy(Location_x+(2*Width), Location_y+(Height+1));
				printf_s("��  ");  
			}
			if (Width > 0 && (Height % 2) == 1 && Width % 2 == 0){
				Gotoxy(Location_x + 2*Width, Location_y + Height+1);
				printf_s("��");
			}
			if (Width > 2 && Width % 2 == 1 && Height==1&&Width<16){
				Gotoxy(Location_x+2*Width, Location_y+2);
				printf_s("��");
			}
			if (Height > 2 && Height < (2 * ZidoMaxHeight) && Height % 2 == 1 && Width == 1){
				Gotoxy(Location_x+2, Location_y+Height+1);
				printf_s("��");
			}
			if (Width>2 && Width<(2 * ZidoMaxWidth) && Height>2 && Height < (2 * ZidoMaxHeight) && Width % 2 == 1 && Height % 2 == 1){
				Gotoxy(Location_x+2*Width, Location_y+Height+1);
				printf_s("��");
			}
			if (Width == (2 * ZidoMaxWidth) + 1 && Height>2 && Height < (2 * ZidoMaxHeight) && Height % 2 == 1){
				Gotoxy(Location_x+2*Width, Location_y+Height+1);
				printf_s("��");
			}
			if (Height == (2 * ZidoMaxHeight + 1) && Width>2 && Width < (2 * ZidoMaxWidth) && Width % 2 == 1){
				Gotoxy(Location_x + 2 * Width, Location_y + (2 * ZidoMaxHeight + 2));
				printf_s("��");
			}

		}
		printf_s("\n");
	}
}

void Draw_ShipsOnMap(int Location_x, int Location_y)
{
	Location_x = MY_ZIDO_X;
	Location_y = MY_ZIDO_Y;
}
