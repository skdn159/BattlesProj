#include "stdafx.h"
#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

void Player::SetupShips()
{
	Ship* ships[5] = { &m_Aircraft, &m_BattleShip, &m_Cruiser, &m_Destroyer[0], &m_Destroyer[1] };
	Position placePos;
	int direction;
	int dx, dy;

	for (int j = 0; j < _countof(ships);)
	{
		dx = dy = 0;
		placePos.x = rand() % 8;
		placePos.y = rand() % 8;
		direction = rand() % 2;

		if (direction == 0){ //가로배치
			if (placePos.x + ships[j]->GetLength() > 8){
				continue;
			}
			dx = 1;
		}

		if (direction == 1){//세로배치
			if (placePos.y + ships[j]->GetLength() > 8){
				continue;
			}
			dy = 1;
		}

		

		for (int i = 0; i < ships[j]->GetLength(); i++){
			ships[j]->AddPosition(placePos);
			placePos.x += dx;
			placePos.y += dy;
		}

		j++;
	}





}

void Player::PrintShips()
{
	m_Aircraft.PrintPos();
	m_BattleShip.PrintPos();
	m_Cruiser.PrintPos();
	m_Destroyer[0].PrintPos();
	m_Destroyer[1].PrintPos();

}
