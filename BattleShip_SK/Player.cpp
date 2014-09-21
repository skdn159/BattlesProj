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
		//�������� �� üũ����
		
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

	// �ߺ�check

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
			return hitresult; // Hit, Destroy_shiptype�� �ȳ���
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
	//���: ���ݿ� ���� ����� �뺸 �޾Ƽ�
	//1. m_PrevHitPos�� �����ϰ� (+�ʿ�� FirstHitpo�� ����)
	//2. �� ������ �� Enemy_Zido�� ǥ���Ѵ�.
	//3. Aimode=changeAimode(); �� ��带 �����ϰ�
	
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

				// ���� ��ã���� 
				// firstPos �ֺ����� �� ����
				m_NextoFindPos = GenerateSurroundPos(m_FirstHitPos);
			}
			break;

		case HIT:
			m_AImode = TARGET_MODE;
			m_FirstHitPos = attackPos;
			m_NextoFindPos = attackPos;

			++m_HitCount;

			if (m_HavetoFind>0){
				//ã�Ҵ�.
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
			    //ã�Ƽ� �μ̴�
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
				//ã�Ƽ� �μ̴�
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
				//ã�Ƽ� �μ̴�
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
				//ã�Ƽ� �μ̴�
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
	
	else // TARGETMODE �ϰ��
	{
		switch (hitResult)
		{
		case MISS:
			m_NextoFindPos = m_FirstHitPos;
			m_AttackDir = ReverseAttackDir(m_AttackDir);
			break;

		case HIT:
			m_NextoFindPos = attackPos;

			//���� ���ݹ����� ��ĭ ���µ� ���� ���ٸ� FirstHitpos + ������ Ž��
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
				//ã�Ƽ� �μ̴�
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
				//ã�Ƽ� �μ̴�
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
				//ã�Ƽ� �μ̴�
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
				//ã�Ƽ� �μ̴�
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

void Player::LoadSearchList() //�켱���� search List
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
		//�켱���� ����Ʈ�� �ƹ��͵� �����ÿ� ��������...
		do
		{
			hitpos.x = rand() % zidoLength;
			hitpos.y = rand() % zidoLength;

		} while (m_EnemyZido->AttackValidCheck(hitpos.x, hitpos.y) == false);

		return hitpos;
	}
		
	//TARGET_MODE or HavetoFind>0 �� ���
	else
	{
		//���
		//1. Aimode�� �������� ������ nextattackPos�� ��ȯ�ؾ��Ѵ�

		Direction_MY nextDir = m_AttackDir;
		Position nextAttackPos = GenerateNextattackPos(nextDir, m_NextoFindPos);

		if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false){

			nextDir = ReverseAttackDir(nextDir); //�ݴ�������� ��ĭ
			nextAttackPos = GenerateNextattackPos(nextDir, m_NextoFindPos);

			if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
			{
				nextDir = TurnRightAttackDir(nextDir); //�ݴ������ ��ȸ������ ��ĭ
				nextAttackPos = GenerateNextattackPos(nextDir, m_NextoFindPos);

				if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
				{
					nextDir = ReverseAttackDir(nextDir); //������ ���� �������� ��ĭ
					nextAttackPos = GenerateNextattackPos(nextDir, m_NextoFindPos);

					if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
					{
						//����ȹ��� �ٸ���

						//�׷� �밢�� �� 2ĭ �ֺ��� Ž��
						nextAttackPos = GenerateSurroundPos(m_NextoFindPos);
						if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
						{
							//�־� ����
							do
							{
								hitpos.x = rand() % zidoLength;
								hitpos.y = rand() % zidoLength;

							} while (m_EnemyZido->AttackValidCheck(hitpos.x, hitpos.y) == false);

							return hitpos; //���� ��ǥ
						}
						return nextAttackPos;
					}
					m_AttackDir = nextDir;
					return nextAttackPos; // ������ ���� �������� ��ĭ
				}
				m_AttackDir = nextDir;
				return nextAttackPos; // �ݴ������ ��ȸ������ ��ĭ
			}
			m_AttackDir = nextDir;
			return nextAttackPos; // �ݴ�������� ��ĭ
		}
		m_AttackDir = nextDir;
		return nextAttackPos; //m_AttackDir �� ��ĭ
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
	//������ �ı��� �������� ���� ��ǥ���� ����
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
	//1. firstHitPos�� �߽����� ������� 1ĭ������
	//Valid�ϸ� ������ ������ ���Ƿ� �Ѱ��� ����

	//2. Valid���� �ʴٸ� firstHitPos�� �ֺ����� �밢������ ��ĭ���� ��
	//�� �߿��� ������ ���� ����

	//3. �ش������ 2ĭ���� ����

	//4. �پȵǸ� Search�� ������ ����

	//1.
	Direction_MY nextDir = m_AttackDir;
	Position nextAttackPos = GenerateNextattackPos(nextDir, FirstAttackPos);

	if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false){

		nextDir = ReverseAttackDir(nextDir); //�ݴ�������� ��ĭ
		nextAttackPos = GenerateNextattackPos(nextDir, FirstAttackPos);

		if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
		{
			nextDir = TurnRightAttackDir(nextDir); //�ݴ������ ��ȸ������ ��ĭ
			nextAttackPos = GenerateNextattackPos(nextDir, FirstAttackPos);

			if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
			{
				nextDir = ReverseAttackDir(nextDir); //������ ���� �������� ��ĭ
				nextAttackPos = GenerateNextattackPos(nextDir, FirstAttackPos);

				if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
				{
					//����ȹ��� �ٸ��� 
					//2. �׷� �밢������ �ѹ��� ����

					//�ϵ�
					nextAttackPos = GeneratePosByManual({ FirstAttackPos.x - 1, FirstAttackPos.y + 1 });
					if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
					{
						//����
						nextAttackPos = GeneratePosByManual({ FirstAttackPos.x + 1, FirstAttackPos.y + 1 });
						if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
						{
							//�ϼ�
							nextAttackPos = GeneratePosByManual({ FirstAttackPos.x - 1, FirstAttackPos.y - 1 });
							if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
							{
								//����
								nextAttackPos = GeneratePosByManual({ FirstAttackPos.x + 1, FirstAttackPos.y - 1 });
								if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
								{
									//�밢������ ����
									// 3. �׷� ���� ��ġ���� 2ĭ�� ������.
									
									//���� ��ġ���� UP���� 2ĭ
									nextAttackPos = GeneratePosByManual({ FirstAttackPos.x - 2, FirstAttackPos.y });
									if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
									{
										//���� ��ġ���� DOWN���� 2ĭ
										nextAttackPos = GeneratePosByManual({ FirstAttackPos.x + 2, FirstAttackPos.y  });
										if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
										{
											//���� ��ġ���� RIGHT���� 2ĭ
											nextAttackPos = GeneratePosByManual({ FirstAttackPos.x, FirstAttackPos.y +2 });

											if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
											{
												//���� ��ġ���� LEFT�� 2ĭ
												nextAttackPos = GeneratePosByManual({ FirstAttackPos.x , FirstAttackPos.y - 2 });

												if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
												{	//����a
													nextAttackPos = GeneratePosByManual({ FirstAttackPos.x -2 , FirstAttackPos.y + 1 });

													if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
													{	//����b
														nextAttackPos = GeneratePosByManual({ FirstAttackPos.x -1 , FirstAttackPos.y + 2 });

														if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
														{	//����a
															nextAttackPos = GeneratePosByManual({ FirstAttackPos.x + 1, FirstAttackPos.y +2 });

															if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
															{	//����b
																nextAttackPos = GeneratePosByManual({ FirstAttackPos.x + 2, FirstAttackPos.y + 1 });

																if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
																{	//����a
																	nextAttackPos = GeneratePosByManual({ FirstAttackPos.x + 2, FirstAttackPos.y - 1 });

																	if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
																	{	//����b
																		nextAttackPos = GeneratePosByManual({ FirstAttackPos.x + 1, FirstAttackPos.y - 2 });

																		if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
																		{	//����a
																			nextAttackPos = GeneratePosByManual({ FirstAttackPos.x -2, FirstAttackPos.y - 1 });

																			if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
																			{	//����b
																				nextAttackPos = GeneratePosByManual({ FirstAttackPos.x - 1, FirstAttackPos.y - 2 });

																				if (m_EnemyZido->AttackValidCheck(nextAttackPos.x, nextAttackPos.y) == false)
																				{
																					//�� �ȵ�
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
												return nextAttackPos;// LEFT�� 2ĭ
											}
											return nextAttackPos; // RIGHT�� 2ĭ
										}
										return nextAttackPos; // DOWN���� 2ĭ
									}
									return nextAttackPos; // UP���� 2ĭ

								}
								return nextAttackPos; // �밢��: ����
							}
							return nextAttackPos; // �밢��: �ϼ�

						}
						return nextAttackPos; // �밢��: ����
					}
					return nextAttackPos; // �밢��: �ϵ�
				}
				m_AttackDir = nextDir;
				return nextAttackPos; //������ �ѹ��� ��ĭ
			}
			m_AttackDir = nextDir;
			return nextAttackPos; // �ݴ���� ��ȸ�� ��ĭ
		}
		m_AttackDir = nextDir;
		return nextAttackPos; // �ݴ���� ��ĭ

	}
	m_AttackDir = nextDir;
	return nextAttackPos; //������ ��ĭ

}

Position Player::GeneratePosByManual(Position tempPos)
{
	Position CrossPos;
	CrossPos.x = tempPos.x;
	CrossPos.y = tempPos.y;

	return CrossPos;
}


