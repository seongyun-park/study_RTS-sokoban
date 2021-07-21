#pragma once

/// <summary>
/// 게임 내의 연출, 진행 등을 담당
///
/// 2020.11.23 108 Passion
/// </summary>
class Cinematic
{
public:
	void Initialize(DRD2DEngine* pEngine);
	void SetCharacterMoveNum2(int* pMove);
	void MainTitleDraw();
	bool MainWork();

	void GameEndTitle();

	// 캐릭터의 초기 위치를 파라미터로 받게 만듬
	bool EndMain(int* CharPosX, int* CharPosY);

private:
//public:
	DRD2DEngine* m_pEngine;
	int* m_pCharNumMove;

public:
	int* GetCharNumMove() const { return m_pCharNumMove; }
	//void SetCharNumMove(int* val) { m_pCharNumMove = val; }

};
