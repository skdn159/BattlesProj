#pragma once
#include "Ship.h"
class Destroyer :
	public Ship
{
public:
	Destroyer();
	~Destroyer();

	virtual HitResult Hitcheck(Position hitpos);
};

