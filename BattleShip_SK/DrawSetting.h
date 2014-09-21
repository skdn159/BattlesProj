#pragma once
#include "stdafx.h"

enum Colors
{
	BLACK,
	DARK_BLUE,
	DARK_GREEN,
	DARK_SKY,
	DARK_RED,
	DARK_PINK,
	DARK_YELLOW,
	LIGHT_GRAY,
	GRAY,
	BLUE,
	GREEN,
	SKY,
	RED,
	PINK,
	YELLOW,
	WHITE,
};

enum DrawLocation
{
	MY_ZIDO_X =30,
	MY_ZIDO_Y =7,
	ENEMY_ZIDO_X =85,
	ENEMY_ZIDO_Y =7,
	
};

void Setcolor(int color, int bgcolor);
void Gotoxy(int x, int y);
void SetCursorAndColor(int x, int y, int fcolor, int bcolor);
