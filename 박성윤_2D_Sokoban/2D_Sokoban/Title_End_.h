#pragma once
#include "sokoban.h"
#include "../DRD2DEngine/DRD2DEngine.h"

void SetCharacterMoveNum2(int* pMove);
void MainTitleDraw();
bool MainWork();

void GameEndTitle();

// ĳ������ �ʱ� ��ġ�� �Ķ���ͷ� �ް� ����
bool EndMain(int *CharPosX, int *CharPosY);