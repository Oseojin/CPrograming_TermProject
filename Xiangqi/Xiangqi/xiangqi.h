#pragma once

#ifndef __XIANGQI_H__
#define __XIANGQI_H__

#include <stdio.h>

// �׷��� �迭 ��, ��
#define G_BOARDROW (50)
#define G_BOARDCOL (45)

// ��⸻ �迭 ��, ��
#define BOARDROW (10)
#define BOARDCOL (9)

typedef struct Board
{
	// ���� ȭ�鿡 ��Ÿ�� ������� �����ϴ� �迭
	char graphicBoard[G_BOARDROW][G_BOARDCOL];
	// ��꿡 �ʿ��� ��⸻�� ��ġ�� �����ϰ� �ִ� �迭
	int piecesArr[BOARDROW][BOARDCOL];
} Board;

void initBorad(char _pBoard[G_BOARDROW][G_BOARDCOL]);

#endif // !__XIANGQI_H__

