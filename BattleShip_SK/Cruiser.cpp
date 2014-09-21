#include "stdafx.h"
#include "Cruiser.h"


Cruiser::Cruiser()
{
	m_Name = "Cruiser";
	m_Type = CRUISER;
	m_MapMark_ShipType = 3;
	m_Hp = 3;

}


Cruiser::~Cruiser()
{
}

HitResult Cruiser::Hitcheck(Position hitpos)
{
	HitResult hitResult = Ship::Hitcheck(hitpos);

	if (hitResult == DESTROY){
		return DESTROY_CRUISER;
	}

	return hitResult;
}
