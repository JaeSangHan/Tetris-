//���θ޴� UI�� ���� �κ��̴�.
#include "stdafx.h"

float ShowMenu() {
	system("cls");
	SetColor(11);
	gotoxy(17, 0);
	puts("��������������������������������������������������");
	gotoxy(17, 3);
	puts("��������������������������������������������������");
	gotoxy(20, 1);
	puts("Tetris!");
	Sleep(300);
	gotoxy(27, 2);
	puts("20225_�����");
	Sleep(300);
	gotoxy(19, 10);
	puts("�������������������㦬����������������");//���

	float Speed_Level = 1.0f;
	gotoxy(22, 15);
	printf("SPEED : %.2f /Sec", Speed_Level);

	gotoxy(19, 20);
	puts("�������������������妬����������������");

	gotoxy(19, 21);
	printf("PRESS SPACE TO START");
	while (1)
	{
		if (kbhit()) //Ű �Է��� ������
		{
			switch (getch())
			{
			case UP: if (Speed_Level <= 2.95) Speed_Level += 0.05; break;
			case DOWN: if (Speed_Level > 0.05) Speed_Level -= 0.05; break;
			case SPACEBAR: return Speed_Level;//�����̽��� ������ ���� //���ǵ� ��ȯ
			}
			gotoxy(22, 15);
			printf("SPEED : %.2f /Sec", Speed_Level);
		}
	}

	system("cls");
}

void GameOverScreen()
{
	system("cls");
	system("mode con cols=70 lines=15"); //������ �ܼ�â ũ��
	printf("���������������������������������\n");
	printf("���������������������������������\n");
	printf("���������������������������������\n");
	printf("���������������������������������\n");
	printf("���������������������������������\n");
	printf("���������������������������������\n");
	printf("���������������������������������\n");
	printf("���������������������������������\n");
	printf("���������������������������������\n");
	printf("���������������������������������\n");
	printf("���������������������������������\n");
	Sleep(500);
}																				