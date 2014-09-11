#include "stdafx.h"
#include "GameManager.h"
#include "Player.h"
#include "zido.h"
#include "Ship.h"
#include "DrawSetting.h"

//이건 무슨 의미?
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
	
	//플레이어 세팅
	m_Attacker->RandomSetupShips();
	m_Defender->RandomSetupShips();

	//플레이어의 지도를 받아옴
	m_Zido_Attacker = m_Attacker->GetMyZido();
	m_Zido_Defender = m_Defender->GetMyZido();

	//Attacker(나)의 지도 출력
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
			//hitResult를 이용헤서 플레이어게 hit miss를 알려줌
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
		//화면에 게임메니저가 각자가 제출한 것을 표시
		
		//m_Attacker->GetMyZido()->PrintZido({MY_ZIDO_X, MY_ZIDO_Y});
		//m_Defender->GetMyZido()->PrintZido({ENEMY_ZIDO_X,ENEMY_ZIDO_Y});
		m_Zido_Attacker->PrintZido({ MY_ZIDO_X, MY_ZIDO_Y });
		m_Zido_Defender->PrintZido({ ENEMY_ZIDO_X, ENEMY_ZIDO_Y });

		//그렇다면 개인이 가지고 있는 atk zido는 ??
		++m_TurnCount;
		printf_s("count:%d", m_TurnCount/2);
		//game check
		m_Gamestatus = CheckGameOVer();

	} 
}

GameStatus GameManager::CheckGameOVer()
{
	//배 모두격추
	if (m_Attacker->IsAllSunK() || m_Defender->IsAllSunK()||m_Gamestatus==GAMEOVER)
	{
		return GAMEOVER;
	}
	
	// 플레이어가 중간에 나가는 경우도 추가

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
	// 승리자 패배자에 따른 엔딩화면
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

