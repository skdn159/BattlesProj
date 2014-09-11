#include "stdafx.h"
#include "Player.h"
//#include "zido.h"
#include "Enums.h"


Player::Player()
{
	m_Name = "Anonymous";
	m_AirCraft = new AirCraft();
	m_BattleShip = new BattleShip();
	m_Cruiser = new Cruiser();
	m_Destroyer[0] = new Destroyer();
	m_Destroyer[1] = new Destroyer();
	
	//m_ShipList.reserve(5);
	m_ShipList.push_back(m_AirCraft);
	m_ShipList.push_back(m_BattleShip);
	m_ShipList.push_back(m_Cruiser);
	m_ShipList.push_back(m_Destroyer[0]);
	m_ShipList.push_back(m_Destroyer[1]);

	m_MyZido = new zido();
	m_EnemyZido = new zido();
	
}


Player::~Player()
{
	for (auto& i : m_ShipList){
		delete i;
	}
	delete m_MyZido;
	delete m_EnemyZido;
}

void Player::See_initial_Ships()
{
	m_AirCraft->PrintPos();
	m_BattleShip->PrintPos();
	m_Cruiser->PrintPos();
	m_Destroyer[0]->PrintPos();
	m_Destroyer[1]->PrintPos();
	
}

void Player::RandomSetupShips(){
	
	//Ship* ships[5] = { &m_AirCraft, &m_BattleShip, &m_Cruiser, &m_Destroyer[0], &m_Destroyer[1] };

	Position placePos;
	int direction;
	int mapSize = m_MyZido->GetMapLength();
	
	for (int ships_index = 0; ships_index <(int)m_ShipList.size();)
	{
		
		Ship* ships = m_ShipList[ships_index];

		int shipMaxHP = m_ShipList[ships_index]->GetShipMaxHP();
		//starting point check
		do
		{
			
			placePos.x = rand() % mapSize;
			placePos.y = rand() % mapSize;
			direction = rand() % 2;
									
		} while (PlaceValidCheck(direction,shipMaxHP,placePos)==false);
		//시작점을 다 체크했음
		
		for (int i = 0; i < shipMaxHP; ++i){

			ships->AddPosition(placePos);
			//ships->PrintPos();

			if (direction == HORIZONTAL){
				++placePos.x;
			}
			if (direction == VERTICAL){
				++placePos.y;
			}
		}
		++ships_index;
	
	}
}

bool Player::PlaceValidCheck(int rndDirection, int shipMaxHP, Position rndPos )
{
	int mapLength = m_MyZido->GetMapLength();

	//map limit check
	if (rndDirection == HORIZONTAL){
		if ((rndPos.x + shipMaxHP) > (mapLength-1)){
			
			return false;
		}

	}

	if (rndDirection == VERTICAL){
		if ((rndPos.y + shipMaxHP) > (mapLength - 1)){
			return false;
		}

	}

	// 중복check

	if (rndDirection == HORIZONTAL)
	{
		for (int i = 0; i < shipMaxHP; ++i){
			if (m_MyZido->ShipOverlapCheck(rndPos.x, rndPos.y) == false)
			{	
				return false;
			}
			++rndPos.x;
		}

		--rndPos.x;

		for (int k = 0; k < shipMaxHP; ++k){
			m_MyZido->MarkShipPosition(rndPos.x, rndPos.y, shipMaxHP);
			--rndPos.x;
		}
	}
		
	
	if (rndDirection == VERTICAL){
		for (int j = 0; j < shipMaxHP; ++j){
			if (m_MyZido->ShipOverlapCheck(rndPos.x, rndPos.y) == false)
			{
				return false;

			}
			++rndPos.y;
		}
		--rndPos.y;

		for (int m = 0; m < shipMaxHP; ++m)
		{
			m_MyZido->MarkShipPosition(rndPos.x, rndPos.y, shipMaxHP);
			--rndPos.y;
		}
	}
	
	return true;
}

Position Player::RandomAttack()
{
	Position hitpos;
	int zidoLength=m_MyZido->GetMapLength();
	
	do 
	{
		hitpos.x = rand() % zidoLength;
		hitpos.y = rand() % zidoLength;

	} while (m_EnemyZido->AttackValidCheck(hitpos.x,hitpos.y)==false);
	
	UpdateEnemyZido(hitpos.x, hitpos.y);
	
	return hitpos;
}

HitResult Player::HitCheck(int x, int y)
{
	Position hitpos = { x, y }; 
	HitResult hitResult;
	hitResult=HitCheck(hitpos);
	return hitResult;
}

bool Player::IsAllSunK()
{
	/*for (auto& i : m_ShipList)
	{
		if (i->GetHP() != 0){
			return false;
		}
	}
	return true;*/


	for (unsigned int i = 0; i < m_ShipList.size(); ++i){

		printf_s("\n%d번째 배 들감\n", i);
		printf_s("HP : %d", m_ShipList[i]->GetHP());

		if (m_ShipList[i]->GetHP() !=0)
		{
			printf_s("\n%d번째배 HP가 0이아님\n",i);

			return false;
		}

	}
	return true;
}

HitResult Player::HitCheck(Position hitpos)
{
	for (unsigned int i = 0; i <m_ShipList.size(); ++i)
	{

		HitResult hitResult = m_ShipList[i]->Hitcheck(hitpos);
			

		if (hitResult != MISS){
			return hitResult; // HIT, DESTROY가 나옴
		}
	}
	return MISS;
}

void Player::UpdateEnemyZido(int x, int y)
{
	m_EnemyZido->MarkEnemyZido(x, y);

}
