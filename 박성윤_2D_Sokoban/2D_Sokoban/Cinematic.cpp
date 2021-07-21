#include "Cinematic.h"

#include <stdio.h>
#include <windows.h>
#include "sokoban.h"
#include "GameApp.h"
#include "../DRD2DEngine/DRD2DEngine.h"



void Cinematic::Initialize(DRD2DEngine* pEngine)
{
	m_pEngine = pEngine;
}

void Cinematic::SetCharacterMoveNum2(int* pMove)
{

	m_pCharNumMove = pMove;
}

// ���ڹ� ���� Ÿ��Ʋ ȭ��
void Cinematic::MainTitleDraw()
{
	m_pEngine->DrawText("=========================================\n");
	m_pEngine->DrawText("         ���ڹݽ��ڹ� �����Դϴ�           \n");
	m_pEngine->DrawText("                                         \n");
	m_pEngine->DrawText("                  ��                     \n");
	m_pEngine->DrawText("                  ��                     \n");
	m_pEngine->DrawText("                  ��                     \n");
	m_pEngine->DrawText("                               by ����   \n");
	m_pEngine->DrawText("=========================================\n");
	m_pEngine->DrawText("       (1) �����ϱ�      (2) ������		 \n");
	m_pEngine->DrawText("=========================================\n");
}

//Ÿ��Ʋ ȭ�� �޴� ����
bool Cinematic::MainWork()
{
	bool isValue = false;
	int MenuNum = 0;

	scanf_s("%d", &MenuNum);
	getchar();

	switch (MenuNum)
	{
		case 1:
			PlaySound(L"menuSelectSound_beep.wav", NULL, SND_ASYNC);
			printf(" ������ �����մϴ�.\n");
			printf("      STAGE 1     \n");
			Sleep(500);
			isValue = false;
			break;

		case 2:
			PlaySound(L"menuSelectSound_beep.wav", NULL, SND_ASYNC);
			printf("������ �����ϴ�.\n");
			isValue = true;
			break;
	}

	return isValue;
}

// ���ӿ���ȭ��
void Cinematic::GameEndTitle()
{
	printf("=========================================\n");
	printf("         ���ڹݽ��ڹ� ���� ��~~~~          \n");
	printf("                                         \n");
	printf("                  ��                     \n");
	printf("                  ��                     \n");
	printf("                  ��                     \n");
	printf("                               by ����   \n");
	printf("=========================================\n");
	printf("  (1) �ٽ��ϱ�  (2) �����ܰ�  (3) ������	 \n");
	printf("=========================================\n");
}

// ���ӿ����޴� ����
bool Cinematic::EndMain(int* CharPosX, int* CharPosY)
{
	bool isValue = false;
	int MenuNum = 0;

	scanf_s("%d", &MenuNum);

	switch (MenuNum)
	{
		case 1:
			PlaySound(L"menuSelectSound_beep.wav", NULL, SND_ASYNC);
			printf(" ������ �ٽ� �����մϴ�.\n");
			printf("      STAGE 1     \n");
			Sleep(300);
			//system("cls");

			// �������� �� �ٽ� ����� �׷��ֱ�
			reInitMap();

			// ĳ���� ��ġ �ʱ�ȭ �����ֱ�
			ResetCharPos(CharPosX, CharPosY);
			// UI ĳ���� ������ Ƚ�� �ʱ�ȭ
			ResetMoveNum(m_pCharNumMove);
			break;

		case 2:
			PlaySound(L"menuSelectSound_beep.wav", NULL, SND_ASYNC);
			// ���� �ܰ� �����Ƿ� �׳� ������
			isValue = true;
			break;
		case 3:
			PlaySound(L"menuSelectSound_beep.wav", NULL, SND_ASYNC);
			printf("������ �����ϴ�.\n");
			isValue = true;
			break;
	}

	return isValue;
}
