#pragma once

/// <summary>
/// ���� ���� ����, ���� ���� ���
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

	// ĳ������ �ʱ� ��ġ�� �Ķ���ͷ� �ް� ����
	bool EndMain(int* CharPosX, int* CharPosY);

private:
//public:
	DRD2DEngine* m_pEngine;
	int* m_pCharNumMove;

public:
	int* GetCharNumMove() const { return m_pCharNumMove; }
	//void SetCharNumMove(int* val) { m_pCharNumMove = val; }

};
