#include "xiangqi.h"

void initGame(wchar_t _board[G_BOARD_ROW][G_BOARD_COL], PointCurser *player1, PointCurser *player2)
{
	initBoard(_board);
	drawBoard(_board);
	initCurser(player1, player2);
}

// 초기 장기판을 그래픽 배열에 저장하는 함수
void initBoard(wchar_t _board[G_BOARD_ROW][G_BOARD_COL])
{
	for (int i = 0; i < G_BOARD_ROW; i++)
	{
		for (int j = 0; j < G_BOARD_COL; j++)
		{
			// 여백 부분
			if (i < G_ROW_START || i > G_ROW_END || j < G_COL_START || j > G_COL_END)
			{
				_board[i][j] = L' ';
				continue;
			}

			// 왼쪽 위
			if (i == G_ROW_START && j == G_COL_START)
			{
				_board[i][j] = L'';
			}
			// 오른쪽 위
			else if (i == G_ROW_START && j == G_COL_END)
			{
				_board[i][j] = L'';
			}
			// 왼쪽 아래
			else if (i == G_ROW_END && j == G_COL_START)
			{
				_board[i][j] = L'';
			}
			// 오른쪽 아래
			else if (i == G_ROW_END && j == G_COL_END)
			{
				_board[i][j] = L'';
			}
			// 교차 맨 위
			else if (i == G_ROW_START && (j - G_COL_START) % (G_BOARD_INTERVAL_COL + 1) == 0)
			{
				_board[i][j] = L'';
			}
			// 교차 맨 아래
			else if (i == G_ROW_END && (j - G_COL_START) % (G_BOARD_INTERVAL_COL + 1) == 0)
			{
				_board[i][j] = L'';
			}
			// 교차 맨 왼쪽
			else if (j == G_COL_START && (i - G_ROW_START) % (G_BOARD_INTERVAL_ROW + 1) == 0)
			{
				_board[i][j] = L'';
			}
			// 교차 맨 오른쪽
			else if (j == G_COL_END && (i - G_ROW_START) % (G_BOARD_INTERVAL_ROW + 1) == 0)
			{
				_board[i][j] = L'';
			}
			// 교차 양방
			else if ((i - G_ROW_START) % (G_BOARD_INTERVAL_ROW + 1) == 0 && (j - G_COL_START) % (G_BOARD_INTERVAL_COL + 1) == 0)
			{
				_board[i][j] = L'';
			}
			// 선 수평
			else if ((i - G_ROW_START) % (G_BOARD_INTERVAL_ROW + 1) == 0 && (j - G_COL_START) % (G_BOARD_INTERVAL_COL + 1) != 0)
			{
				_board[i][j] = L'';
			}
			// 선 수직
			else if ((i - G_ROW_START) % (G_BOARD_INTERVAL_ROW + 1) != 0 && (j - G_COL_START) % (G_BOARD_INTERVAL_COL + 1) == 0)
			{
				_board[i][j] = L'';
			}
			// 빈 공간
			else
			{
				_board[i][j] = L' ';
			}
		}
	}
}

// 장기판을 그리는 함수
void drawBoard(wchar_t _board[G_BOARD_ROW][G_BOARD_COL])
{
	for (int i = 0; i < G_BOARD_ROW; i++)
	{
		for (int j = 0; j < G_BOARD_COL; j++)
		{
			putwchar(_board[i][j]);
		}
		printf("\n");
	}
}

// 플레이어의 선택 위치를 표시하는 커서 위치를 초기화 시키는 함수
void initCurser(PointCurser *player1, PointCurser *player2)
{
	player1->x = G_BOARD_ROW / 2 - 2;
	player1->y = G_BOARD_COL / 2;

	player2->x = G_BOARD_ROW / 2 - 2;
	player2->y = G_BOARD_COL / 2;
}

// 플레이어의 커서를 이동시키는 함수
void moveCurser(wchar_t _board[G_BOARD_ROW][G_BOARD_COL], PointCurser *player, int moveDir)
{
	switch (moveDir)
	{
	case LEFT:
		if (player->x - (G_BOARD_INTERVAL_COL + 1) < G_COL_START)
		{
			printAlert("장기판 밖으로 나갈 수 없습니다.\n");
			printf("(%d,%d)\n", player->x, player->y);
			break;
		}

		player->x -= (G_BOARD_INTERVAL_COL + 1);
		printf("(%d,%d)\n", player->x, player->y);
		break;

	case RIGHT:
		if (player->x + (G_BOARD_INTERVAL_COL + 1) > G_COL_END)
		{
			printAlert("장기판 밖으로 나갈 수 없습니다.\n");
			printf("(%d,%d)\n", player->x, player->y);
			break;
		}

		player->x += (G_BOARD_INTERVAL_COL + 1);
		printf("(%d,%d)\n", player->x, player->y);
		break;

	case UP:
		if (player->y - (G_BOARD_INTERVAL_ROW + 1) > G_ROW_END)
		{
			printAlert("장기판 밖으로 나갈 수 없습니다.\n");
			printf("(%d,%d)\n", player->x, player->y);
			break;
		}

		player->y -= (G_BOARD_INTERVAL_ROW + 1);
		printf("(%d,%d)\n", player->x, player->y);
		break;

	case DOWN:
		if (player->y + (G_BOARD_INTERVAL_ROW + 1) < G_ROW_START)
		{
			printAlert("장기판 밖으로 나갈 수 없습니다.\n");
			printf("(%d,%d)\n", player->x, player->y);
			break;
		}

		player->y += (G_BOARD_INTERVAL_ROW + 1);
		printf("(%d,%d)\n", player->x, player->y);
		break;

	default:
		break;
	}

	initBoard(_board);
	_board[player->y][player->x] = L'a';
	drawBoard(_board);
}

// 플레이어의 입력을 받는 함수
char playerInputKey(PointCurser* player)
{
	char c;
	if (_kbhit())
	{
		c = _getch();
		if (c == -32)
		{
			c = _getch();
			return c;
		}
	}
}

// 경고문을 표시하는 함수
void printAlert(char alertText[])
{
	printf("%s", alertText);
}