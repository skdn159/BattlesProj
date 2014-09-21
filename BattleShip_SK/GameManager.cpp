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
			printf_s("%d��° ��\n ",i);

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
	
	//�÷��̾� ����
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
		//ȭ�鿡 ���Ӹ޴����� ���ڰ� ������ ���� ǥ��
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
	//�� ��ΰ���
	if (m_Attacker->IsAllSunK() || m_Defender->IsAllSunK()||m_Gamestatus==GAMEOVER)
	{
		return GAMEOVER;
	}
	
	//to do : �÷��̾ �߰��� ������ ��쵵 �߰�
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
	//to do : �¸��� �й��ڿ� ���� ����ȭ��
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
	** ��Ʈ��ũ �ʱ�ȭ
	*/
	try
	{
		Network::Initialize();
	}
	catch (Network::Exception)
	{
		puts("�ʱ�ȭ ���� ������ �߻��߽��ϴ�.");
		return;
	}

	/*
	** ������ ����
	������ IP�� ��Ʈ�� ���ϳ� �����ȴ�.
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
			puts("������ ���ῡ �����߽��ϴ�.");
			break;
		case Network::PARAMETER_ERROR:
			puts("�Լ��� �μ��� �߸��Ǿ����ϴ�.");
			break;
		}
		return;
	}
	puts("���� ����!");

	try	// ���� ó���� ���� try������ ��� ���Ѵ�.
	{
		/*
		** �̸�&�й� ����
		�ִ� ���̴� MAX_NAME_LEN-1 == 15����.
		������ ET_OK�� ���ϵȴ�.
		�̹� �ִ� �̸��� ���� ET_DUPLICATED_NAME�� �´�.
		*/
		const wchar_t name[MAX_NAME_LEN] = L"��ƿ������";
		const int studentID = 141044;

		error = network.SubmitName(name, studentID);
		if (error == ET_DUPLICATED_NAME)
		{
			puts("�̹� �����ϴ� �̸��Դϴ�.");
			return;
		}

		/*
		** ���� ���� ���
		������ ���۵Ǹ� ������ ������ ���´�.
		Network::GameStartData ����ü�� ���� ������ �����´�.
		*/
		Network::GameStartData gameStartData;
		puts("���� ���� �����");
		network.WaitForStart(&gameStartData);
		wprintf_s(L"��Ī�Ǿ����ϴ�. ���� �̸�: %s, �й�: %d\n", gameStartData.oppositionName, gameStartData.oppositionStudentID);

		/*
		** ���� ����
		�� ������� ���� ������� nȸ �ݺ��Ѵ�.
		�ϳ��� ������ ������ ���� ������ �����ؾ� �Ѵٸ� PKT_SC_NEXT_GAME ��Ŷ��
		��� ������ ������ PKT_SC_ALL_OVER ��Ŷ�� ���´�.
		*/
		bool allOver = false;
		while (!allOver)
		{
			SetGame();
			
			
			/*
			** �� ����
			�ڽ��� ��ġ�� �� �����͸� ������ �����Ѵ�.
			�� �����͸� ����� ������� �� ������ �ִ�.
			�ϳ��� ���� MAP_WIDHT * MAP_HEIGHT ũ���� ���� ����� ���̰�,
			�ϳ��� ShipData ����ü�� �̿��ؼ� ����� ���̴�.
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
				shiptype++; //�ϵ��ڵ�
			}

			while (true)
			{
				
				error = network.SubmitMap(mapData);
				if (error == ET_INVALID_MAP)
					puts("��ȿ���� ���� �� �������Դϴ�.");
				else
					break;
			}

			/*
			** ���� ����
			�� ���ʶ�� ���� ��ġ�� �����Ѵ�.
			���ʰ� ������ �����ڿ� ���� ��ġ, ���� ����� �޴´�.
			�� ������ ������ PKT_SC_GAME_OVER ��Ŷ�� ���´�.
			*/
			bool gameOver = false;
			while (!gameOver)
			{
				error = network.GetPacketType(&type);

				switch (type)
				{
					// ������ �߻��ϴ� ���(������ ���� ����)
				case PKT_SC_ERROR:
					if (error == ET_OPPOSITION_DISCONNECTED)
						puts("������ ������ ���������ϴ�.");
					else
						puts("�� �� ���� �����Դϴ�.");
					return;

					// �� ����
				case PKT_SC_MY_TURN:
				{
									   /*
									   ** ���� ��ġ ����
									   x, y�� 0~7 ������ �����̴�.
									   */
									   while (true)
									   {
										  // Coord pos = MakeAttackPos();
										   Position attackpos = m_Attacker->RandomAttack();

										   error = network.SubmitAttack({ attackpos.x, attackpos.y });
										   if (error == ET_INVALID_ATTACK)
											   puts("��ȿ���� ���� ���� ��ġ�Դϴ�.");
										   else
											   break;
									   }
									   break;
				}

					// ���� ���
				case PKT_SC_ATTACK_RESULT:
				{
											 Network::AttackResultData attackResult = network.GetAttackResult();

											 Position attackpos;
											 attackpos.x = attackResult.pos.mX;
											 attackpos.y = attackResult.pos.mY;

											 HitResult hitResult = TranslateHitResult(attackResult.attackResult);


											 if (attackResult.isMine){
												// puts("���� ���:");
												 m_Attacker->ReceiveHitResult(attackpos, hitResult);
											 }
											 else
											 {
												 puts("�ǰ� ���:");
												 //HandleOpositionAttackResult(attackResult.attackResult, attackResult.pos.mX, attackResult.pos.mY);
												 m_Zido_Attacker->ZidoMarkByGM(attackpos);
											 }
											 printf_s("X: %d, Y: %d, RESULT: %s\n", attackResult.pos.mX, attackResult.pos.mY, ATTACK_RESULT_STR[attackResult.attackResult]);
											 break;
				}

					// ���� ����
				case PKT_SC_GAME_OVER:
				{
										 Network::GameResultData gameResult = network.GetGameResult();
										 if (gameResult.isWinner)
											 puts("�¸�!!!");
										 else
											 puts("�й�...");
										 printf_s("�� ��: %d\n", gameResult.turns);
										 gameOver = true;
										 break;
				}

				default:
					throw Network::UNEXPECTED_PACKET;
					break;
				}
			}

			/*
			** ������ ó��
			*/
			network.GetPacketType(&type);

			if (type == PKT_SC_NEXT_GAME)
			{
				puts("���� ������ �غ����ּ���.");
			}
			else if (type == PKT_SC_ALL_OVER)
			{
				Network::FinalResultData finalResult = network.GetFinalResult();
				puts("��� ����");
				printf_s("�¸� Ƚ��: %d, ��� �� ��: %.1f", finalResult.winCount, finalResult.avgTurns);

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
			puts("��Ʈ��ũ�� ������ �߻��߽��ϴ�.");
			break;
		case Network::SERVER_CLOSED:
			puts("�������� ������ ���������ϴ�.");
			break;
		case Network::PARAMETER_ERROR:
			puts("�Լ��� �μ��� �߸��Ǿ����ϴ�.");
			break;
		case Network::UNEXPECTED_PACKET:
			puts("�������� �߸��� ������ ���۵Ǿ����ϴ�.");
			break;
		default:
			break;
		}
	}


	/*
	** ���� ����
	����� �Ҹ�ÿ��� �ڵ����� Disconnect�� ȣ���Ѵ�.
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

// ���� �� �����͸� �����ϴ� ���
void MakeMapData(char* const mapData)
{
	ZeroMemory(mapData, MAP_SIZE);

	int size, sx, sy, dir, listIdx = 0;
	bool placeable;

	// �� ������ġ�� ������ ���� ����� ���
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


// ShipData ����ü�� ����ؼ� �� ������ �����ϴ� ���
void MakeMapData2(char* const mapData)
{
	ShipData shipData;

	char map[MAP_SIZE] = { 0, };

	int size, sx, sy, dir, listIdx = 0;
	bool placeable;
	Coord posArr[MAX_SHIP_LEN];	// ShipData�� ���� ���� ��ġ �迭

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

		// 1.2 ���� ��ǥ �迭�� �����ͼ�...
		 Coord* shipPosArr = shipData.GetShipCoordArray((ShipType)type);

		for (int i = 0; i < size && placeable; ++i)
		{
			int x, y;
			Coord coord;
			if (dir == 0) { x = sx + i; y = sy; }
			else  { x = sx; y = sy + i; }
			map[x + y * MAP_WIDTH] = type;

			coord = Coord(x, y);
			// 1. ���� ��ǥ�� �ϳ��� �ִ� ���
			// 1.1. �Լ� ���
			shipData.SetShipCoord((ShipType)type, i, coord);
			// 1.2. �迭�� �����ͼ� �ֱ�
			// shipPosArr[i] = coord;

			// 2. Coord �迭�� ����...
			// posArr[i] = coord;
		}

		// 2. ���� ��ǥ�� �迭�� �� ���� �ִ� ���
		// shipData.SetShip((ShipType)type, posArr);

		// 3. ���� ���������� ���⸸ �ִ� ���
		// shipData.SetShip((ShipType)type, Coord(sx, sy), dir==0 ? DIR_HORIZONTAL:DIR_VERTICAL);
	}

	// ���� ��ġ�� �� �����ͷ� ��ȯ
	shipData.ToMapData(mapData);
}
