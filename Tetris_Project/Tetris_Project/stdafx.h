// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//
#pragma once
#define _CRT_NONSTDC_NO_WARNINGS //getch 오류 방지를 위해
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACEBAR 32

#define KEY_Z 122
#define KEY_X 120
#define KEY_C 99

#define BOARD_HEIGHT 20 // 보드 높이
#define BOARD_WIDTH 10 // 보드 폭
#define BOARD_X 4 //보드 열 x좌표
#define BOARD_Y 2 //보드 행 y좌표

#define WINDOW_X 60 //윈도우 창 크기
#define WINDOW_Y 35

#include "targetver.h"

#include <stdio.h>
#include <Windows.h>
#include <time.h>

#include <conio.h>
#include <tchar.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include "Util.h"
#include "FrameSkip.h"
#include "TimeManager.h"
#include "Ingame.h"
#include "UI_Function.h"
#include "MainMenu.h"
