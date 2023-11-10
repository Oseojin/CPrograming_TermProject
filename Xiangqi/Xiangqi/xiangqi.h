#pragma once

#ifndef __XIANGQI_H__
#define __XIANGQI_H__

#include <stdio.h>
#include <locale.h>
#include <conio.h>

// 그래픽 배열 행, 열 + 양쪽 여백 4칸씩 총 8칸
#define G_BOARD_ROW (81)
#define G_BOARD_COL (137)

// 여백 제외 장기판 시작 인덱스
#define G_ROW_START (4)
#define G_ROW_END (G_BOARD_ROW - 4 - 1)
#define G_COL_START (8)
#define G_COL_END (G_BOARD_COL - 8 - 1)

// 장기판 줄 사이 간격
#define G_BOARD_INTERVAL_ROW (7)
#define G_BOARD_INTERVAL_COL (14)

// 장기말 배열 행, 열
#define BOARD_ROW (10)
#define BOARD_COL (9)

// 키 입력
#define LEFT (75)
#define RIGHT (77)
#define UP (72)
#define DOWN (80)

typedef struct PointCurser
{
	int x, y;
	// 색 집어넣어야 함
} PointCurser;


typedef struct Board
{
	// 실제 화면에 나타날 장기판을 저장하는 배열
	wchar_t graphicBoard[G_BOARD_ROW][G_BOARD_COL];
	// 계산에 필요한 장기말의 위치를 저장하고 있는 배열
	int piecesArr[BOARD_ROW][BOARD_COL];
} Board;

void initGame(wchar_t _board[G_BOARD_ROW][G_BOARD_COL], PointCurser *player1, PointCurser *player2);
void initBoard(wchar_t _board[G_BOARD_ROW][G_BOARD_COL]);
void drawBoard(wchar_t _board[G_BOARD_ROW][G_BOARD_COL]);

void initCurser(PointCurser* player1, PointCurser* player2);
void moveCurser(wchar_t _board[G_BOARD_ROW][G_BOARD_COL], PointCurser* player, int moveDir);

char playerInputKey(PointCurser* player);

void printAlert(char alertText[]);

#endif // !__XIANGQI_H__

