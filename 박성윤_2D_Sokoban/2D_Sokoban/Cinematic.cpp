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

// 소코반 게임 타이틀 화면
void Cinematic::MainTitleDraw()
{
	m_pEngine->DrawText("=========================================\n");
	m_pEngine->DrawText("         쏘코반쏘코반 게임입니당           \n");
	m_pEngine->DrawText("                                         \n");
	m_pEngine->DrawText("                  ☆                     \n");
	m_pEngine->DrawText("                  ☆                     \n");
	m_pEngine->DrawText("                  ☆                     \n");
	m_pEngine->DrawText("                               by 성윤   \n");
	m_pEngine->DrawText("=========================================\n");
	m_pEngine->DrawText("       (1) 시작하기      (2) 나가기		 \n");
	m_pEngine->DrawText("=========================================\n");
}

//타이틀 화면 메뉴 선택
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
			printf(" 게임을 시작합니다.\n");
			printf("      STAGE 1     \n");
			Sleep(500);
			isValue = false;
			break;

		case 2:
			PlaySound(L"menuSelectSound_beep.wav", NULL, SND_ASYNC);
			printf("게임을 나갑니다.\n");
			isValue = true;
			break;
	}

	return isValue;
}

// 게임엔딩화면
void Cinematic::GameEndTitle()
{
	printf("=========================================\n");
	printf("         쏘코반쏘코반 게임 끝~~~~          \n");
	printf("                                         \n");
	printf("                  ☆                     \n");
	printf("                  ☆                     \n");
	printf("                  ☆                     \n");
	printf("                               by 성윤   \n");
	printf("=========================================\n");
	printf("  (1) 다시하기  (2) 다음단계  (3) 나가기	 \n");
	printf("=========================================\n");
}

// 게임엔딩메뉴 선택
bool Cinematic::EndMain(int* CharPosX, int* CharPosY)
{
	bool isValue = false;
	int MenuNum = 0;

	scanf_s("%d", &MenuNum);

	switch (MenuNum)
	{
		case 1:
			PlaySound(L"menuSelectSound_beep.wav", NULL, SND_ASYNC);
			printf(" 게임을 다시 시작합니다.\n");
			printf("      STAGE 1     \n");
			Sleep(300);
			//system("cls");

			// 움직여진 맵 다시 제대로 그려주기
			reInitMap();

			// 캐릭터 위치 초기화 시켜주기
			ResetCharPos(CharPosX, CharPosY);
			// UI 캐릭터 움직임 횟수 초기화
			ResetMoveNum(m_pCharNumMove);
			break;

		case 2:
			PlaySound(L"menuSelectSound_beep.wav", NULL, SND_ASYNC);
			// 다음 단계 없으므로 그냥 끝내기
			isValue = true;
			break;
		case 3:
			PlaySound(L"menuSelectSound_beep.wav", NULL, SND_ASYNC);
			printf("게임을 나갑니다.\n");
			isValue = true;
			break;
	}

	return isValue;
}
