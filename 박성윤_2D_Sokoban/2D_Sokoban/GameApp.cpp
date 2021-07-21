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
	// �ܺο��� ������ ������ �����͸� �޾Ƽ� ������ �ִ´�
	m_pEngine = pEngine;

	m_Cinematic = new Cinematic();

	_characterPosX = 11;	// ĳ������ ��ǥ
	_characterPosY = 8;
	_offsetPosX = 0;		// ĳ���� �̵���. ������. �̵� ����
	_offsetPosY = 0;
	_boxPosX = BOX;
	_boxPosY = BOX;
	_keyInput = 0;			// Ű �Է�

	g_CharNumMove = 0;

	int d = *(m_Cinematic->GetCharNumMove());
	//m_Cinematic->SetCharNumMove(&d);
	//*(m_Cinematic->m_pCharNumMove) = 3;


	SetCharacterMoveNum(&g_CharNumMove);
	///SetCharacterMoveNum2(&g_CharNumMove);
	m_Cinematic->SetCharacterMoveNum2(&g_CharNumMove);

	//���� ����
	g_GameState = eGameState::TitleScene;

	/// �ý��� �ʱ�ȭ

	reDrawMap();

	///�ܼ� â�� Ÿ��Ʋ ����
	///SetConsoleTitle("���ڹ�!");

	/// ��ũ�� ������ ����
	//set_screen_size(60, 30);


	/// ���ڹ� ����

	MakeDestination();

	PlaySound(L"SokobanGameBGM.wav", NULL, SND_ASYNC | SND_LOOP);
}

void GameApp::Loop()
{
	/// ���⼭���� ���ӷ��� ����
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

		// ȭ���� ����� -> �Լ��� �����
		//system("cls");

		PrintTitleScene();

		// �ƹ� Ű�� ������, ������ �����Ѵ� (=�ΰ��� ������ ����)
		_keyInput = KeyInput();
		if (_keyInput != KEY_NONE)
		{
			// ȭ���� ����� -> �Լ��� �����
			//system("cls");
			g_GameState = eGameState::InGame;
		}
	}
	break;

	case eGameState::InGame:
	{
		// �ΰ��� �� UI ����
		DrawUI();

		/// �Է�
		_keyInput = KeyInput();

		// �������� ���� ���ؼ�, Ű �Է��� ���� ���� �Ʒ��� �������� �ʴ´�.
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

		/// ����
		// ĳ������ �̵��� ó��
		if (CheckCharacterMove(_characterPosX, _characterPosY, _offsetPosX, _offsetPosY) == true)
		{
			// �̵� ���� - �̵���Ű��.
			_characterPosX += _offsetPosX;

			// UI�� �̵�Ƚ�� ����. �̵� �� �� offsetPosX �� �ٽ� Ű, ���� Ű�Է� �ް� ++
			if (_offsetPosX == 0)
			{

			}
			else if (_offsetPosX++)
			{
				g_CharNumMove++;
			}

			// UI�� �̵�Ƚ�� ����. �̵� �� �� offsetPosX �� �ٽ� Ű, ���� Ű�Է� �ް� ++
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
			// �̵� �Ұ� - �ƹ� �͵� ���� �ʴ´�.
		}

		// ������ ����
		Sleep(100);

		/// �׸���
		// �������� ��� �׸���.
		DrawAll();

		// (���� �� ����) ���� ĳ���͸� �׸���.
		DrawCharacter(_characterPosX, _characterPosY);

		// ������ ������, ���������� �ȴ�.
		if (isEnd())
		{
			// ���� Ÿ��Ʋ �����ֱ�
			///GameEndTitle();
			m_Cinematic->GameEndTitle();

			/// �����ϱ� �޴� 1�� �ٽ��ϱ� �۵� ����(�ʱ�ȭ �ȵ�)
			if (EndMain(&_characterPosX, &_characterPosY) == true)
			{
				// ȭ���� ����� -> �Լ��� �����
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
