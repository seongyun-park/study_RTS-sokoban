#pragma once
#include "sokoban.h"
#include "../DRD2DEngine/DRD2DEngine.h"

void SetCharacterMoveNum2(int* pMove);
void MainTitleDraw();
bool MainWork();

void GameEndTitle();

// 캐릭터의 초기 위치를 파라미터로 받게 만듬
bool EndMain(int *CharPosX, int *CharPosY);