#pragma once
#include "Enums.h"
#include "Player.h"

class GameManager
{
public:
	GameManager();
	~GameManager();

	void StartGame(int Gameplay);
		
	float GetTurnCount() { return m_TurnCount; }
	float GetAVG_TurnCount(int GamePlay){ return TotalCount/GamePlay; }
	void Networking();

private:
	void SetGame();
	void Setplayer();
	void RunningGame();
	void EndGame();

	Winner WhoIsWinner();
	GameStatus CheckGameOVer();

	//for NetWork
	HitResult TranslateHitResult(short info);
	
private:
	Turn m_Turn;
	GameStatus m_Gamestatus;

	Player* m_Attacker;
	Player* m_Defender;
	zido* m_Zido_Attacker;
	zido* m_Zido_Defender;
	
	
	float m_TurnCount;
	int m_Winner;
	float TotalCount;
};

