#include "stdafx.h"
#include "Player.h"
#include "Enums.h"




Player::Player()
{
	m_Name = "Anonymous";
	m_AirCraft = new AirCraft();
	m_BattleShip = new BattleShip();
	m_Cruiser = new Cruiser();
	m_Destroyer[0] = new Destroyer();
	m_Destroyer[1] = new Destroyer();
		
	m_ShipList.push_back(m_AirCraft);
	m_ShipList.push_back(m_BattleShip);
	m_ShipList.push_back(m_Cruiser);
	m_ShipList.push_back(m_Destroyer[0]);
	m_ShipList.push_back(m_Destroyer[1]);

	m_MyZido = new zido();
	m_EnemyZido = new zido();
	
	m_AttackDir = UP;
	m_HitCount = 0;
	m_HavetoFind = 0;

}

Player::~Player()
{
	for (auto& ship : m_ShipList){
		delete ship;
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
	
	
	
	return hitpos;
}

bool Player::IsAllSunK()
{
	for (unsigned int i = 0; i < m_ShipList.size(); ++i){



		if (m_ShipList[i]->GetHP() != 0)
		{
			return false;
		}

	}
	return true;
}

HitResult Player::HitCheck(Position hitpos)
{
	for (unsigned int i = 0; i <m_ShipList.size(); ++i)
	{
		HitResult hitresult = m_ShipList[i]->Hitcheck(hitpos);

		if (hitresult != MISS){
			return hitresult; // Hit, Destroy_shiptype가 안나옴
		}
	}
	
	return MISS;
}

void Player::UpdateEnemyZido(MarkHitResult markType, Position attackPos)
{
	int x = attackPos.x;
	int y = attackPos.y;

	if (markType == MARK_HIT){
		m_EnemyZido->MarkHit_EnemyZido(x, y);
	}
	
	if (markType == MARK_MISS){
		m_EnemyZido->MarkMiss_EnemyZido(x, y);
	}
}


void Player::ReceiveHitResult(Position attackPos, HitResult hitResult)
{
	//기능: 공격에 대한 결과를 통보 받아서
	//1. m_PrevHitPos를 세팅하고 (+필요시 FirstHitpo도 세팅)
	//2. 그 정보를 내 Enemy_Zido에 표시한다.
	//3. Aimode=changeAimode(); 로 모드를 세팅하고
	
	//1.
	m_PrevAttackPos = attackPos;
	

	//2.
	if (hitResult == MISS){

		UpdateEnemyZido(MARK_MISS, attackPos);
	}

	else{
		UpdateEnemyZido(MARK_HIT, attackPos);
	}

	//3.
	if (m_AImode == SEARCH_MODE){
		switch (hitResult)
		{
		
		case MISS:
			m_AImode = SEARCH_MODE;


			if (m_HavetoFind > 0){

				// 아직 못찾은것 
				// firstPos 주변으로 더 수색
				m_NextoFindPos = GenerateSurroundPos(m_FirstHitPos);
			}
			break;

		case HIT:
			m_AImode = TARGET_MODE;
			m_FirstHitPos = attackPos;
			m_NextoFindPos = attackPos;

			++m_HitCount;

			if (m_HavetoFind>0){
				//찾았다.
				m_HavetoFind--;
			}

			break;
		
		case DESTROY_DESTROYER:
			++m_HitCount;
			m_HitCount = m_HitCount - 2;

			if (m_HitCount > 0)
			{
				m_AImode = SEARCH_MODE;
				m_NextoFindPos = GenerateSurroundPos(m_FirstHitPos);

				m_HavetoFind++;
			}

			if (m_HavetoFind > 0){
			    //찾아서 부셨다
				m_HavetoFind--;
				m_AImode = SEARCH_MODE;
			}

			m_AImode = SEARCH_MODE;
			break;
		
		case DESTROY_CRUISER:
			++m_HitCount;
			m_HitCount = m_HitCount - 3;

			if (m_HitCount > 0){
				m_AImode = SEARCH_MODE;
				m_NextoFindPos = GenerateSurroundPos(m_FirstHitPos);

				m_HavetoFind++;
			}

			if (m_HavetoFind > 0){
				//찾아서 부셨다
				m_HavetoFind--;
				m_AImode = SEARCH_MODE;

			}
			m_AImode = SEARCH_MODE;

			break;
		
		case DESTROY_BATTLESHIP:
			++m_HitCount;
			m_HitCount = m_HitCount - 4;

			if (m_HitCount > 0){
				m_AImode = SEARCH_MODE;
				m_NextoFindPos = GenerateSurroundPos(m_FirstHitPos);

				m_HavetoFind++;
			}
		
			if (m_HavetoFind > 0){
				//찾아서 부셨다
				m_HavetoFind--;
				m_AImode = SEARCH_MODE;

			}
			m_AImode = SEARCH_MODE;

			break;
		
		case DESTROY_AIRCRAFT:
			++m_HitCount;
			m_HitCount = m_HitCount - 5;

			if (m_HitCount > 0){
				m_AImode = SEARCH_MODE;
				m_NextoFindPos = GenerateSurroundPos(m_FirstHitPos);

				m_HavetoFind++;
			}
			if (m_HavetoFind > 0){
				//찾아서 부셨다
				m_HavetoFind--;
				m_AImode = SEARCH_MODE;
			}
			m_AImode = SEARCH_MODE;

			break;
		
		default:
			m_AImode = SEARCH_MODE;
			break;
		}
		
	}
	
	else // TARGETMODE 일경우
	{
		switch (hitResult)
		{
		case MISS:
			m_NextoFindPos = m_FirstHitPos;
			m_AttackDir = ReverseAttackDir(m_AttackDir);
			break;

		case HIT:
			m_NextoFindPos = attackPos;

			//만약 공격방향대로 한칸 갔는데 갈수 없다면 FirstHitpos + 역방향 탐색
			attackPos = GenerateNextattackPos(m_AttackDir, m_NextoFindPos);
			if (m_EnemyZido->AttackValidCheck(attackPos.x, attackPos.y) == false){
				m_NextoFindPos = m_FirstHitPos;
				m_AttackDir = ReverseAttackDir(m_AttackDir);
			}
			++m_HitCount;
			break;
	

		case DESTROY_DESTROYER:
			++m_HitCount;
			m_HitCount = m_HitCount-2;

			if (m_HitCount > 0){
				m_AImode = SEARCH_MODE;
				m_NextoFindPos = GenerateSurroundPos(m_FirstHitPos);

				m_HavetoFind++;
			}

			if (m_HavetoFind > 0){
				//찾아서 부셨다
				m_HavetoFind--;
				m_AImode = SEARCH_MODE;

			}
			m_AImode = SEARCH_MODE;
			break;

		case DESTROY_CRUISER:
			++m_HitCount;
			m_HitCount = m_HitCount - 3;

			if (m_HitCount > 0){
				m_AImode = SEARCH_MODE;
				m_NextoFindPos = GenerateSurroundPos(m_FirstHitPos);

				m_HavetoFind++;
			}
			
			if (m_HavetoFind > 0){
				//찾아서 부셨다
				m_HavetoFind--;
				m_AImode = SEARCH_MODE;

			}
			m_AImode = SEARCH_MODE;
			break;

		case DESTROY_BATTLESHIP:
			++m_HitCount;
			m_HitCount = m_HitCount - 4;

			if (m_HitCount > 0){
				m_AImode = SEARCH_MODE;
				m_NextoFindPos = GenerateSurroundPos(m_FirstHitPos);

				m_HavetoFind++;
			}

			if (m_HavetoFind > 0){
				//찾아서 부셨다
				m_HavetoFind--;
				m_AImode = SEARCH_MODE;

			}
			m_AImode = SEARCH_MODE;
			break;

		case DESTROY_AIRCRAFT:
			++m_HitCount;
			m_HitCount = m_HitCount - 5;

			if (m_HitCount > 0){
				m_AImode = SEARCH_MODE;
				m_NextoFindPos = GenerateSurroundPos(m_FirstHitPos);

				m_HavetoFind++;
			}

			if (m_HavetoFind > 0){
				//찾아서 부셨다
				m_HavetoFind--;
				m_AImode = SEARCH_MODE;

			}
			m_AImode = SEARCH_MODE;
			break;

		default:
			m_AImode = SEARCH_MODE;
			break;
		}
	}
}

void Player::LoadSearchList() //우선순위 search List
{
	m_SearchList_First.clear();
	m_SearchList_Second.clear();
	m_SearchList_Third.clear();

	m_SearchList_First.push_back({ 1, 1 });
	m_SearchList_First.push_back({ 1, 3 });
	m_SearchList_First.push_back({ 1, 5 });
	m_SearchList_First.push_back({ 2, 4 });
	m_SearchList_First.push_back({ 2, 6 });
	m_SearchList_First.push_back({ 3, 1 });
	m_SearchList_First.push_back({ 4, 2 });
	m_SearchList_First.push_back({ 4, 4 });
	m_SearchList_First.push_back({ 4, 6 });
	m_SearchList_First.push_back({ 5, 1 });
	m_SearchList_First.push_back({ 5, 5 });
	m_SearchList_First.push_back({ 6, 2 });
	m_SearchList_First.push_back({ 6, 4 });
	m_SearchList_First.push_back({ 6, 6 });

	m_SearchList_Second.push_back({ 3, 3 });
	m_SearchList_Second.push_back({ 0, 2 });
	m_SearchList_Second.push_back({ 0, 6 });
	m_SearchList_Second.push_back({ 2, 0 });
	m_SearchList_Second.push_back({ 2, 2 });
	m_SearchList_Second.push_back({ 3, 5 });
	m_SearchList_Second.push_back({ 3, 7 });
	m_SearchList_Second.push_back({ 5, 3 });
	m_SearchList_Second.push_back({ 6, 0 });
	m_SearchList_Second.push_back({ 7, 3 });

	m_SearchList_Third.push_back({ 0, 0 });
	m_SearchList_Third.push_back({ 0, 4 });
	m_SearchList_Third.push_back({ 1, 7 });
	m_SearchList_Third.push_back({ 4, 0 });
	m_SearchList_Third.push_back({ 5, 7 });
	m_SearchList_Third.push_back({ 7, 1 });
	m_SearchList_Third.push_back({ 7, 5 });
	m_SearchList_Third.push_back({ 7, 7 });

}

Position Player::AI_Attack()
{
	Position hitpos;
	int zidoLength = m_MyZido->GetMapLength();

	if (m_AImode == SEARCH_MODE&&m_HavetoFind==0){ 

		if (!m_SearchList_First.empty()){
			std::vector<Position>::iterator iterpos;

			while (!m_SearchList_First.empty())
			{
				int i = rand() % m_SearchList_First.size();
				iterpos = m_SearchList_First.begin() + i;

				Position hitpos = *iterpos;

				if (m_EnemyZido->AttackValidCheck(hitpos.x, hitpos.y) == false){
					m_SearchList_First.erase(iterpos);

					if (m_SearchList_First.empty() == true){
						break;
					}

					continue;
				}

				if (m_EnemyZido->AttackValidCheck(hitpos.x, hitpos.y) == true){
					return hitpos;
				}

				return hitpos;

			}
		}

		if (!m_SearchList_Second.empty()){
			std::vector<Position>::iterator iterpos;

			while (!m_SearchList_Second.empty())
			{
				int i = rand() % m_SearchList_Second.size();
				iterpos = m_SearchList_Second.begin() + i;
				Position hitpos = *iterpos;

				if (m_EnemyZido->AttackValidCheck(hitpos.x, hitpos.y) == false){
					m_SearchList_Second.erase(iterpos);

					if (m_SearchList_Second.empty() == true){
						break;
					}

					continue;
				}

				if (m_EnemyZido->AttackValidCheck(hitpos.x, hitpos.y) == true){
					return hitpos;
				}
				return hitpos;
			}
		}

		if (!m_SearchList_Third.empty()){
			std::vector<Position>::iterator iterpos;

			while (!m_SearchList_Third.empty())
			{
				int i = rand() % m_SearchList_Third.size();
				iterpos = m_SearchList_Third.begin() + i;
				Position hitpos = *iterpos;

				if (m_EnemyZido->AttackValidCheck(hitpos.x, hitpos.y) == false){
					m_SearchList_Third.erase(iterpos);

					if (m_SearchList_Third.empty() == true){
						break;
					}
					continue;
				}

				if (m_EnemyZido->AttackValidCheck(hitpos.x, hitpos.y) == true){
					return hitpos;
				}
				return hitpos;
			}
		}
		//우선순위 리스트에 아무것도 없을시에 랜덤으로...
		do
		{
			hitpos.x = rand() % zidoLength;
			hitpos.y = rand() % zidoLength;

		} while (m_EnemyZido->AttackValidCheck(hitpos.x, hitpos.y) == false);

		return hitpos;
	}
		
	//TARGET_MODE or HavetoFind>0 인 경우
	else
	{
		//기능
		//1. Aimode를 바탕으로 적절한 nextattackPos를 반환해야한다

		Direction_MY nextDir = m_AttackDir;
		Position nextAttackPos = GenerateNextattackPos(nextDir, m_NextoFindPos);

		if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false){

			nextDir = ReverseAttackDir(nextDir); //반대방향으로 한칸
			nextAttackPos = GenerateNextattackPos(nextDir, m_NextoFindPos);

			if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
			{
				nextDir = TurnRightAttackDir(nextDir); //반대방향의 우회전으로 한칸
				nextAttackPos = GenerateNextattackPos(nextDir, m_NextoFindPos);

				if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
				{
					nextDir = ReverseAttackDir(nextDir); //마지막 남은 방향으로 한칸
					nextAttackPos = GenerateNextattackPos(nextDir, m_NextoFindPos);

					if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
					{
						//사방팔방이 다막힘

						//그럼 대각선 및 2칸 주변을 탐색
						nextAttackPos = GenerateSurroundPos(m_NextoFindPos);
						if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
						{
							//최악 랜덤
							do
							{
								hitpos.x = rand() % zidoLength;
								hitpos.y = rand() % zidoLength;

							} while (m_EnemyZido->AttackValidCheck(hitpos.x, hitpos.y) == false);

							return hitpos; //랜덤 좌표
						}
						return nextAttackPos;
					}
					m_AttackDir = nextDir;
					return nextAttackPos; // 마지막 남은 방향으로 한칸
				}
				m_AttackDir = nextDir;
				return nextAttackPos; // 반대방향의 우회전으로 한칸
			}
			m_AttackDir = nextDir;
			return nextAttackPos; // 반대방향으로 한칸
		}
		m_AttackDir = nextDir;
		return nextAttackPos; //m_AttackDir 로 한칸
	}
}


Position Player::GenerateNextattackPos(Direction_MY dir, Position attackPos)
{
	Position NextattackPos=attackPos;

	switch (dir)
	{
	case UP:
		NextattackPos.x--;
		break;
	case DOWN:
		NextattackPos.x++;
		break;
	case LEFT:
		NextattackPos.y--;
		break;
	case RIGHT:
		NextattackPos.y++;
		break;
	default:
		break;
	}
	return NextattackPos;
}

Direction_MY Player::ReverseAttackDir(Direction_MY tempDir)
{
	Direction_MY NextattackDir;

	switch (tempDir)
	{
	case UP:
		NextattackDir = DOWN;
		break;
	case DOWN:
		NextattackDir = UP;
		break;
	case LEFT:
		NextattackDir = RIGHT;
		break;
	case RIGHT:
		NextattackDir = LEFT;
		break;
	default:
		break;
	}
	return NextattackDir;
}

Direction_MY Player::TurnRightAttackDir(Direction_MY tempDir)
{
	Direction_MY NextattackDir;
	
	switch (tempDir)
	{
	case UP:
		NextattackDir = RIGHT;
		break;
	case DOWN:
		NextattackDir = LEFT;
		break;
	case LEFT:
		NextattackDir = UP;
		break;
	case RIGHT:
		NextattackDir = DOWN;
		break;

	default:
		break;
	}

	return NextattackDir;
}


Position Player::MakeNextDestroyPos(Direction_MY chaseDir, Position tempPos)
{
	//추적할 파괴된 방향으로 다음 좌표값을 생성
	switch (chaseDir)
	{
	case UP:
		tempPos.x--;
		break;
	case DOWN:
		tempPos.x++;
		break;
	case LEFT:
		tempPos.y--;
		break;
	case RIGHT:
		tempPos.y++;
		break;
	
	}
	return tempPos;
}


Position Player::GenerateSurroundPos(Position FirstAttackPos)
{
	//1. firstHitPos를 중심으로 사방으로 1칸씩을봄
	//Valid하면 가능한 곳에서 임의로 한곳을 배출

	//2. Valid하지 않다면 firstHitPos를 주변으로 대각선으로 한칸씩을 봄
	//그 중에서 가능한 곳을 배출

	//3. 해당없으면 2칸씩을 가봄

	//4. 다안되면 Search로 돌리고 랜덤

	//1.
	Direction_MY nextDir = m_AttackDir;
	Position nextAttackPos = GenerateNextattackPos(nextDir, FirstAttackPos);

	if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false){

		nextDir = ReverseAttackDir(nextDir); //반대방향으로 한칸
		nextAttackPos = GenerateNextattackPos(nextDir, FirstAttackPos);

		if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
		{
			nextDir = TurnRightAttackDir(nextDir); //반대방향의 우회전으로 한칸
			nextAttackPos = GenerateNextattackPos(nextDir, FirstAttackPos);

			if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
			{
				nextDir = ReverseAttackDir(nextDir); //마지막 남은 방향으로 한칸
				nextAttackPos = GenerateNextattackPos(nextDir, FirstAttackPos);

				if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
				{
					//사방팔방이 다막힘 
					//2. 그럼 대각선으로 한번씩 가봄

					//북동
					nextAttackPos = GeneratePosByManual({ FirstAttackPos.x - 1, FirstAttackPos.y + 1 });
					if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
					{
						//남동
						nextAttackPos = GeneratePosByManual({ FirstAttackPos.x + 1, FirstAttackPos.y + 1 });
						if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
						{
							//북서
							nextAttackPos = GeneratePosByManual({ FirstAttackPos.x - 1, FirstAttackPos.y - 1 });
							if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
							{
								//남서
								nextAttackPos = GeneratePosByManual({ FirstAttackPos.x + 1, FirstAttackPos.y - 1 });
								if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
								{
									//대각선으로 못감
									// 3. 그럼 원래 위치에서 2칸씩 가본다.
									
									//원래 위치에서 UP으로 2칸
									nextAttackPos = GeneratePosByManual({ FirstAttackPos.x - 2, FirstAttackPos.y });
									if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
									{
										//원래 위치에서 DOWN으로 2칸
										nextAttackPos = GeneratePosByManual({ FirstAttackPos.x + 2, FirstAttackPos.y  });
										if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
										{
											//원래 위치에서 RIGHT으로 2칸
											nextAttackPos = GeneratePosByManual({ FirstAttackPos.x, FirstAttackPos.y +2 });

											if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
											{
												//원래 위치에서 LEFT로 2칸
												nextAttackPos = GeneratePosByManual({ FirstAttackPos.x , FirstAttackPos.y - 2 });

												if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
												{	//눈목a
													nextAttackPos = GeneratePosByManual({ FirstAttackPos.x -2 , FirstAttackPos.y + 1 });

													if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
													{	//눈목b
														nextAttackPos = GeneratePosByManual({ FirstAttackPos.x -1 , FirstAttackPos.y + 2 });

														if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
														{	//눈목a
															nextAttackPos = GeneratePosByManual({ FirstAttackPos.x + 1, FirstAttackPos.y +2 });

															if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
															{	//눈목b
																nextAttackPos = GeneratePosByManual({ FirstAttackPos.x + 2, FirstAttackPos.y + 1 });

																if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
																{	//눈목a
																	nextAttackPos = GeneratePosByManual({ FirstAttackPos.x + 2, FirstAttackPos.y - 1 });

																	if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
																	{	//눈목b
																		nextAttackPos = GeneratePosByManual({ FirstAttackPos.x + 1, FirstAttackPos.y - 2 });

																		if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
																		{	//눈목a
																			nextAttackPos = GeneratePosByManual({ FirstAttackPos.x -2, FirstAttackPos.y - 1 });

																			if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
																			{	//눈목b
																				nextAttackPos = GeneratePosByManual({ FirstAttackPos.x - 1, FirstAttackPos.y - 2 });

																				if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
																				{
																					//다 안됨
																					m_HavetoFind = 0;
																					m_AImode = SEARCH_MODE;
																					m_HitCount = 0;

																				}return nextAttackPos;
																			}return nextAttackPos;
																		}return nextAttackPos;
																	}return nextAttackPos;
																}return nextAttackPos;
															}return nextAttackPos;
														}return nextAttackPos;
													}return nextAttackPos;
												}
												return nextAttackPos;// LEFT로 2칸
											}
											return nextAttackPos; // RIGHT로 2칸
										}
										return nextAttackPos; // DOWN으로 2칸
									}
									return nextAttackPos; // UP으로 2칸

								}
								return nextAttackPos; // 대각선: 남서
							}
							return nextAttackPos; // 대각선: 북서

						}
						return nextAttackPos; // 대각선: 남동
					}
					return nextAttackPos; // 대각선: 북동
				}
				m_AttackDir = nextDir;
				return nextAttackPos; //나머지 한방향 한칸
			}
			m_AttackDir = nextDir;
			return nextAttackPos; // 반대방향 우회전 한칸
		}
		m_AttackDir = nextDir;
		return nextAttackPos; // 반대방향 한칸

	}
	m_AttackDir = nextDir;
	return nextAttackPos; //원방향 한칸

}

Position Player::GeneratePosByManual(Position tempPos)
{
	Position CrossPos;
	CrossPos.x = tempPos.x;
	CrossPos.y = tempPos.y;

	return CrossPos;
}


