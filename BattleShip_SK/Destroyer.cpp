#include "stdafx.h"
#include "Destroyer.h"


Destroyer::Destroyer()
{
	m_Name = "Destroyer";
	m_Type = DESTROYER;
	m_MapMark_ShipType = 2;
	m_Hp = 2;

}


Destroyer::~Destroyer()
{
}

HitResult Destroyer::Hitcheck(Position hitpos)
{
	HitResult hitResult = Ship::Hitcheck(hitpos);

	if (hitResult == DESTROY){
		return DESTROY_DESTROYER;
	}


	return hitResult;
}
