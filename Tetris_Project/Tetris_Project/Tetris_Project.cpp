//메인 함수가 진행되는 부분이다.
#include "stdafx.h"

int main()
{
	system("mode con cols=60 lines=35"); //윈도우 콘솔창 크기
	_SetCursor(false); //커서 숨기기

	Ingame(ShowMenu());
	GameOverScreen();
    return 0;
}

