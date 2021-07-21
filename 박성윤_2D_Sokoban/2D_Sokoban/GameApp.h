#pragma once
#include "sokoban.h"

class DRD2DEngine;
class Cinematic;

//modern C++ enum class
enum class eGameState
{
	TitleScene,
	InGame,
	GameOver,
	Win,
};

/// <summary>
/// ���� ���α׷��� �Ϲ����� �κ��� ����Ѵ�.

/// ���� �Լ��� ��κ��� ��ü�ϴ� ���� ū Ŭ����

/// 2020.11.04
/// </summary>

class GameApp
{
public:
	// ������
	GameApp();
	~GameApp();

public:
	// ū ������ �Լ���
	void Initialize(DRD2DEngine* pEngine);
	void Loop();
	// void Finalize();

private:
	// �� Ŭ���� ���ο����� ����ϴ� �Լ���
	void PrintTitleScene();
	void SokobanTiniteStateMachine();

private:
	// ��� ������
		//���� ������ FSM�� State
	eGameState g_GameState = eGameState::TitleScene;
	//Ű�Է�, �׿� ���� �̵� ���� ������ش�.
	//int _keyInput = 0;

	/// ���ڹ�(Ŭ����)���� ����� ������
	int _characterPosX = 11;	// ĳ������ ��ǥ
	int _characterPosY = 8;
	int _offsetPosX = 0;		// ĳ���� �̵���. ������. �̵� ����
	int _offsetPosY = 0;
	int _boxPosX = BOX;
	int _boxPosY = BOX;
	int _keyInput = 0;			// Ű �Է�

	// ������ �ʱ갪
	int g_CharNumMove = 0;
	int g_CharNumMove2 = 0;


public:

	/// Ŭ������ ����� ���� �ӽ� ����
	LHCGEngine* m_pCEngine;

	// 2D ����� �������� ��ü
	DRD2DEngine* m_pEngine;

private:
	/// Ÿ��Ʋ, ���� ���� ����ϴ� �ó׸�ƽ Ŭ����
	Cinematic* m_Cinematic;
};

