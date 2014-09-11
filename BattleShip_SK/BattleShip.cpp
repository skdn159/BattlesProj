#include "stdafx.h"
#include "BattleShip.h"


BattleShip::BattleShip()
{
	m_Name = "BattleShip";
	//m_Length = 4;
	m_Type = BATTLESHIP;
	m_MapMark_ShipType = 4;
	m_Hp = 4;


}


BattleShip::~BattleShip()
{
}

HitResult BattleShip::HitCheck(Position hitpos)
{
	HitResult hitResult = Ship::Hitcheck(hitpos);

	if (hitResult == DESTROY){
		return DESTROY_BATTLESHIP;
	}

	return hitResult;
}
