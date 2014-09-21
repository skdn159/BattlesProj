#include "stdafx.h"
#include "GameManager.h"
#include "Player.h"
#include "zido.h"
#include "Ship.h"
#include "DrawSetting.h"

//class zido;
//class player;
//class ship;

const char* const ATTACK_RESULT_STR[] = {
	"No Result",
	"Miss",
	"Hit",
	"Aircraft Destroyed",
	"Battleship Destroyed",
	"Cruiser Destroyed",
	"Destroyer Destroyed",
};

GameManager::GameManager()
{
	m_Attacker = nullptr;
	m_Defender = nullptr;
	m_Zido_Attacker = nullptr;
	m_Zido_Defender = nullptr;
	m_Gamestatus = GAMEOVER;
	m_Winner = NO_ONE;

	TotalCount = 0;
}


GameManager::~GameManager()
{
	delete m_Attacker;
	delete m_Defender;
}


void GameManager::StartGame(int GamePlay)
{
	for (int i = 0; i < GamePlay; i++){

		if (i%200==0){
			printf_s("%d판째 중\n ",i);

		}

		SetGame();
		//system("cls");
		RunningGame();
		//system("cls");
		//EndGame();
	}
}

void GameManager::SetGame()
{
	srand((unsigned int)time(NULL));
	
	Setplayer();
	
	//플레이어 세팅
	m_Attacker->RandomSetupShips();
	m_Defender->RandomSetupShips();
		
	m_Zido_Attacker = m_Attacker->GetMyZido();
	m_Zido_Defender = m_Defender->GetMyZido();

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
	
	m_Attacker->SetAImodeSearch();
	m_Defender->SetAImodeSearch();

	m_Attacker->LoadSearchList();
	m_Defender->LoadSearchList();

	m_Turn = ATTACKER;
}

void GameManager::RunningGame()
{
	m_TurnCount = 0;
	if (m_Gamestatus != PLAYING){
		printf_s("Gamestatus is Not 'PLAYING'\n");
		return;
	}

	while (m_Gamestatus == PLAYING)
	{
		
		switch (m_Turn)
		{
			case ATTACKER:
			{
			Position attackPosition = m_Attacker->AI_Attack();
			HitResult hitResult = m_Defender->HitCheck(attackPosition);
			m_Attacker->ReceiveHitResult(attackPosition, hitResult);

			m_Zido_Defender->ZidoMarkByGM(attackPosition);

		    //m_Defender->GetMyZido()->PrintZido(ENEMY_ZIDO_X, ENEMY_ZIDO_Y);
			//m_Attacker->GetEnemyZido()->PrintZido(MY_ZIDO_X, MY_ZIDO_Y);


			m_Turn = DEFENDER;
			//getchar();
			++m_TurnCount;
			break;
			}
				
			case DEFENDER:
			{
			Position attackPosition = m_Defender->AI_Attack();
			HitResult hitResult = m_Attacker->HitCheck(attackPosition);
			m_Defender->ReceiveHitResult(attackPosition, hitResult);
			
			m_Zido_Attacker->ZidoMarkByGM(attackPosition);
			m_Turn = ATTACKER;
			++m_TurnCount;
			break;

			}
				
		}
		//화면에 게임메니저가 각자가 제출한 것을 표시
		//system("cls");
		//m_Zido_Attacker->PrintZido( MY_ZIDO_X, MY_ZIDO_Y );
		//m_Zido_Defender->PrintZido(ENEMY_ZIDO_X, ENEMY_ZIDO_Y );

		//game check
		m_Gamestatus = CheckGameOVer();

	} 
	TotalCount += m_TurnCount / 2;

}

GameStatus GameManager::CheckGameOVer()
{
	//배 모두격추
	if (m_Attacker->IsAllSunK() || m_Defender->IsAllSunK()||m_Gamestatus==GAMEOVER)
	{
		return GAMEOVER;
	}
	
	//to do : 플레이어가 중간에 나가는 경우도 추가
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
	//to do : 승리자 패배자에 따른 엔딩화면
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

void GameManager::Networking()
{
	Network network;
	PacketType type;
	ErrorType error;

	srand((unsigned int)time(NULL));

	/*
	** 네트워크 초기화
	*/
	try
	{
		Network::Initialize();
	}
	catch (Network::Exception)
	{
		puts("초기화 도중 문제가 발생했습니다.");
		return;
	}

	/*
	** 서버에 연결
	서버의 IP와 포트는 당일날 공지된다.
	*/
	const char* ip = "10.73.42.117";
	const unsigned short port = 9001;

	try
	{
		network.Connect(ip, port);
	}
	catch (Network::Exception ex)
	{
		switch (ex)
		{
		case Network::NETWORK_ERROR:
			puts("서버와 연결에 실패했습니다.");
			break;
		case Network::PARAMETER_ERROR:
			puts("함수의 인수가 잘못되었습니다.");
			break;
		}
		return;
	}
	puts("접속 성공!");

	try	// 예외 처리를 위해 try문으로 모두 감싼다.
	{
		/*
		** 이름&학번 전송
		최대 길이는 MAX_NAME_LEN-1 == 15글자.
		성공시 ET_OK가 리턴된다.
		이미 있는 이름을 쓰면 ET_DUPLICATED_NAME이 온다.
		*/
		const wchar_t name[MAX_NAME_LEN] = L"버틸수없다";
		const int studentID = 141044;

		error = network.SubmitName(name, studentID);
		if (error == ET_DUPLICATED_NAME)
		{
			puts("이미 존재하는 이름입니다.");
			return;
		}

		/*
		** 게임 시작 대기
		게임이 시작되면 상대방의 정보가 들어온다.
		Network::GameStartData 구조체로 상대방 정보를 가져온다.
		*/
		Network::GameStartData gameStartData;
		puts("게임 시작 대기중");
		network.WaitForStart(&gameStartData);
		wprintf_s(L"매칭되었습니다. 상대방 이름: %s, 학번: %d\n", gameStartData.oppositionName, gameStartData.oppositionStudentID);

		/*
		** 게임 시작
		맵 제출부터 게임 종료까지 n회 반복한다.
		하나의 게임이 끝나고 다음 게임을 시작해야 한다면 PKT_SC_NEXT_GAME 패킷이
		모든 게임이 끝나면 PKT_SC_ALL_OVER 패킷이 들어온다.
		*/
		bool allOver = false;
		while (!allOver)
		{
			SetGame();
			
			
			/*
			** 맵 제출
			자신이 배치한 맵 데이터를 서버로 전송한다.
			맵 데이터를 만드는 방법에는 두 가지가 있다.
			하나는 직접 MAP_WIDHT * MAP_HEIGHT 크기의 맵을 만드는 것이고,
			하나는 ShipData 구조체를 이용해서 만드는 것이다.
			*/
			char mapData[MAP_SIZE];

			//TransferMyMapData(mapData, m_Attacker);

			memset(mapData, MI_EMPTY, sizeof(mapData));
			int shiptype = 1;
			for (auto ship : *m_Attacker->GetShipList())
			{
				for (int i = 0; i < ship->GetShipType(); ++i){
					auto position = ship->GetShipPos(i);
					mapData[position.y*MAP_WIDTH + position.x] = shiptype;

				}
				shiptype++; //하드코딩
			}

			while (true)
			{
				
				error = network.SubmitMap(mapData);
				if (error == ET_INVALID_MAP)
					puts("유효하지 않은 맵 데이터입니다.");
				else
					break;
			}

			/*
			** 게임 루프
			내 차례라면 공격 위치를 전송한다.
			차례가 끝나면 공격자와 공격 위치, 공격 결과를 받는다.
			한 게임이 끝나면 PKT_SC_GAME_OVER 패킷이 들어온다.
			*/
			bool gameOver = false;
			while (!gameOver)
			{
				error = network.GetPacketType(&type);

				switch (type)
				{
					// 에러가 발생하는 경우(상대방의 접속 종료)
				case PKT_SC_ERROR:
					if (error == ET_OPPOSITION_DISCONNECTED)
						puts("상대방의 접속이 끊어졌습니다.");
					else
						puts("알 수 없는 에러입니다.");
					return;

					// 내 차례
				case PKT_SC_MY_TURN:
				{
									   /*
									   ** 공격 위치 전송
									   x, y는 0~7 사이의 정수이다.
									   */
									   while (true)
									   {
										  // Coord pos = MakeAttackPos();
										   Position attackpos = m_Attacker->RandomAttack();

										   error = network.SubmitAttack({ attackpos.x, attackpos.y });
										   if (error == ET_INVALID_ATTACK)
											   puts("유효하지 않은 공격 위치입니다.");
										   else
											   break;
									   }
									   break;
				}

					// 공격 결과
				case PKT_SC_ATTACK_RESULT:
				{
											 Network::AttackResultData attackResult = network.GetAttackResult();

											 Position attackpos;
											 attackpos.x = attackResult.pos.mX;
											 attackpos.y = attackResult.pos.mY;

											 HitResult hitResult = TranslateHitResult(attackResult.attackResult);


											 if (attackResult.isMine){
												// puts("공격 결과:");
												 m_Attacker->ReceiveHitResult(attackpos, hitResult);
											 }
											 else
											 {
												 puts("피격 결과:");
												 //HandleOpositionAttackResult(attackResult.attackResult, attackResult.pos.mX, attackResult.pos.mY);
												 m_Zido_Attacker->ZidoMarkByGM(attackpos);
											 }
											 printf_s("X: %d, Y: %d, RESULT: %s\n", attackResult.pos.mX, attackResult.pos.mY, ATTACK_RESULT_STR[attackResult.attackResult]);
											 break;
				}

					// 게임 종료
				case PKT_SC_GAME_OVER:
				{
										 Network::GameResultData gameResult = network.GetGameResult();
										 if (gameResult.isWinner)
											 puts("승리!!!");
										 else
											 puts("패배...");
										 printf_s("턴 수: %d\n", gameResult.turns);
										 gameOver = true;
										 break;
				}

				default:
					throw Network::UNEXPECTED_PACKET;
					break;
				}
			}

			/*
			** 종료후 처리
			*/
			network.GetPacketType(&type);

			if (type == PKT_SC_NEXT_GAME)
			{
				puts("다음 게임을 준비해주세요.");
			}
			else if (type == PKT_SC_ALL_OVER)
			{
				Network::FinalResultData finalResult = network.GetFinalResult();
				puts("모두 종료");
				printf_s("승리 횟수: %d, 평균 턴 수: %.1f", finalResult.winCount, finalResult.avgTurns);

				allOver = true;
			}
			else
				throw Network::UNEXPECTED_PACKET;
		}
	}
	catch (Network::Exception ex)
	{
		switch (ex)
		{
		case Network::NETWORK_ERROR:
			puts("네트워크에 문제가 발생했습니다.");
			break;
		case Network::SERVER_CLOSED:
			puts("서버와의 연결이 끊어졌습니다.");
			break;
		case Network::PARAMETER_ERROR:
			puts("함수의 인수가 잘못되었습니다.");
			break;
		case Network::UNEXPECTED_PACKET:
			puts("서버에서 잘못된 정보가 전송되었습니다.");
			break;
		default:
			break;
		}
	}


	/*
	** 연결 종료
	참고로 소멸시에도 자동으로 Disconnect를 호출한다.
	*/
	network.Disconnect();

	_getch();
}


HitResult GameManager::TranslateHitResult(short info)
{
	switch (info)
	{
	case AR_NONE:
		return RES_NONE;
	case AR_MISS:
		return MISS;
	case AR_HIT:
		return HIT;
	case AR_DESTROY_AIRCRAFT:
		return DESTROY_AIRCRAFT;
	case AR_DESTROY_BATTLESHIP:
		return DESTROY_BATTLESHIP;
	case AR_DESTROY_CRUISER:
		return DESTROY_CRUISER;
	case AR_DESTROY_DESTROYER:
		return DESTROY_DESTROYER;
	default:
		return RES_NONE;
	}

}

// 직접 맵 데이터를 생성하는 방법
void MakeMapData(char* const mapData)
{
	ZeroMemory(mapData, MAP_SIZE);

	int size, sx, sy, dir, listIdx = 0;
	bool placeable;

	// 배 랜덤배치로 지도를 직접 만드는 방식
	for (int type = MD_NONE + 1; type < MD_END; ++type)
	{
		while (true)
		{
			size = ShipData::SHIP_LEN[type];
			placeable = true;
			dir = rand() % 2;
			if (dir == 0) // hori
			{
				sx = rand() % (MAP_WIDTH - size);
				sy = rand() % MAP_HEIGHT;
			}
			else // vert
			{
				sx = rand() % MAP_WIDTH;
				sy = rand() % (MAP_HEIGHT - size);
			}

			for (int i = 0; i < size && placeable; ++i)
			{
				if (dir == 0 && mapData[sx + i + sy * MAP_WIDTH])
					placeable = false;
				else if (dir == 1 && mapData[sx + (sy + i) * MAP_WIDTH])
					placeable = false;
			}

			if (placeable)
				break;
		}

		for (int i = 0; i < size && placeable; ++i)
		{
			int x, y;
			if (dir == 0) { x = sx + i; y = sy; }
			else  { x = sx; y = sy + i; }
			mapData[x + y * MAP_WIDTH] = type;
		}
	}
}


// ShipData 구조체를 사용해서 맵 데이터 생성하는 방법
void MakeMapData2(char* const mapData)
{
	ShipData shipData;

	char map[MAP_SIZE] = { 0, };

	int size, sx, sy, dir, listIdx = 0;
	bool placeable;
	Coord posArr[MAX_SHIP_LEN];	// ShipData에 넣을 배의 위치 배열

	for (int type = MD_NONE + 1; type < MD_END; ++type)
	{
		while (true)
		{
			size = ShipData::SHIP_LEN[type];
			placeable = true;
			dir = rand() % 2;
			if (dir == 0) // hori
			{
				sx = rand() % (MAP_WIDTH - size);
				sy = rand() % MAP_HEIGHT;
			}
			else // vert
			{
				sx = rand() % MAP_WIDTH;
				sy = rand() % (MAP_HEIGHT - size);
			}

			for (int i = 0; i < size && placeable; ++i)
			{
				if (dir == 0 && map[sx + i + sy * MAP_WIDTH])
					placeable = false;
				else if (dir == 1 && map[sx + (sy + i) * MAP_WIDTH])
					placeable = false;
			}

			if (placeable)
				break;
		}

		// 1.2 배의 좌표 배열을 가져와서...
		 Coord* shipPosArr = shipData.GetShipCoordArray((ShipType)type);

		for (int i = 0; i < size && placeable; ++i)
		{
			int x, y;
			Coord coord;
			if (dir == 0) { x = sx + i; y = sy; }
			else  { x = sx; y = sy + i; }
			map[x + y * MAP_WIDTH] = type;

			coord = Coord(x, y);
			// 1. 배의 좌표를 하나씩 넣는 방법
			// 1.1. 함수 사용
			shipData.SetShipCoord((ShipType)type, i, coord);
			// 1.2. 배열을 가져와서 넣기
			// shipPosArr[i] = coord;

			// 2. Coord 배열을 만들어서...
			// posArr[i] = coord;
		}

		// 2. 배의 좌표를 배열로 한 번에 넣는 방법
		// shipData.SetShip((ShipType)type, posArr);

		// 3. 배의 시작지점과 방향만 넣는 방법
		// shipData.SetShip((ShipType)type, Coord(sx, sy), dir==0 ? DIR_HORIZONTAL:DIR_VERTICAL);
	}

	// 배의 배치를 맵 데이터로 변환
	shipData.ToMapData(mapData);
}
