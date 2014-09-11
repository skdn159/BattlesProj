#include "stdafx.h"
#include "GameManager.h"


GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

GameStatus GameManager::getStatus(){

	return gameStatus;
}
void GameManager::SetStatus(GameStatus status){

	gameStatus = status;

}