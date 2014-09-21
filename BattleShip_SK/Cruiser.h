#pragma once
#include "Ship.h"
class Cruiser :
	public Ship
{
public:
	Cruiser();
	~Cruiser();

	virtual HitResult Hitcheck(Position hitpos);
};

