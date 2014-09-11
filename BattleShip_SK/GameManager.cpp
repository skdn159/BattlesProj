#include "stdafx.h"
#include "GameManager.h"
#include "Player.h"
#include "zido.h"
#include "Ship.h"
#include "DrawSetting.h"

//�̰� ���� �ǹ�?
class zido;
class player;
class ship;

GameManager::GameManager()
{
	m_Attacker = nullptr;
	m_Defender = nullptr;
	m_Zido_Attacker = nullptr;
	m_Zido_Defender = nullptr;
	m_Gamestatus = GAMEOVER;
	m_TurnCount;
	m_Winner = NO_ONE;
}


GameManager::~GameManager()
{
}


void GameManager::StartGame()
{
	SetGame();
	getchar();
	system("cls");
	RunningGame();
	//system("cls");

	EndGame();
}


void GameManager::SetGame()
{
	srand((unsigned int)time(NULL));
	
	Setplayer();
	
	//�÷��̾� ����
	m_Attacker->RandomSetupShips();
	m_Defender->RandomSetupShips();

	//�÷��̾��� ������ �޾ƿ�
	m_Zido_Attacker = m_Attacker->GetMyZido();
	m_Zido_Defender = m_Defender->GetMyZido();

	//Attacker(��)�� ���� ���
	m_Attacker->GetMyZido()->PrintZido({MY_ZIDO_X,MY_ZIDO_Y});
	m_Defender->GetMyZido()->PrintZido({ ENEMY_ZIDO_X, ENEMY_ZIDO_Y });
	//m_Attacker->GetEnemyZido()->PrintZido();
	//m_Defender->GetEnemyZido()->PrintZido(); 

	m_Gamestatus = PLAYING;
}

void GameManager::Setplayer()
{
	m_Attacker = new Player();
	m_Defender = new Player();
	m_Attacker->SetPlayerName("Attacker");
	m_Defender->SetPlayerName("Defender");

	m_Attacker->GetMyZido()->SetZidoName(m_Attacker->GetPlayerName());
	m_Attacker->GetEnemyZido()->SetZidoName(m_Attacker->GetPlayerName() + "'s EnemyZido");
	m_Defender->GetMyZido()->SetZidoName(m_Defender->GetPlayerName());
	m_Defender->GetEnemyZido()->SetZidoName(m_Defender->GetPlayerName() + "'s EnemyZido");
	/*
	std::string name = m_Attacker->GetEnemyZido()->GetZidoName();
	std::cout << name << std::endl;*/
	m_Turn = ATTACKER;

}

void GameManager::RunningGame()
{
	m_TurnCount = 0;
	if (m_Gamestatus != PLAYING){ 
		printf_s("Gamestatus is Not 'PLAYING'\n");
		return; }

	while (m_Gamestatus == PLAYING)
	{
		
		switch (m_Turn)
		{
			case ATTACKER:
			{
			Position attackPosition = m_Attacker->RandomAttack();
			HitResult hitResult = m_Defender->HitCheck(attackPosition);
			
			if (hitResult == MISS)printf_s("MISS\n");
			if (hitResult == HIT)printf_s("HIT\n");
			if (hitResult == DESTROY)printf_s("DESTROY\n");

			m_Zido_Defender->ZidoMarkByGM(attackPosition);
			m_Turn = DEFENDER;
			//getchar();
			//++m_TurnCount;
			

			break;


			}


			case DEFENDER:
			{
			Position attackPosition = m_Defender->RandomAttack();
			HitResult hitResult = m_Attacker->HitCheck(attackPosition);
			//hitResult�� �̿��켭 �÷��̾�� hit miss�� �˷���
			if (hitResult == MISS)printf_s("MISS\n");
			if (hitResult == HIT)printf_s("HIT\n");
			if (hitResult == DESTROY)printf_s("DESTROY\n");
			m_Zido_Attacker->ZidoMarkByGM(attackPosition);
			m_Turn = ATTACKER;
			//getchar();
			//++m_TurnCount;
			

			break;

			}
				
		}
		//ȭ�鿡 ���Ӹ޴����� ���ڰ� ������ ���� ǥ��
		
		//m_Attacker->GetMyZido()->PrintZido({MY_ZIDO_X, MY_ZIDO_Y});
		//m_Defender->GetMyZido()->PrintZido({ENEMY_ZIDO_X,ENEMY_ZIDO_Y});
		m_Zido_Attacker->PrintZido({ MY_ZIDO_X, MY_ZIDO_Y });
		m_Zido_Defender->PrintZido({ ENEMY_ZIDO_X, ENEMY_ZIDO_Y });

		//�׷��ٸ� ������ ������ �ִ� atk zido�� ??
		++m_TurnCount;
		printf_s("count:%d", m_TurnCount/2);
		//game check
		m_Gamestatus = CheckGameOVer();

	} 
}

GameStatus GameManager::CheckGameOVer()
{
	//�� ��ΰ���
	if (m_Attacker->IsAllSunK() || m_Defender->IsAllSunK()||m_Gamestatus==GAMEOVER)
	{
		return GAMEOVER;
	}
	
	// �÷��̾ �߰��� ������ ��쵵 �߰�

	return PLAYING;
}

void GameManager::EndGame()
{
	m_Winner=WhoIsWinner();

	if (m_Winner == WINNER_ATTACKER){
		printf_s("\nWinner is %s\n", m_Attacker->GetPlayerName().c_str());
	}

	if (m_Winner == WINNER_DEFENDER){
		printf_s("\nWinner is %s\n", m_Defender->GetPlayerName().c_str());
	}
	if (m_Winner == NO_ONE){
		printf_s("\nDRAW!\n");
	}
	// �¸��� �й��ڿ� ���� ����ȭ��
	// 
	printf_s("\nGAMEOVER!\n");
	printf_s("count:%d",m_TurnCount/2);
}

Winner GameManager::WhoIsWinner()
{
	if (m_Attacker->IsAllSunK()){
		return WINNER_DEFENDER;
	}

	if (m_Defender->IsAllSunK()){
		return WINNER_ATTACKER;
	}

	return NO_ONE;
}

//int GameManager::GetZidoLength()
//{
//	int zidoLength;
//	zidoLength = m_Zido_Attacker->GetMapLength();
//
//	return zidoLength;
//}

