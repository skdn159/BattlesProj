#pragma once
#include "Ship.h"
class AirCraft :
	public Ship
{
public:
	AirCraft();
	~AirCraft();

	virtual HitResult Hitcheck(Position hitpos);

};

