#include "stdafx.h"
#include "AirCraft.h"


AirCraft::AirCraft()
{
	m_Name = "AirCraft";
	//m_Length = 5;
	m_Type = AIRCRAFT;
	m_MapMark_ShipType = 5;
	m_Hp = 5;
}


AirCraft::~AirCraft()
{
}

HitResult AirCraft::HitCheck(Position hitpos)
{
	HitResult hitResult = Ship::Hitcheck(hitpos);

	if (hitResult == DESTROY){
		return DESTROY_AIRCRAFT;
	}

	return hitResult;
}
