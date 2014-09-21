#pragma once
#include "Ship.h"
class BattleShip :
	public Ship
{
public:
	BattleShip();
	~BattleShip();

	virtual HitResult Hitcheck(Position hitpos);
};

