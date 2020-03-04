#include "stdafx.h"

int Area[BOARD_HEIGHT + 1][BOARD_WIDTH + 1] = { 0, }; //0은 빈 공간, -3은 외벽
int backBufferArea[BOARD_HEIGHT + 1][BOARD_HEIGHT + 1] = { 0, }; //더블버퍼링을 위해서
int kb; //키보드 입력
int Block_Xpos = 5; //블럭의 x좌표
int Block_Ypos = 0; //블럭의 y좌표
int Shadow_Xpos = 0; //그림자 블럭의 x좌표
int Shadow_Ypos = 0; //그림자 블럭의 y좌표
int Block_Rotation = 0; //블럭의 회전상태 (1~28)
int Block_Type = 1; //블럭의 종류 (1~7)
int NextBlock_Type = 1; //다음 블럭
int YIndex; //얼마나 더 내릴 수 있는가
int score; //점수
int TotalDeletedLine = 0; //총 지워진 줄 수
float Speed_Level_Fixed; //속도 레벨 (초기값)
float Speed_Level; //속도 레벨
int map_type = 1; //맵 종류

int block[][4][4] = {
	/*■
	■■■*/
{ { 0, 0, 0, 0 },{ 1, 0, 0, 0 },{ 1, 1, 1, 0 },{ 0, 0, 0, 0 } },
{ { 0, 0, 1, 0 },{ 0, 0, 1, 0 },{ 0 ,1 ,1 ,0 },{ 0 ,0 ,0 ,0 } },
{ { 1, 1, 1, 0 },{ 0, 0, 1, 0 },{ 0 ,0 ,0 ,0 },{ 0 ,0 ,0 ,0 } },
{ { 1, 1, 0, 0 },{ 1, 0, 0, 0 },{ 1 ,0 ,0 ,0 },{ 0 ,0 ,0 ,0 } },
/* 두 번째 블록
■
■■■     */
{ { 0, 0, 0, 0 },{ 0, 0, 1, 0 },{ 1, 1, 1, 0 },{ 0, 0, 0, 0 } },
{ { 0, 1, 1, 0 },{ 0, 0, 1, 0 },{ 0, 0, 1, 0 },{ 0, 0, 0, 0 } },
{ { 1, 1, 1, 0 },{ 1, 0, 0, 0 },{ 0, 0, 0, 0 },{ 0, 0, 0, 0 } },
{ { 1, 0, 0, 0 },{ 1, 0, 0, 0 },{ 1, 1, 0, 0 },{ 0, 0, 0, 0 } },

/* 세 번째 블록
■
■■■    */
{ { 0, 0, 0, 0 },{ 0, 1, 0, 0 },{ 1, 1, 1, 0 },{ 0, 0, 0, 0 } },
{ { 0, 0, 0, 0 },{ 0, 1, 0, 0 },{ 1, 1, 0, 0 },{ 0, 1, 0, 0 } },
{ { 0, 0, 0, 0 },{ 0, 0, 0, 0 },{ 1, 1, 1, 0 },{ 0, 1, 0, 0 } },
{ { 0, 0, 0, 0 },{ 0, 1, 0, 0 },{ 0, 1, 1, 0 },{ 0, 1, 0, 0 } },

/* 네 번째 블록

■■■■   */
{ { 0, 1, 0, 0 },{ 0, 1, 0, 0 },{ 0, 1, 0, 0 },{ 0, 1, 0, 0 } },
{ { 0, 0, 0, 0 },{ 0, 0, 0, 0 },{ 1, 1, 1, 1 },{ 0, 0, 0, 0 } },
{ { 0, 1, 0, 0 },{ 0, 1, 0, 0 },{ 0, 1, 0, 0 },{ 0, 1, 0, 0 } },
{ { 0, 0, 0, 0 },{ 0, 0, 0, 0 },{ 1, 1, 1, 1 },{ 0, 0, 0, 0 } },

/* 다섯 번째 블록

■■
■■      */
{ { 0, 0, 0, 0 },{ 0, 1, 1, 0 },{ 0, 1, 1, 0 },{ 0, 0, 0, 0 } },
{ { 0, 0, 0, 0 },{ 0, 1, 1, 0 },{ 0, 1, 1, 0 },{ 0, 0, 0, 0 } },
{ { 0, 0, 0, 0 },{ 0, 1, 1, 0 },{ 0, 1, 1, 0 },{ 0, 0, 0, 0 } },
{ { 0, 0, 0, 0 },{ 0, 1, 1, 0 },{ 0, 1, 1, 0 },{ 0, 0, 0, 0 } },

/* 여섯 번째 블록
■■
■■      */
{ { 0, 0, 0, 0 },{ 0, 1, 1, 0 },{ 1, 1, 0, 0 },{ 0, 0, 0, 0 } },
{ { 0, 1, 0, 0 },{ 0, 1, 1, 0 },{ 0, 0, 1, 0 },{ 0, 0, 0, 0 } },
{ { 0, 0, 0, 0 },{ 0, 1, 1, 0 },{ 1, 1, 0, 0 },{ 0, 0, 0, 0 } },
{ { 0, 1, 0, 0 },{ 0, 1, 1, 0 },{ 0, 0, 1, 0 },{ 0, 0, 0, 0 } },

/* 일곱 번째 블록
■■
■■    */
{ { 0, 0, 0, 0 },{ 1, 1, 0, 0 },{ 0, 1, 1, 0 },{ 0, 0, 0, 0 } },
{ { 0, 0, 1, 0 },{ 0, 1, 1, 0 },{ 0, 1, 0, 0 },{ 0, 0, 0, 0 } },
{ { 0, 0, 0, 0 },{ 1, 1, 0, 0 },{ 0, 1, 1, 0 },{ 0, 0, 0, 0 } },
{ { 0, 0, 1, 0 },{ 0, 1, 1, 0 },{ 0, 1, 0, 0 },{ 0, 0, 0, 0 } },
};

CSystem::CSystem(void) //생성자
{
	srand((unsigned int)time(NULL)); //난수생성 기본설정
}

CSystem::~CSystem(void) //소멸자
{
}

void Ingame(float Set_Level) //실제 게임이 진행되는 부분.
{
	CSystem* pSystem = new CSystem; //memory 할당 //객체 생성
	system("cls"); //화면 클리어

	//mciSendString(L"play Tetris2.mp3", NULL, 0, NULL);
	Speed_Level_Fixed = Set_Level;
	Speed_Level = Speed_Level_Fixed;
	SetCoord(); //위치 지정
	SetBlock();
	UpdateUI();
	NextBlockUI();
	gotoxy(35, 17);
	printf("총 지운 줄 : %d (줄)", TotalDeletedLine);
	pSystem->Pulse(); //업데이트
}

void CSystem::Pulse() //밀다 //업데이트
{
	TIMEMANAGER->Initialize(); //타임매니저 기본설정
	while (1)
	{
		if (GameOver()) break; //만약 게임오버면 반복문 탈출한다.
		TIMEMANAGER->Pulse(); //타임매니저 업데이트 돌리기

		m_pGameFrame = new CFrameSkip; //프레임 제한
		m_pGameFrame->SetFramePerSec(60); //60fps

		float fTimeStep = TIMEMANAGER->GetTimeStep();

		if (m_pGameFrame->Update(fTimeStep))
		{
			DrawAllArea(); //블럭 업데이트
			//DrawNumber(); //디버깅 전용
			gotoxy(1, 1);
			printf("누적시간 : %.2f", TIMEMANAGER->m_fAcculTime);

			if (kbhit()) //키 입력이 있으면
			{
				kb = _getch();	//키 분석

				DeletePrevBlock(); //현재 모양 지우기
				DeletePrevShadowBlock(Block_Xpos, Block_Ypos + YIndex - 1); //현재 그림자 지우기
				Movement(); //이동하기
				BlockPreview(); //그림자 생성과 렌더링
			}
			if (TIMEMANAGER->m_fdeltaTime > Speed_Level) //n초에 한 번씩 실행
			{
				FallDown(); //블럭이 떨어진다
				CreateNewBlock(); //새 블럭을 만들것인지 체크
				TIMEMANAGER->m_fdeltaTime = 0;
			}
		}
	}
}

void SetCoord() //처음 블럭 배치
{
	for (int y = 1; y <= BOARD_HEIGHT; y++)
	{
		for (int x = 1; x <= BOARD_WIDTH; x++)
		{
			if (x == 1 || x == BOARD_WIDTH || y == BOARD_HEIGHT)
				Area[y][x] = -3; //-3은 외벽
		}
	}
	system("cls");
	printf("맵을 선택해주세요.\n");
	printf("1. 클래식 2. 자갈 3. 절벽");
	map_type = getch();
		switch (map_type)
		{
		case 49: break;
		case 50: SetMap_1(); break;
		case 51: SetMap_2(); break;
		}
	system("cls");
}

void SetMap_1() //1번맵 배치 //자갈
{
	int HowManyBlock = 10; //총 배치될 블럭의 개수
	while (HowManyBlock > 0)
	{
		for (int y = 1; y < BOARD_HEIGHT; y++)
		{
			for (int x = 1; x <= BOARD_WIDTH; x++)
			{
				if (y > BOARD_HEIGHT - 5 && x > 1 && x < BOARD_WIDTH)
				{
					if (rand() % 100 + 1 > 40 && Area[y][x] != 2) //50퍼 확률로 //그 자리에 블럭이 없으면
					{
						Area[y][x] = 2;
						HowManyBlock--;
					}
				}
			}
		}
	}
}

void SetMap_2() //2번맵 배치 //절벽
{
		for (int x = 1; x <= BOARD_WIDTH; x++)
		{
			if (x == 2 || x == BOARD_WIDTH-1)
			{
				for (int y = 10; y < BOARD_HEIGHT; y++)
					Area[y][x] = 2;
			}
			if (x == 3 || x == BOARD_WIDTH - 2)
			{
				for (int y = 9; y < BOARD_HEIGHT; y++)
					Area[y][x] = 2;
			}
			if (x == 4 || x == BOARD_WIDTH - 3)
			{
				for (int y = 8; y < BOARD_HEIGHT; y++)
					Area[y][x] = 2;
			}
		}
}

void SetBlock() //블럭 배치하기
{
	for (int y = 0; y < 4; y++) //블럭 배열을 불러와서 화면에 띄우고 값을 수정한다.
	{
		for (int x = 0; x < 4; x++) 
		{
			if (Area[Block_Ypos + y][Block_Xpos + x] + block[Block_Rotation][y][x] == 6) //만약 그곳이 그림자면
				Area[Block_Ypos + y][Block_Xpos + x] = 1; //그림자 제거하기
			else 
			Area[Block_Ypos + y][Block_Xpos + x] += block[Block_Rotation][y][x];
		}
	}
}

void DeletePrevBlock() //잔상 지우기
{
	for (int y = 0; y < 4; y++) //블럭 배열을 불러와서 화면에 띄우고 값을 수정한다.
	{
		for (int x = 0; x < 4; x++)
		{
			if (block[Block_Rotation][y][x] == 1) //현재 자기 블럭을 0으로 바꾸기
				Area[Block_Ypos + y][Block_Xpos + x] = 0;
		}
	}
}

void DrawAllArea() 
{
	for (int y = 0; y <= BOARD_HEIGHT; y++)
	{
		for (int x = 0; x <= BOARD_WIDTH; x++)
		{
			if (backBufferArea[y][x] != Area[y][x])
			{
				gotoxy(BOARD_X + x * 2, BOARD_Y + y);
				if (Area[y][x] == 0)
				{
					printf("　");
				}
				else if (Area[y][x] == 1)
				{
					printf("■");
				}
				else if (Area[y][x] == 2)
				{
					printf("▣");
				}
				else if (Area[y][x] == 5)
				{
					printf("□");
				}
				else if (Area[y][x] == -3)
				{
					printf("▨");
				}
			}
		}
		puts("");
	}
	for (int y = 0; y <= BOARD_HEIGHT; y++)
	{
		for (int x = 0; x <= BOARD_WIDTH; x++)
		{
			backBufferArea[y][x] = Area[y][x];
		}
	}
}

void DrawNumber() //보드판 숫자로 업데이트
{
	for (int y = 1; y <= BOARD_HEIGHT; y++)
	{
		for (int x = 1; x <= BOARD_WIDTH; x++)
		{
			gotoxy(BOARD_X + x * 2, BOARD_Y + y);
				printf("%d", Area[y][x]);
		}
		puts("");
	}
}

void FallDown() //블럭이 매 초마다 아래로 떨어지게
{
	DeletePrevBlock(); //내 자신 지우고
	if (CheckClash(Block_Ypos+1, Block_Xpos)) //떨어지려는 공간이 이동가능하면
	{
		Block_Ypos++; //Y축 하나 내리고 
	}
	SetBlock(); //배열에 좌표 찍고
}

void CreateNewBlock() {
	if (!CheckClash(Block_Ypos + 1, Block_Xpos)) //더 이상 아래로 떨어질 수 없으면 
	{
		SetBlock(); //배열에 좌표 찍고
		ConvertToStopBlock(); //멈춘 블럭(2)로 만든다음
		Check_RemoveBlock(); //줄 지울지 체크하고

		Block_Ypos = 0; //높이 재설정
		Block_Xpos = 5; //랜덤하게 위치 생성 //아직은 일단 중앙에 생성
		Block_Type = NextBlock_Type; //다음 블럭 받아오고
		Block_Rotation = Block_Type * 4 - 4; //회전상태 설정
		SetBlock(); //배열에 좌표 찍고

		NextBlock_Type = rand() % 7 + 1; //다음 모양 무작위로

		NextBlockUI();
	}
}

void ConvertToStopBlock() //블럭 굳히기
{
	for (int y = 0; y < 4; y++) 
	{
		for (int x = 0; x < 4; x++)
		{
			if (Area[Block_Ypos + y][Block_Xpos + x] == 1)
			Area[Block_Ypos + y][Block_Xpos + x] = 2;
		}
	}
}

void Movement() //이동하는 함수
{
	switch (kb)
	{
	case VK_ESCAPE:
		return;
	case LEFT:
		if (CheckClash(Block_Ypos, Block_Xpos-1)) //이동할 위치가 충돌이 아니면
			Block_Xpos--; //이동한다.
		break;
	case RIGHT:
		if(CheckClash(Block_Ypos, Block_Xpos+1)) //이동할 위치가 충돌이 아니면
			Block_Xpos++; //이동한다
		break;
	case UP:
		Block_Rotation++; //일단 뒤집고
		if (Block_Rotation < Block_Type * 4)
		{
			if (!CheckClash(Block_Ypos, Block_Xpos)) //뒤집은 값이 충돌이면
				Block_Rotation--; //전 상태로 돌려놓는다.
			break;
		}
		else if (Block_Rotation == Block_Type * 4) //그게 블럭 타입의 마지막 모양이면
		{
			Block_Rotation = Block_Type * 4 - 4;
			if (!CheckClash(Block_Ypos, Block_Xpos)) //뒤집은 값이 충돌이면
			{
				Block_Rotation = Block_Type * 4 - 1; //다시 마지막 모양으로 되돌린다
			}
			break;
		}
	case DOWN:
		if (CheckClash(Block_Ypos + 1, Block_Xpos)) //이동할 위치가 충돌이 아니면
			Block_Ypos++; //이동한다
		break;
	case SPACEBAR:
		while (1)
		{
			if (CheckClash(Block_Ypos + 1, Block_Xpos)) //이동할 위치가 충돌이 아니면
				Block_Ypos++; //이동한다
			else
				break;
		}
		score += 100; //바로내리기 점수 보너스
	}
	SetBlock();
	CreateNewBlock(); //새 블럭을 만들것인지 체크
} 

bool CheckClash(int PosY, int PosX) //겹침 체크 //Block_Xpos와 Ypos의 인자값을 받는다.
{
	for (int y = 0; y < 4; y++) //블럭 배열 부분만 불러와서 화면에 띄우고 값을 수정한다.
	{
		for (int x = 0; x < 4; x++)
		{
			if ((Area[PosY + y][PosX + x] + block[Block_Rotation][y][x]) == -2
				|| (Area[PosY + y][PosX + x] + block[Block_Rotation][y][x]) == 3)
		//위치값에 블록을 더한값 //블럭(1)과 외벽(-3)이 만나면 -2 이므로 충돌 //블럭이 멈춘블럭(2)와 만나면 3이므로 충돌
			{
				return false;
			}
		}
	}
	return true;
}

void Check_RemoveBlock() //바닥을 지울 것인지 체크한다
{
	int Total = 0;
	int Deleted_Line = 0; // 지워진 줄 합계
	for (int y = 1; y <= BOARD_HEIGHT - 1; y++)
	{
		for (int x = 2; x <= BOARD_WIDTH - 1; x++)
		{
			Total += Area[y][x]; //해당 라인의 값을 모두 더하기
			if (Total == 2* (BOARD_WIDTH - 2)) //멈춘 블럭(2)의 합으로 그 줄이 가득찼는지 확인
			{
				for (int j = 2; j< BOARD_WIDTH; j++) //그 라인을 빈 공간으로 만들기
					Area[y][j] = 0;
				Total = 0; //Total값 초기화
				DescentBlock(y); //블럭들 내리기 //지워야 할 줄의 y값을 전달
				y = 1; x = 2; //블럭 내리고 다시 처음부터 계산
				Deleted_Line++; //지운 줄의 숫자 더하기
				TotalDeletedLine++; //누적 줄 숫자 더하기
			}
		}
		Total = 0;
	}
	if (Deleted_Line > 0) //만약 1줄이라도 지웠으면
	{
		gotoxy(35, 19);
		switch (Deleted_Line)
		{
		case 1: 
			score += 100;
			printf("1줄 제거! (+100)", Deleted_Line);
			break;
		case 2:
			score += 300;
			printf("2줄 제거!! (+300)", Deleted_Line);
			break;
		case 3:
			score += 500;
			printf("3줄 제거!!! (+500)", Deleted_Line);
			break;
		case 4:
			score += 1000;
			printf("4줄 제거!!!! (+1000)", Deleted_Line);
			break;
		}
		SetSpeed();
		//속도 점점 빠르게;
		gotoxy(35, 19);
		printf("                      ");
		gotoxy(35, 20);
		printf("                        ");
		gotoxy(35, 17);
		printf("총 지운 줄 : %d (줄)", TotalDeletedLine);
		UpdateUI(); //스코어 창 업데이트
	}
}

void SetSpeed()
{
	if (Speed_Level > 2)
		Speed_Level = Speed_Level_Fixed - (TotalDeletedLine*0.03);
	else if (Speed_Level > 1.5)
		Speed_Level = Speed_Level_Fixed - (TotalDeletedLine*0.02);
	else if (Speed_Level > 0.1)
		Speed_Level = Speed_Level_Fixed - (TotalDeletedLine*0.01);
}

void DescentBlock(int _y) //블럭 내려주기 //_y는 내리려는 행의 값
{
	for (int y = _y; y > 0; y--)
	{
		for (int x = 2; x < BOARD_WIDTH; x++)
		{
			if (Area[y][x] != -3 && Area[y][x] != 1) //내리려는 부분이 외벽과 현재 떨어지는 블럭이 아닌경우
			Area[y][x] = Area[y-1][x]; //윗 블럭을 하나 내림
		}
	}
}

void BlockPreview() {
	YIndex = 0; // 그릴 y좌표를 저장 할 변수
	while (true)
	{
		if (!CheckClash(Block_Ypos + YIndex, Block_Xpos)) break;
		YIndex++;
	}
	SetShadowBlock(Block_Xpos, Block_Ypos + YIndex - 1);
}

void SetShadowBlock(int x_index, int y_index) {
	for (int y = 0; y < 4; y++) //블럭 배열 부분만 불러와서 화면에 띄우고 값을 수정한다.
	{
		for (int x = 0; x < 4; x++)
		{
			if (block[Block_Rotation][y][x] == 1 && Area[y_index + y][x_index + x] != 1) { //그림자 만드려는 곳에 이미 움직이는 블럭이 있지 않을때만
				Area[y_index + y][x_index + x] = 5;
			}
		}
	}
}

void DeletePrevShadowBlock(int x_index, int y_index) //잔상 지우기
{
	for (int y = 0; y < 5; y++) //블럭 배열을 불러와서 화면에 띄우고 값을 수정한다.
	{
		for (int x = 0; x < 5; x++)
		{
			if (Area[y_index + y][x_index + x] == 5)
				Area[y_index + y][x_index + x] = 0;
		}
	}
}

void UpdateUI() 
{
	gotoxy(25 + BOARD_WIDTH, 5);
	puts("┏━━━━━━━┓");
	gotoxy(25 + BOARD_WIDTH, 7);
	puts("┗━━━━━━━┛");
	gotoxy(27 + BOARD_WIDTH, 6);
	printf("SCORE : %d", score);
	gotoxy(35, 20);
	printf("속도 : %.2f /Sec", Speed_Level);
}

void NextBlockUI()
{
	gotoxy(25 + BOARD_WIDTH, 10);
	puts("┏━━━━━━┓");
	gotoxy(25 + BOARD_WIDTH, 15);
	puts("┗━━━━━━┛");

	for (int y = 0; y < 4; y++) // 블럭 배열의 부분만 업데이트한다.
	{
		for (int x = 0; x < 4; x++)
		{
			if (block[NextBlock_Type * 4 - 4][y][x] == 1)
			{
				gotoxy((x * 2) + 29 + BOARD_WIDTH, 11 + y);
				printf("■");
			}
			else
			{
				gotoxy((x * 2) + 29 + BOARD_WIDTH, 11 + y);
				printf("  ");
			}
		}
	}
}

bool GameOver()
{
	for (int x = 2; x < BOARD_WIDTH; x++)
		if (Area[1][x] == 2)
		{
			Sleep(500);
			return true; //y축 1열에 쌓인 블럭이 있으면
		}
	return false;
}