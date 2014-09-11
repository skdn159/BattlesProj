#include "stdafx.h"
#include "Destroyer.h"


Destroyer::Destroyer()
{
	m_Name = "Destroyer";
	//m_Length = 2;
	m_Type = DESTROYER;
	m_MapMark_ShipType = 2;
	m_Hp = 2;

}


Destroyer::~Destroyer()
{
}

HitResult Destroyer::HitCheck(Position hitpos)
{
	HitResult hitResult = Ship::Hitcheck(hitpos);

	if (hitResult == DESTROY){
		return DESTROY_DESTROYER;
	}

	return hitResult;
}
