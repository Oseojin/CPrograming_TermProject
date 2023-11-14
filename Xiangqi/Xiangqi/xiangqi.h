#pragma once

#ifndef __XIANGQI_H__
#define __XIANGQI_H__

#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <Windows.h>

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

// ��⸻ ����
#define PIECE_NUM (16)

// Ű �Է�
#define LEFT (75)
#define RIGHT (77)
#define UP (72)
#define DOWN (80)

enum TeamType
{
	�� = 1,
	�� = 2
} TEAM;

enum ColorType
{
	WHITE = 15,
	BLUE = 9,
	RED = 12
} COLOR;

typedef struct PointCurser
{
	int x, y;
	int colorNum;
} PointCurser;

typedef struct Piece
{
	// ���� �׷��� ũ��
	int width;
	// ���� ����
	wchar_t pieceType;
	// ���� ��
	int team;
	// ���� ����
	float score;
	// ���� ��ġ
	int x, y;
	// �̵� �Լ�: �Լ� ������
}Piece;

typedef struct Player
{
	int teamID;
	int score;
	PointCurser curser;
	Piece pieceSet[PIECE_NUM];
}Player;

typedef struct Board
{
	// ���� ȭ�鿡 ��Ÿ�� ������� �����ϴ� �迭
	wchar_t graphicBoard[G_BOARD_ROW][G_BOARD_COL];
} Board;

void gotoxy(int x, int y);

void initGame(Board* _board, Player* player1, Player* player2);
void initBoard(Board* _board);
void drawBoard(Board* _board);

void initPlayer(Player* player, int _teamID);

void initCurser(PointCurser* curser, int _colorNum);
void moveCurser(Board* _board, Player* player, int moveDir);
void drawCurser(int x, int y, int colorNum);
void removeCurser(int x, int y);

void initPiece(Piece* _piece, wchar_t _type, int _team, int _width, float _score, int _x, int _y);
void initAllPiece(Piece _pieceSet[PIECE_NUM], int team);

void drawPiece(Board* _board, Piece* _piece);
void drawAllPiece(Board* _board, Piece _pieceSet[PIECE_NUM]);

//Piece selectPiece(Board* _board, int x, int y);

char playerInputKey();

void printAlert(char alertText[]);

#endif // !__XIANGQI_H__

