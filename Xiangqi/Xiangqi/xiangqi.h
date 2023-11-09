#pragma once

#ifndef __XIANGQI_H__
#define __XIANGQI_H__

#include <stdio.h>

// 그래픽 배열 행, 열
#define G_BOARDROW (50)
#define G_BOARDCOL (45)

// 장기말 배열 행, 열
#define BOARDROW (10)
#define BOARDCOL (9)

typedef struct Board
{
	// 실제 화면에 나타날 장기판을 저장하는 배열
	char graphicBoard[G_BOARDROW][G_BOARDCOL];
	// 계산에 필요한 장기말의 위치를 저장하고 있는 배열
	int piecesArr[BOARDROW][BOARDCOL];
} Board;

void initBorad(char _pBoard[G_BOARDROW][G_BOARDCOL]);

#endif // !__XIANGQI_H__

