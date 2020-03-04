//메인메뉴 UI를 띄우는 부분이다.
#include "stdafx.h"

float ShowMenu() {
	system("cls");
	SetColor(11);
	gotoxy(17, 0);
	puts("┏━━━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(17, 3);
	puts("┗━━━━━━━━━━━━━━━━━━━━━━━┛");
	gotoxy(20, 1);
	puts("Tetris!");
	Sleep(300);
	gotoxy(27, 2);
	puts("20225_한재상");
	Sleep(300);
	gotoxy(19, 10);
	puts("━━━━━━━━━▲━━━━━━━━━");//▲▼

	float Speed_Level = 1.0f;
	gotoxy(22, 15);
	printf("SPEED : %.2f /Sec", Speed_Level);

	gotoxy(19, 20);
	puts("━━━━━━━━━▼━━━━━━━━━");

	gotoxy(19, 21);
	printf("PRESS SPACE TO START");
	while (1)
	{
		if (kbhit()) //키 입력이 있으면
		{
			switch (getch())
			{
			case UP: if (Speed_Level <= 2.95) Speed_Level += 0.05; break;
			case DOWN: if (Speed_Level > 0.05) Speed_Level -= 0.05; break;
			case SPACEBAR: return Speed_Level;//스페이스바 눌러서 시작 //스피드 반환
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
	system("mode con cols=70 lines=15"); //윈도우 콘솔창 크기
	printf("□■■■■■□□□□□■□□□□■□□□□□■□■■■■■□□□\n");
	printf("□■□□□□□□□□■□■□□□■■□□□■■□■□□□□□□□\n");
	printf("□■□□■■■□□■□□□■□□■□■□■□■□■■■■■□□□\n");
	printf("□■□□□■□□□■■■■■□□■□□■□□■□■□□□□□□□\n");
	printf("□■■■■■□□□■□□□■□□■□□■□□■□■■■■■□□□\n");
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
	printf("□■■■■■■□□■□□□□□□□■□■■■■■□□■■■■□□\n");
	printf("□■□□□□■□□□■□□□□□■□□■□□□□□□■□□■□□\n");
	printf("□■□□□□■□□□□■□□□■□□□■■■■■□□■■■□□□\n");
	printf("□■□□□□■□□□□□■□■□□□□■□□□□□□■□□■□□\n");
	printf("□■■■■■■□□□□□□■□□□□□■■■■■□□■□□□■□\n");
	Sleep(500);
}																				