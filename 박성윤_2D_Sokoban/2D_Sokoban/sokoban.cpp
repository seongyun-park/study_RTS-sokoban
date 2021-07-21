#include "sokoban.h"
#include <windows.h>
#include "ConsoleLib.h"
#include "GameApp.h"

LHCGEngine* _pCEngine;

//맵 전체 
#define MAP_HEIGHT_ 11
#define MAP_WIDTH_ 19	

//캐릭터 (크기..?)
#define CHARACTER_HEIGHT 1
#define CHARACTER_WIDTH_ 1

// 캐릭터 처음 위치 고정시키기
#define START_CHAR_X 11
#define START_CHAR_Y 8

//캐릭터 위치 초기화
int CharacterX = 11;
int CharacterY = 8;

int* g_CharNumMove;

///게임판 만들기 . 전역변수로
///가로 19, 세로 11
int GameBoard[MAP_HEIGHT_][MAP_WIDTH_] =
{
	0 ,0 ,0 ,0 ,1 ,1 ,1 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
	0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
	0 ,0 ,0 ,0 ,1 ,3 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
	0 ,0 ,1 ,1 ,1 ,0 ,0 ,3 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
	0 ,0 ,1 ,0 ,0 ,3 ,0 ,3 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
	1 ,1 ,1 ,0 ,1 ,0 ,1 ,1 ,0 ,1 ,0 ,0 ,0 ,1 ,1 ,1 ,1 ,1 ,1,
	1 ,0 ,0 ,0 ,1 ,0 ,1 ,1 ,0 ,1 ,1 ,1 ,1 ,1 ,0 ,0 ,4 ,4 ,1,
	1 ,0 ,3 ,0 ,0 ,3 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,4 ,4 ,1,
	1 ,1 ,1 ,1 ,1 ,0 ,1 ,1 ,1 ,0 ,1 ,0 ,1 ,1 ,0 ,0 ,4 ,4 ,1,
	0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1,
	0 ,0 ,0 ,0 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
};

//목적지 초기화
int tempDestination[MAP_HEIGHT_][MAP_WIDTH_] = { 0, };

int tempGameBoard[MAP_HEIGHT_][MAP_WIDTH_] = { 0, };

void SetEngine(LHCGEngine* pEngine)
{
	_pCEngine = pEngine;
}

void SetCharacterMoveNum(int* pMove)
{
	g_CharNumMove = pMove;
}

// 맵 다시 그리기 위해 임시에 원본 맵을 대입
void reDrawMap()
{
	for (int y = 0; y < 11; y++)
	{
		for (int x = 0; x < 19; x++)
		{
			tempGameBoard[y][x] = GameBoard[y][x];
		}
	}
}

// 원본 맵에 임시에 대입한 맵을 다시 대입
void reInitMap()
{
	for (int y = 0; y < 11; y++)
	{
		for (int x = 0; x < 19; x++)
		{
			GameBoard[y][x] = tempGameBoard[y][x];
		}
	}
}

// 캐릭터의 현재 위치를 초기위치로 스왑해주는 함수
void ResetCharPos(int *PosX, int *PosY)
{
	int tempX = START_CHAR_X;
	int tempY = START_CHAR_Y;

	*PosX = tempX;
	*PosY = tempY;
}

// 움직임 횟수 0으로 만들어주는 함수(포인터로 받는다.)
void ResetMoveNum(int *CharNum)
{
	*CharNum = 0;
}

//게임판에서 목적지에 박스가 다 들어가는 지 확인!
void MakeDestination()
{
	for (int y = 0; y < MAP_HEIGHT_; y++)
	{
		for (int x = 0; x < MAP_WIDTH_; x++)
		{
			if (GameBoard[y][x] == 4)
			{
				tempDestination[y][x] = 4;
			}
		}
	}
}

// 키 입력, 그에 따른 이동 값을 만들어준다.
int KeyInput()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		return KEY_LEFTMOVE;
	}

	else if (GetAsyncKeyState(VK_RIGHT))
	{
		return KEY_RIGHTMOVE;
	}

	else if (GetAsyncKeyState(VK_UP))
	{
		return KEY_UPMOVE;
	}

	else if (GetAsyncKeyState(VK_DOWN))
	{
		return KEY_DOWNMOVE;
	}

	// 치트키 키입력 받는 키 F1
	else if (GetAsyncKeyState(VK_F1))
	{
		return CHEAT_KEY;
	}

	return KEY_NONE;
}

/// 그리기
// 게임판을 모두 그린다.
void DrawAll()
{
	for (int y = 0; y < 11; y++)
	{
		for (int x = 0; x < 19; x++)
		{
			// 게임판의 목적지가 목적지와 같고, 게임판이 빈칸이면
			if (tempDestination[y][x] == DESTINATION && GameBoard[y][x] == EMPTY)
			{
				// 게임판에 목적지를 대입
				GameBoard[y][x] = DESTINATION;
			}
			DrawOneBlock(x, y, GameBoard[y][x]);

			// 특정 위치에 블럭을 하나 그린다.
		}
	}
}

// 게임 시 UI 나타내는 함수
void DrawUI()
{
	// 맵 전체를 돌면서 박스가 목적지에 도달 했는지 확인.
	int CompleteBox = 0;

	for (int y = 0; y < 11; y++)
	{
		for (int x = 0; x < 19; x++)
		{
			if (tempDestination[y][x] == DESTINATION && GameBoard[y][x] == BOX)
			{
				// 목적지에 박스 들어 갈 때 마다 박스 ++
				CompleteBox++;
			}
		}
	}

	// 박스 갯수 세는 함수
	_pCEngine->LHLocateCursor(0, 13);
	printf("성공한 박스의 갯수는? : %d\n", CompleteBox);

	// 캐릭터의 움직임 세는 함수
	_pCEngine->LHLocateCursor(0, 12);
	printf(" 캐릭터의 움직인 횟수는? : %d\n", g_CharNumMove);

	// UI 설명 출력
	_pCEngine->LHLocateCursor(0, 15);
	printf(" 이동 키 : ← → ↑ ↓ \n");
}

// 게임이 끝나면(목적지에 박스가 다 들어가면) 게임 완료! 
bool isEnd()
{
	int check = 0;
	for (int y = 0; y < 11; y++)
	{
		for (int x = 0; x < 19; x++)
		{
			//목적지에 박스가 다 들어가면? 완료
			if (tempDestination[y][x] == DESTINATION && GameBoard[y][x] == BOX)
			{
				check++;
			}
			// 특정 위치에 블럭을 하나 그린다.
		}
	}

	// 게임 끝내주는 치트키 만들어줌
	int _keyInput = KeyInput();

	if(_keyInput == CHEAT_KEY)
	{
		check = 6;
	}

	// 아하 6번을 체크하면서 박스 6개가 목적지에 다 올라왔는지!
	if (check == 6)
	{
		return true;
	}
	//아니면 작동 안함
	return false;
}

// 한 개의 블럭을 출력
void DrawOneBlock(int posX, int posY, int type)
{
	switch (type)
	{
	case EMPTY:
	{
		_pCEngine->LHPutAttrCharEx(posX * 2, posY, "  ", BG_WHITE, FG_WHITE);
	}
	break;

	case WALL:
	{
		_pCEngine->LHPutAttrCharEx(posX * 2, posY, "■", BG_BLUE, FG_WHITE);
	}
	break;

	case BOX:
	{
		_pCEngine->LHPutAttrCharEx(posX * 2, posY, "▨", BG_PURPLE, FG_WHITE);
	}
	break;

	case DESTINATION:
	{
		_pCEngine->LHPutAttrCharEx(posX * 2, posY, "◎", BG_GREEN, FG_WHITE);
	}
	break;
	}
}

// 캐릭터의 이동 시 체크 (충돌감지 - 벽 여부, 상자 밀기 등)
int CheckCharacterMove(int nowPosX, int nowPosY, int offsetX, int offsetY)
{
	// 현재 캐릭터가 있는 위치가 유효한가?

	// 이동해야 될 위치가 유효한가?
	int _nextPosX = nowPosX + offsetX;
	int _nextPosY = nowPosY + offsetY;


	/// 1. 이동할 위치가 게임판의 밖이면, 아무 것도 하지 않는다.
	// 게임판 범위 체크 - 밖으로 나가게 되나?
	if (_nextPosX < 0 || 18 < _nextPosX || _nextPosY < 0 || 10 < _nextPosY)
	{
		return false;
	}

	/// 2-p. 이동할 위치에 상자가 있다면, 상자를 민다.
	if (GameBoard[_nextPosY][_nextPosX] == BOX)
	{
		// 박스가 이동할 시 적용되는 것들
		if (CheckCharacterMove(_nextPosX, _nextPosY, offsetX, offsetY) == true)
		{

			// 이동해야 할 박스 위치로 이동시켜 준다.
			GameBoard[_nextPosY + offsetY][_nextPosX + offsetX] = BOX;

			// 원래 박스 위치는 빈칸이 되어야 한다.
			GameBoard[_nextPosY][_nextPosX] = EMPTY;

			return true;
		}

		// 그 외에는 다 못움직임.
		return false;
	}

	/// 3. 이동할 위치가 빈 칸이면, 이동한다.
	if (GameBoard[_nextPosY][_nextPosX] == EMPTY)
	{
		return true;
	}

	/// 5. 이동할 박스의 위치가 목적지라면, 이동 가능하다.
	if (GameBoard[_nextPosY][_nextPosX] == DESTINATION)
	{
		return true;
	}

	/// 이도 저도 아니면 이동하지 못한다.
	return false;
}

// 캐릭터를 맵 위에 새로 그려준다.
void DrawCharacter(int posX, int posY)
{
	_pCEngine->LHPutAttrCharEx(posX * 2, posY, "△", BG_RED, FG_WHITE);
}