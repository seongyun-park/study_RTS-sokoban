#pragma once
class LHCGEngine;

#define EMPTY 0			//빈칸
#define WALL 1			//벽, 방해물(고정, 충돌)

#define CHARACTER 2		//움직일 캐릭터(커서?????)
#define BOX 3			//굴리는 공, 방해물(유동적 움직임)
#define DESTINATION 4	//목적지

//키 입력 정의
#define KEY_LEFTMOVE 101
#define KEY_RIGHTMOVE 102
#define KEY_DOWNMOVE 103
#define KEY_UPMOVE 104
#define KEY_NONE 106
#define CHEAT_KEY 107

void SetEngine(LHCGEngine* pEngine);
//void InitializeCGEngine(LHCGEngine* pCGEngine);

void SetCharacterMoveNum(int* pMove);
// 맵 다시하기 시 초기화 시켜주기
void reDrawMap();
void reInitMap();

// 캐릭터 위치 파라미터로 받아서 초기화 시켜주기
void ResetCharPos(int *PosX, int *PosY);

// UI Char 움직임 횟수 초기화 시켜주기
void ResetMoveNum(int *CharNum);

//목적지 달성 함수(목적지 == 박스)
void MakeDestination();

//키입력함수
int KeyInput();

//맵 그리는 함수
void DrawAll();

// UI 그려주는 함수
void DrawUI();

//게임끝나는 함수
bool isEnd();

void DrawOneBlock(int posX, int posY, int type);

// 캐릭터의 이동 시 체크 (충돌감지 - 벽 여부, 상자 밀기, 등)
int CheckCharacterMove(int nowPosX, int nowPosY, int offsetX, int offsetY);
// 캐릭터를 그린다.
void DrawCharacter(int posX, int posY);
