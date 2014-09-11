#pragma once
#include "Enums.h"
#include "Player.h"

class GameManager
{
public:
	GameManager();
	~GameManager();

	void StartGame();

	//int GetZidoLength();
	int GetTurnCount() {return m_TurnCount; }

private:
	void SetGame();
	void RunningGame();
	void EndGame();
	Winner WhoIsWinner();
	void Setplayer();
	GameStatus CheckGameOVer();

	//void ChangeTurn();



private:
	Player* m_Attacker;
	Player* m_Defender;
	zido* m_Zido_Attacker;
	zido* m_Zido_Defender;
	
	Turn m_Turn;
	GameStatus m_Gamestatus;
	int m_TurnCount;
	int m_Winner;
};

