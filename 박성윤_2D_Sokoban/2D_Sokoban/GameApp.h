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
/// 게임 프로그램의 일반적인 부분을 담당한다.

/// 메인 함수의 대부분을 대체하는 가장 큰 클래스

/// 2020.11.04
/// </summary>

class GameApp
{
public:
	// 생성자
	GameApp();
	~GameApp();

public:
	// 큰 단위의 함수들
	void Initialize(DRD2DEngine* pEngine);
	void Loop();
	// void Finalize();

private:
	// 이 클래스 내부에서만 사용하는 함수들
	void PrintTitleScene();
	void SokobanTiniteStateMachine();

private:
	// 멤버 변수들
		//현재 동작할 FSM의 State
	eGameState g_GameState = eGameState::TitleScene;
	//키입력, 그에 따른 이동 값을 만들어준다.
	//int _keyInput = 0;

	/// 소코반(클래스)에서 사용할 변수들
	int _characterPosX = 11;	// 캐릭터의 좌표
	int _characterPosY = 8;
	int _offsetPosX = 0;		// 캐릭터 이동값. 오프셋. 이동 벡터
	int _offsetPosY = 0;
	int _boxPosX = BOX;
	int _boxPosY = BOX;
	int _keyInput = 0;			// 키 입력

	// 움직임 초깃값
	int g_CharNumMove = 0;
	int g_CharNumMove2 = 0;


public:

	/// 클래스를 만들기 이전 임시 전역
	LHCGEngine* m_pCEngine;

	// 2D 기반의 엔진으로 대체
	DRD2DEngine* m_pEngine;

private:
	/// 타이틀, 엔딩 등을 담당하는 시네매틱 클래스
	Cinematic* m_Cinematic;
};

