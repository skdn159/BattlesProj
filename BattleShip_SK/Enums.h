#pragma once
enum PlaceDirection
{
 HORIZONTAL,
 VERTICAL,

};

enum ShipType_MY
{
	COMMON = 0,
	DESTROYER = 2,
	CRUISER = 3,
	BATTLESHIP = 4,
	AIRCRAFT = 5
};

enum HitResult
{	
	RES_NONE,
	MISS,
	HIT,
	DESTROY,

	DESTROY_DESTROYER,
	DESTROY_CRUISER,
	DESTROY_BATTLESHIP,
	DESTROY_AIRCRAFT,
};

enum Direction_MY
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};
enum Turn
{
ATTACKER,
DEFENDER,

};
enum GameStatus
{
	PLAYING,
	GAMEOVER,

};

enum Winner
{
 NO_ONE,
 WINNER_ATTACKER,
 WINNER_DEFENDER,

};

enum AImode
{
	SEARCH_MODE,
	TARGET_MODE,
};

enum MarkHitResult
{
	MARK_MISS,
	MARK_HIT,
	MARK_DESTROY,
};