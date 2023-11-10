#pragma once

#ifndef __XIANGQI_H__
#define __XIANGQI_H__

#include <stdio.h>
#include <locale.h>
#include <conio.h>

// �׷��� �迭 ��, �� + ���� ���� 4ĭ�� �� 8ĭ
#define G_BOARD_ROW (81)
#define G_BOARD_COL (137)

// ���� ���� ����� ���� �ε���
#define G_ROW_START (4)
#define G_ROW_END (G_BOARD_ROW - 4 - 1)
#define G_COL_START (8)
#define G_COL_END (G_BOARD_COL - 8 - 1)

// ����� �� ���� ����
#define G_BOARD_INTERVAL_ROW (7)
#define G_BOARD_INTERVAL_COL (14)

// ��⸻ �迭 ��, ��
#define BOARD_ROW (10)
#define BOARD_COL (9)

// Ű �Է�
#define LEFT (75)
#define RIGHT (77)
#define UP (72)
#define DOWN (80)

typedef struct PointCurser
{
	int x, y;
	// �� ����־�� ��
} PointCurser;


typedef struct Board
{
	// ���� ȭ�鿡 ��Ÿ�� ������� �����ϴ� �迭
	wchar_t graphicBoard[G_BOARD_ROW][G_BOARD_COL];
	// ��꿡 �ʿ��� ��⸻�� ��ġ�� �����ϰ� �ִ� �迭
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

