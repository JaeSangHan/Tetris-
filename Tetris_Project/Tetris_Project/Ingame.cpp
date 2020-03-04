#include "stdafx.h"

int Area[BOARD_HEIGHT + 1][BOARD_WIDTH + 1] = { 0, }; //0�� �� ����, -3�� �ܺ�
int backBufferArea[BOARD_HEIGHT + 1][BOARD_HEIGHT + 1] = { 0, }; //������۸��� ���ؼ�
int kb; //Ű���� �Է�
int Block_Xpos = 5; //���� x��ǥ
int Block_Ypos = 0; //���� y��ǥ
int Shadow_Xpos = 0; //�׸��� ���� x��ǥ
int Shadow_Ypos = 0; //�׸��� ���� y��ǥ
int Block_Rotation = 0; //���� ȸ������ (1~28)
int Block_Type = 1; //���� ���� (1~7)
int NextBlock_Type = 1; //���� ��
int YIndex; //�󸶳� �� ���� �� �ִ°�
int score; //����
int TotalDeletedLine = 0; //�� ������ �� ��
float Speed_Level_Fixed; //�ӵ� ���� (�ʱⰪ)
float Speed_Level; //�ӵ� ����
int map_type = 1; //�� ����

int block[][4][4] = {
	/*��
	����*/
{ { 0, 0, 0, 0 },{ 1, 0, 0, 0 },{ 1, 1, 1, 0 },{ 0, 0, 0, 0 } },
{ { 0, 0, 1, 0 },{ 0, 0, 1, 0 },{ 0 ,1 ,1 ,0 },{ 0 ,0 ,0 ,0 } },
{ { 1, 1, 1, 0 },{ 0, 0, 1, 0 },{ 0 ,0 ,0 ,0 },{ 0 ,0 ,0 ,0 } },
{ { 1, 1, 0, 0 },{ 1, 0, 0, 0 },{ 1 ,0 ,0 ,0 },{ 0 ,0 ,0 ,0 } },
/* �� ��° ���
��
����     */
{ { 0, 0, 0, 0 },{ 0, 0, 1, 0 },{ 1, 1, 1, 0 },{ 0, 0, 0, 0 } },
{ { 0, 1, 1, 0 },{ 0, 0, 1, 0 },{ 0, 0, 1, 0 },{ 0, 0, 0, 0 } },
{ { 1, 1, 1, 0 },{ 1, 0, 0, 0 },{ 0, 0, 0, 0 },{ 0, 0, 0, 0 } },
{ { 1, 0, 0, 0 },{ 1, 0, 0, 0 },{ 1, 1, 0, 0 },{ 0, 0, 0, 0 } },

/* �� ��° ���
��
����    */
{ { 0, 0, 0, 0 },{ 0, 1, 0, 0 },{ 1, 1, 1, 0 },{ 0, 0, 0, 0 } },
{ { 0, 0, 0, 0 },{ 0, 1, 0, 0 },{ 1, 1, 0, 0 },{ 0, 1, 0, 0 } },
{ { 0, 0, 0, 0 },{ 0, 0, 0, 0 },{ 1, 1, 1, 0 },{ 0, 1, 0, 0 } },
{ { 0, 0, 0, 0 },{ 0, 1, 0, 0 },{ 0, 1, 1, 0 },{ 0, 1, 0, 0 } },

/* �� ��° ���

�����   */
{ { 0, 1, 0, 0 },{ 0, 1, 0, 0 },{ 0, 1, 0, 0 },{ 0, 1, 0, 0 } },
{ { 0, 0, 0, 0 },{ 0, 0, 0, 0 },{ 1, 1, 1, 1 },{ 0, 0, 0, 0 } },
{ { 0, 1, 0, 0 },{ 0, 1, 0, 0 },{ 0, 1, 0, 0 },{ 0, 1, 0, 0 } },
{ { 0, 0, 0, 0 },{ 0, 0, 0, 0 },{ 1, 1, 1, 1 },{ 0, 0, 0, 0 } },

/* �ټ� ��° ���

���
���      */
{ { 0, 0, 0, 0 },{ 0, 1, 1, 0 },{ 0, 1, 1, 0 },{ 0, 0, 0, 0 } },
{ { 0, 0, 0, 0 },{ 0, 1, 1, 0 },{ 0, 1, 1, 0 },{ 0, 0, 0, 0 } },
{ { 0, 0, 0, 0 },{ 0, 1, 1, 0 },{ 0, 1, 1, 0 },{ 0, 0, 0, 0 } },
{ { 0, 0, 0, 0 },{ 0, 1, 1, 0 },{ 0, 1, 1, 0 },{ 0, 0, 0, 0 } },

/* ���� ��° ���
���
���      */
{ { 0, 0, 0, 0 },{ 0, 1, 1, 0 },{ 1, 1, 0, 0 },{ 0, 0, 0, 0 } },
{ { 0, 1, 0, 0 },{ 0, 1, 1, 0 },{ 0, 0, 1, 0 },{ 0, 0, 0, 0 } },
{ { 0, 0, 0, 0 },{ 0, 1, 1, 0 },{ 1, 1, 0, 0 },{ 0, 0, 0, 0 } },
{ { 0, 1, 0, 0 },{ 0, 1, 1, 0 },{ 0, 0, 1, 0 },{ 0, 0, 0, 0 } },

/* �ϰ� ��° ���
���
���    */
{ { 0, 0, 0, 0 },{ 1, 1, 0, 0 },{ 0, 1, 1, 0 },{ 0, 0, 0, 0 } },
{ { 0, 0, 1, 0 },{ 0, 1, 1, 0 },{ 0, 1, 0, 0 },{ 0, 0, 0, 0 } },
{ { 0, 0, 0, 0 },{ 1, 1, 0, 0 },{ 0, 1, 1, 0 },{ 0, 0, 0, 0 } },
{ { 0, 0, 1, 0 },{ 0, 1, 1, 0 },{ 0, 1, 0, 0 },{ 0, 0, 0, 0 } },
};

CSystem::CSystem(void) //������
{
	srand((unsigned int)time(NULL)); //�������� �⺻����
}

CSystem::~CSystem(void) //�Ҹ���
{
}

void Ingame(float Set_Level) //���� ������ ����Ǵ� �κ�.
{
	CSystem* pSystem = new CSystem; //memory �Ҵ� //��ü ����
	system("cls"); //ȭ�� Ŭ����

	//mciSendString(L"play Tetris2.mp3", NULL, 0, NULL);
	Speed_Level_Fixed = Set_Level;
	Speed_Level = Speed_Level_Fixed;
	SetCoord(); //��ġ ����
	SetBlock();
	UpdateUI();
	NextBlockUI();
	gotoxy(35, 17);
	printf("�� ���� �� : %d (��)", TotalDeletedLine);
	pSystem->Pulse(); //������Ʈ
}

void CSystem::Pulse() //�д� //������Ʈ
{
	TIMEMANAGER->Initialize(); //Ÿ�ӸŴ��� �⺻����
	while (1)
	{
		if (GameOver()) break; //���� ���ӿ����� �ݺ��� Ż���Ѵ�.
		TIMEMANAGER->Pulse(); //Ÿ�ӸŴ��� ������Ʈ ������

		m_pGameFrame = new CFrameSkip; //������ ����
		m_pGameFrame->SetFramePerSec(60); //60fps

		float fTimeStep = TIMEMANAGER->GetTimeStep();

		if (m_pGameFrame->Update(fTimeStep))
		{
			DrawAllArea(); //�� ������Ʈ
			//DrawNumber(); //����� ����
			gotoxy(1, 1);
			printf("�����ð� : %.2f", TIMEMANAGER->m_fAcculTime);

			if (kbhit()) //Ű �Է��� ������
			{
				kb = _getch();	//Ű �м�

				DeletePrevBlock(); //���� ��� �����
				DeletePrevShadowBlock(Block_Xpos, Block_Ypos + YIndex - 1); //���� �׸��� �����
				Movement(); //�̵��ϱ�
				BlockPreview(); //�׸��� ������ ������
			}
			if (TIMEMANAGER->m_fdeltaTime > Speed_Level) //n�ʿ� �� ���� ����
			{
				FallDown(); //���� ��������
				CreateNewBlock(); //�� ���� ��������� üũ
				TIMEMANAGER->m_fdeltaTime = 0;
			}
		}
	}
}

void SetCoord() //ó�� �� ��ġ
{
	for (int y = 1; y <= BOARD_HEIGHT; y++)
	{
		for (int x = 1; x <= BOARD_WIDTH; x++)
		{
			if (x == 1 || x == BOARD_WIDTH || y == BOARD_HEIGHT)
				Area[y][x] = -3; //-3�� �ܺ�
		}
	}
	system("cls");
	printf("���� �������ּ���.\n");
	printf("1. Ŭ���� 2. �ڰ� 3. ����");
	map_type = getch();
		switch (map_type)
		{
		case 49: break;
		case 50: SetMap_1(); break;
		case 51: SetMap_2(); break;
		}
	system("cls");
}

void SetMap_1() //1���� ��ġ //�ڰ�
{
	int HowManyBlock = 10; //�� ��ġ�� ���� ����
	while (HowManyBlock > 0)
	{
		for (int y = 1; y < BOARD_HEIGHT; y++)
		{
			for (int x = 1; x <= BOARD_WIDTH; x++)
			{
				if (y > BOARD_HEIGHT - 5 && x > 1 && x < BOARD_WIDTH)
				{
					if (rand() % 100 + 1 > 40 && Area[y][x] != 2) //50�� Ȯ���� //�� �ڸ��� ���� ������
					{
						Area[y][x] = 2;
						HowManyBlock--;
					}
				}
			}
		}
	}
}

void SetMap_2() //2���� ��ġ //����
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

void SetBlock() //�� ��ġ�ϱ�
{
	for (int y = 0; y < 4; y++) //�� �迭�� �ҷ��ͼ� ȭ�鿡 ���� ���� �����Ѵ�.
	{
		for (int x = 0; x < 4; x++) 
		{
			if (Area[Block_Ypos + y][Block_Xpos + x] + block[Block_Rotation][y][x] == 6) //���� �װ��� �׸��ڸ�
				Area[Block_Ypos + y][Block_Xpos + x] = 1; //�׸��� �����ϱ�
			else 
			Area[Block_Ypos + y][Block_Xpos + x] += block[Block_Rotation][y][x];
		}
	}
}

void DeletePrevBlock() //�ܻ� �����
{
	for (int y = 0; y < 4; y++) //�� �迭�� �ҷ��ͼ� ȭ�鿡 ���� ���� �����Ѵ�.
	{
		for (int x = 0; x < 4; x++)
		{
			if (block[Block_Rotation][y][x] == 1) //���� �ڱ� ���� 0���� �ٲٱ�
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
					printf("��");
				}
				else if (Area[y][x] == 1)
				{
					printf("��");
				}
				else if (Area[y][x] == 2)
				{
					printf("��");
				}
				else if (Area[y][x] == 5)
				{
					printf("��");
				}
				else if (Area[y][x] == -3)
				{
					printf("��");
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

void DrawNumber() //������ ���ڷ� ������Ʈ
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

void FallDown() //���� �� �ʸ��� �Ʒ��� ��������
{
	DeletePrevBlock(); //�� �ڽ� �����
	if (CheckClash(Block_Ypos+1, Block_Xpos)) //���������� ������ �̵������ϸ�
	{
		Block_Ypos++; //Y�� �ϳ� ������ 
	}
	SetBlock(); //�迭�� ��ǥ ���
}

void CreateNewBlock() {
	if (!CheckClash(Block_Ypos + 1, Block_Xpos)) //�� �̻� �Ʒ��� ������ �� ������ 
	{
		SetBlock(); //�迭�� ��ǥ ���
		ConvertToStopBlock(); //���� ��(2)�� �������
		Check_RemoveBlock(); //�� ������ üũ�ϰ�

		Block_Ypos = 0; //���� �缳��
		Block_Xpos = 5; //�����ϰ� ��ġ ���� //������ �ϴ� �߾ӿ� ����
		Block_Type = NextBlock_Type; //���� �� �޾ƿ���
		Block_Rotation = Block_Type * 4 - 4; //ȸ������ ����
		SetBlock(); //�迭�� ��ǥ ���

		NextBlock_Type = rand() % 7 + 1; //���� ��� ��������

		NextBlockUI();
	}
}

void ConvertToStopBlock() //�� ������
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

void Movement() //�̵��ϴ� �Լ�
{
	switch (kb)
	{
	case VK_ESCAPE:
		return;
	case LEFT:
		if (CheckClash(Block_Ypos, Block_Xpos-1)) //�̵��� ��ġ�� �浹�� �ƴϸ�
			Block_Xpos--; //�̵��Ѵ�.
		break;
	case RIGHT:
		if(CheckClash(Block_Ypos, Block_Xpos+1)) //�̵��� ��ġ�� �浹�� �ƴϸ�
			Block_Xpos++; //�̵��Ѵ�
		break;
	case UP:
		Block_Rotation++; //�ϴ� ������
		if (Block_Rotation < Block_Type * 4)
		{
			if (!CheckClash(Block_Ypos, Block_Xpos)) //������ ���� �浹�̸�
				Block_Rotation--; //�� ���·� �������´�.
			break;
		}
		else if (Block_Rotation == Block_Type * 4) //�װ� �� Ÿ���� ������ ����̸�
		{
			Block_Rotation = Block_Type * 4 - 4;
			if (!CheckClash(Block_Ypos, Block_Xpos)) //������ ���� �浹�̸�
			{
				Block_Rotation = Block_Type * 4 - 1; //�ٽ� ������ ������� �ǵ�����
			}
			break;
		}
	case DOWN:
		if (CheckClash(Block_Ypos + 1, Block_Xpos)) //�̵��� ��ġ�� �浹�� �ƴϸ�
			Block_Ypos++; //�̵��Ѵ�
		break;
	case SPACEBAR:
		while (1)
		{
			if (CheckClash(Block_Ypos + 1, Block_Xpos)) //�̵��� ��ġ�� �浹�� �ƴϸ�
				Block_Ypos++; //�̵��Ѵ�
			else
				break;
		}
		score += 100; //�ٷγ����� ���� ���ʽ�
	}
	SetBlock();
	CreateNewBlock(); //�� ���� ��������� üũ
} 

bool CheckClash(int PosY, int PosX) //��ħ üũ //Block_Xpos�� Ypos�� ���ڰ��� �޴´�.
{
	for (int y = 0; y < 4; y++) //�� �迭 �κи� �ҷ��ͼ� ȭ�鿡 ���� ���� �����Ѵ�.
	{
		for (int x = 0; x < 4; x++)
		{
			if ((Area[PosY + y][PosX + x] + block[Block_Rotation][y][x]) == -2
				|| (Area[PosY + y][PosX + x] + block[Block_Rotation][y][x]) == 3)
		//��ġ���� ����� ���Ѱ� //��(1)�� �ܺ�(-3)�� ������ -2 �̹Ƿ� �浹 //���� �����(2)�� ������ 3�̹Ƿ� �浹
			{
				return false;
			}
		}
	}
	return true;
}

void Check_RemoveBlock() //�ٴ��� ���� ������ üũ�Ѵ�
{
	int Total = 0;
	int Deleted_Line = 0; // ������ �� �հ�
	for (int y = 1; y <= BOARD_HEIGHT - 1; y++)
	{
		for (int x = 2; x <= BOARD_WIDTH - 1; x++)
		{
			Total += Area[y][x]; //�ش� ������ ���� ��� ���ϱ�
			if (Total == 2* (BOARD_WIDTH - 2)) //���� ��(2)�� ������ �� ���� ����á���� Ȯ��
			{
				for (int j = 2; j< BOARD_WIDTH; j++) //�� ������ �� �������� �����
					Area[y][j] = 0;
				Total = 0; //Total�� �ʱ�ȭ
				DescentBlock(y); //���� ������ //������ �� ���� y���� ����
				y = 1; x = 2; //�� ������ �ٽ� ó������ ���
				Deleted_Line++; //���� ���� ���� ���ϱ�
				TotalDeletedLine++; //���� �� ���� ���ϱ�
			}
		}
		Total = 0;
	}
	if (Deleted_Line > 0) //���� 1���̶� ��������
	{
		gotoxy(35, 19);
		switch (Deleted_Line)
		{
		case 1: 
			score += 100;
			printf("1�� ����! (+100)", Deleted_Line);
			break;
		case 2:
			score += 300;
			printf("2�� ����!! (+300)", Deleted_Line);
			break;
		case 3:
			score += 500;
			printf("3�� ����!!! (+500)", Deleted_Line);
			break;
		case 4:
			score += 1000;
			printf("4�� ����!!!! (+1000)", Deleted_Line);
			break;
		}
		SetSpeed();
		//�ӵ� ���� ������;
		gotoxy(35, 19);
		printf("                      ");
		gotoxy(35, 20);
		printf("                        ");
		gotoxy(35, 17);
		printf("�� ���� �� : %d (��)", TotalDeletedLine);
		UpdateUI(); //���ھ� â ������Ʈ
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

void DescentBlock(int _y) //�� �����ֱ� //_y�� �������� ���� ��
{
	for (int y = _y; y > 0; y--)
	{
		for (int x = 2; x < BOARD_WIDTH; x++)
		{
			if (Area[y][x] != -3 && Area[y][x] != 1) //�������� �κ��� �ܺ��� ���� �������� ���� �ƴѰ��
			Area[y][x] = Area[y-1][x]; //�� ���� �ϳ� ����
		}
	}
}

void BlockPreview() {
	YIndex = 0; // �׸� y��ǥ�� ���� �� ����
	while (true)
	{
		if (!CheckClash(Block_Ypos + YIndex, Block_Xpos)) break;
		YIndex++;
	}
	SetShadowBlock(Block_Xpos, Block_Ypos + YIndex - 1);
}

void SetShadowBlock(int x_index, int y_index) {
	for (int y = 0; y < 4; y++) //�� �迭 �κи� �ҷ��ͼ� ȭ�鿡 ���� ���� �����Ѵ�.
	{
		for (int x = 0; x < 4; x++)
		{
			if (block[Block_Rotation][y][x] == 1 && Area[y_index + y][x_index + x] != 1) { //�׸��� ������� ���� �̹� �����̴� ���� ���� ��������
				Area[y_index + y][x_index + x] = 5;
			}
		}
	}
}

void DeletePrevShadowBlock(int x_index, int y_index) //�ܻ� �����
{
	for (int y = 0; y < 5; y++) //�� �迭�� �ҷ��ͼ� ȭ�鿡 ���� ���� �����Ѵ�.
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
	puts("������������������");
	gotoxy(25 + BOARD_WIDTH, 7);
	puts("������������������");
	gotoxy(27 + BOARD_WIDTH, 6);
	printf("SCORE : %d", score);
	gotoxy(35, 20);
	printf("�ӵ� : %.2f /Sec", Speed_Level);
}

void NextBlockUI()
{
	gotoxy(25 + BOARD_WIDTH, 10);
	puts("����������������");
	gotoxy(25 + BOARD_WIDTH, 15);
	puts("����������������");

	for (int y = 0; y < 4; y++) // �� �迭�� �κи� ������Ʈ�Ѵ�.
	{
		for (int x = 0; x < 4; x++)
		{
			if (block[NextBlock_Type * 4 - 4][y][x] == 1)
			{
				gotoxy((x * 2) + 29 + BOARD_WIDTH, 11 + y);
				printf("��");
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
			return true; //y�� 1���� ���� ���� ������
		}
	return false;
}