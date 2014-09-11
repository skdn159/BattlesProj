#pragma once
#include "Ship.h"
class AirCraft :
	public Ship
{
public:
	AirCraft();
	~AirCraft();

	HitResult HitCheck(Position hitpos);

};

