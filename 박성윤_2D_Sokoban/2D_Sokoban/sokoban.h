#pragma once
class LHCGEngine;

#define EMPTY 0			//��ĭ
#define WALL 1			//��, ���ع�(����, �浹)

#define CHARACTER 2		//������ ĳ����(Ŀ��?????)
#define BOX 3			//������ ��, ���ع�(������ ������)
#define DESTINATION 4	//������

//Ű �Է� ����
#define KEY_LEFTMOVE 101
#define KEY_RIGHTMOVE 102
#define KEY_DOWNMOVE 103
#define KEY_UPMOVE 104
#define KEY_NONE 106
#define CHEAT_KEY 107

void SetEngine(LHCGEngine* pEngine);
//void InitializeCGEngine(LHCGEngine* pCGEngine);

void SetCharacterMoveNum(int* pMove);
// �� �ٽ��ϱ� �� �ʱ�ȭ �����ֱ�
void reDrawMap();
void reInitMap();

// ĳ���� ��ġ �Ķ���ͷ� �޾Ƽ� �ʱ�ȭ �����ֱ�
void ResetCharPos(int *PosX, int *PosY);

// UI Char ������ Ƚ�� �ʱ�ȭ �����ֱ�
void ResetMoveNum(int *CharNum);

//������ �޼� �Լ�(������ == �ڽ�)
void MakeDestination();

//Ű�Է��Լ�
int KeyInput();

//�� �׸��� �Լ�
void DrawAll();

// UI �׷��ִ� �Լ�
void DrawUI();

//���ӳ����� �Լ�
bool isEnd();

void DrawOneBlock(int posX, int posY, int type);

// ĳ������ �̵� �� üũ (�浹���� - �� ����, ���� �б�, ��)
int CheckCharacterMove(int nowPosX, int nowPosY, int offsetX, int offsetY);
// ĳ���͸� �׸���.
void DrawCharacter(int posX, int posY);
