#pragma once
enum PlaceDirection
{
 HORIZONTAL,
 VERTICAL,

};

enum ShipType
{
	COMMON = 0,
	DESTROYER = 2,
	CRUISER = 3,
	BATTLESHIP = 4,
	AIRCRAFT = 5
};

enum HitResult
{
	MISS,
	HIT,
	DESTROY,
	DESTROY_DESTROYER,
	DESTROY_CRUISER,
	DESTROY_BATTLESHIP,
	DESTROY_AIRCRAFT,
};

enum Direction
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
