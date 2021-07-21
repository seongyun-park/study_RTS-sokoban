#include "GameApp.h"
#include "sokoban.h"
#include "Title_End_.h"
#include <windows.h>
#include "Cinematic.h"
#include "../DRD2DEngine/DRD2DEngine.h"

extern int* g_pCharNumMove2;

GameApp::GameApp()
	: m_Cinematic(NULL)
{
	m_pEngine = NULL;
}

GameApp::~GameApp()
{
}

void GameApp::Initialize(DRD2DEngine* pEngine)
{
	// 외부에서 생성한 엔진의 포인터를 받아서 가지고 있는다
	m_pEngine = pEngine;

	m_Cinematic = new Cinematic();

	_characterPosX = 11;	// 캐릭터의 좌표
	_characterPosY = 8;
	_offsetPosX = 0;		// 캐릭터 이동값. 오프셋. 이동 벡터
	_offsetPosY = 0;
	_boxPosX = BOX;
	_boxPosY = BOX;
	_keyInput = 0;			// 키 입력

	g_CharNumMove = 0;

	int d = *(m_Cinematic->GetCharNumMove());
	//m_Cinematic->SetCharNumMove(&d);
	//*(m_Cinematic->m_pCharNumMove) = 3;


	SetCharacterMoveNum(&g_CharNumMove);
	///SetCharacterMoveNum2(&g_CharNumMove);
	m_Cinematic->SetCharacterMoveNum2(&g_CharNumMove);

	//게임 상태
	g_GameState = eGameState::TitleScene;

	/// 시스템 초기화

	reDrawMap();

	///콘솔 창의 타이틀 변경
	///SetConsoleTitle("쏘코반!");

	/// 스크린 사이즈 변경
	//set_screen_size(60, 30);


	/// 소코반 시작

	MakeDestination();

	PlaySound(L"SokobanGameBGM.wav", NULL, SND_ASYNC | SND_LOOP);
}

void GameApp::Loop()
{
	/// 여기서부터 게임루프 시작
	while (true)
	{
		SokobanTiniteStateMachine();
	}
}

void GameApp::PrintTitleScene()
{
	m_pEngine->DrawText(0,0, " _________       __        ___.                   ._. ._. ._. ._. ._. \n");
	m_pEngine->DrawText(0,14, "/   _____/ ____ |  | ______\_ |__ _____    ____   | | | | | | | | | | \n");
	m_pEngine->DrawText(0,28, "\_____  \ /  _ \|  |/ /  _ \| __ \\__  \  /    \  | | | | | | | | | | \n");
	m_pEngine->DrawText(0,42, "/        (  <_> )    <  <_> ) \_\ \/ __ \|   |  \  \|  \|  \|  \|  \| \n");
	m_pEngine->DrawText(0,56, "/_______ /\____/|__|_ \____/|___  (____  /___|  /  __  __  __  __  __ \n");
	m_pEngine->DrawText(0,70, "       \/            \/         \/     \/     \/   \/  \/  \/  \/  \/ \n");

}

void GameApp::SokobanTiniteStateMachine()
{
	switch (g_GameState)
	{
	case eGameState::TitleScene:
	{
		PlaySound(L"SokobanGameBGM.wav", NULL, SND_ASYNC | SND_LOOP);

		// 화면을 지운다 -> 함수로 만든다
		//system("cls");

		PrintTitleScene();

		// 아무 키나 누르면, 게임을 시작한다 (=인게임 씬으로 간다)
		_keyInput = KeyInput();
		if (_keyInput != KEY_NONE)
		{
			// 화면을 지운다 -> 함수로 만든다
			//system("cls");
			g_GameState = eGameState::InGame;
		}
	}
	break;

	case eGameState::InGame:
	{
		// 인게임 시 UI 적용
		DrawUI();

		/// 입력
		_keyInput = KeyInput();

		// 깜빡임을 막기 위해서, 키 입력이 없을 때는 아래를 진행하지 않는다.
		/// if (_keyInput == KEY_NONE) continue;

		switch (_keyInput)
		{
		case KEY_LEFTMOVE: {_offsetPosX = -1; } break;
		case KEY_RIGHTMOVE: {_offsetPosX = 1; } break;
		case KEY_DOWNMOVE: {_offsetPosY = 1; } break;
		case KEY_UPMOVE: {_offsetPosY = -1; } break;
		case CHEAT_KEY: isEnd(); break;

		default:
		{
			_offsetPosX = 0;
			_offsetPosY = 0;
		}
		break;
		}

		/// 연산
		// 캐릭터의 이동을 처리
		if (CheckCharacterMove(_characterPosX, _characterPosY, _offsetPosX, _offsetPosY) == true)
		{
			// 이동 가능 - 이동시키자.
			_characterPosX += _offsetPosX;

			// UI에 이동횟수 적용. 이동 할 때 offsetPosX 가 핵심 키, 가로 키입력 받고 ++
			if (_offsetPosX == 0)
			{

			}
			else if (_offsetPosX++)
			{
				g_CharNumMove++;
			}

			// UI에 이동횟수 적용. 이동 할 때 offsetPosX 가 핵심 키, 세로 키입력 받고 ++
			_characterPosY += _offsetPosY;

			if (_offsetPosY == 0)
			{

			}
			else if (_offsetPosY++)
			{
				g_CharNumMove++;
			}
		}
		else
		{
			// 이동 불가 - 아무 것도 하지 않는다.
		}

		// 프레임 제어
		Sleep(100);

		/// 그리기
		// 게임판을 모두 그린다.
		DrawAll();

		// (게임 판 위에) 현재 캐릭터를 그린다.
		DrawCharacter(_characterPosX, _characterPosY);

		// 게임이 끝나면, 빠져나오게 된다.
		if (isEnd())
		{
			// 엔딩 타이틀 보여주기
			///GameEndTitle();
			m_Cinematic->GameEndTitle();

			/// 새로하기 메뉴 1번 다시하기 작동 오류(초기화 안됨)
			if (EndMain(&_characterPosX, &_characterPosY) == true)
			{
				// 화면을 지운다 -> 함수로 만든다
				//system("cls");
			}
		}
	}
	//return 0;

	break;

	case eGameState::GameOver:
	{

	}
	break;

	case eGameState::Win:
	{

	}
	break;
	}
}
