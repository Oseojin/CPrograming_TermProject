#include "xiangqi.h"

void initGame(wchar_t _board[G_BOARD_ROW][G_BOARD_COL], PointCurser *player1, PointCurser *player2)
{
	initBoard(_board);
	drawBoard(_board);
	initCurser(player1, player2);
}

// �ʱ� ������� �׷��� �迭�� �����ϴ� �Լ�
void initBoard(wchar_t _board[G_BOARD_ROW][G_BOARD_COL])
{
	for (int i = 0; i < G_BOARD_ROW; i++)
	{
		for (int j = 0; j < G_BOARD_COL; j++)
		{
			// ���� �κ�
			if (i < G_ROW_START || i > G_ROW_END || j < G_COL_START || j > G_COL_END)
			{
				_board[i][j] = L' ';
				continue;
			}

			// ���� ��
			if (i == G_ROW_START && j == G_COL_START)
			{
				_board[i][j] = L'';
			}
			// ������ ��
			else if (i == G_ROW_START && j == G_COL_END)
			{
				_board[i][j] = L'';
			}
			// ���� �Ʒ�
			else if (i == G_ROW_END && j == G_COL_START)
			{
				_board[i][j] = L'';
			}
			// ������ �Ʒ�
			else if (i == G_ROW_END && j == G_COL_END)
			{
				_board[i][j] = L'';
			}
			// ���� �� ��
			else if (i == G_ROW_START && (j - G_COL_START) % (G_BOARD_INTERVAL_COL + 1) == 0)
			{
				_board[i][j] = L'';
			}
			// ���� �� �Ʒ�
			else if (i == G_ROW_END && (j - G_COL_START) % (G_BOARD_INTERVAL_COL + 1) == 0)
			{
				_board[i][j] = L'';
			}
			// ���� �� ����
			else if (j == G_COL_START && (i - G_ROW_START) % (G_BOARD_INTERVAL_ROW + 1) == 0)
			{
				_board[i][j] = L'';
			}
			// ���� �� ������
			else if (j == G_COL_END && (i - G_ROW_START) % (G_BOARD_INTERVAL_ROW + 1) == 0)
			{
				_board[i][j] = L'';
			}
			// ���� ���
			else if ((i - G_ROW_START) % (G_BOARD_INTERVAL_ROW + 1) == 0 && (j - G_COL_START) % (G_BOARD_INTERVAL_COL + 1) == 0)
			{
				_board[i][j] = L'';
			}
			// �� ����
			else if ((i - G_ROW_START) % (G_BOARD_INTERVAL_ROW + 1) == 0 && (j - G_COL_START) % (G_BOARD_INTERVAL_COL + 1) != 0)
			{
				_board[i][j] = L'';
			}
			// �� ����
			else if ((i - G_ROW_START) % (G_BOARD_INTERVAL_ROW + 1) != 0 && (j - G_COL_START) % (G_BOARD_INTERVAL_COL + 1) == 0)
			{
				_board[i][j] = L'';
			}
			// �� ����
			else
			{
				_board[i][j] = L' ';
			}
		}
	}
}

// ������� �׸��� �Լ�
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

// �÷��̾��� ���� ��ġ�� ǥ���ϴ� Ŀ�� ��ġ�� �ʱ�ȭ ��Ű�� �Լ�
void initCurser(PointCurser *player1, PointCurser *player2)
{
	player1->x = G_BOARD_ROW / 2 - 2;
	player1->y = G_BOARD_COL / 2;

	player2->x = G_BOARD_ROW / 2 - 2;
	player2->y = G_BOARD_COL / 2;
}

// �÷��̾��� Ŀ���� �̵���Ű�� �Լ�
void moveCurser(wchar_t _board[G_BOARD_ROW][G_BOARD_COL], PointCurser *player, int moveDir)
{
	switch (moveDir)
	{
	case LEFT:
		if (player->x - (G_BOARD_INTERVAL_COL + 1) < G_COL_START)
		{
			printAlert("����� ������ ���� �� �����ϴ�.\n");
			printf("(%d,%d)\n", player->x, player->y);
			break;
		}

		player->x -= (G_BOARD_INTERVAL_COL + 1);
		printf("(%d,%d)\n", player->x, player->y);
		break;

	case RIGHT:
		if (player->x + (G_BOARD_INTERVAL_COL + 1) > G_COL_END)
		{
			printAlert("����� ������ ���� �� �����ϴ�.\n");
			printf("(%d,%d)\n", player->x, player->y);
			break;
		}

		player->x += (G_BOARD_INTERVAL_COL + 1);
		printf("(%d,%d)\n", player->x, player->y);
		break;

	case UP:
		if (player->y - (G_BOARD_INTERVAL_ROW + 1) > G_ROW_END)
		{
			printAlert("����� ������ ���� �� �����ϴ�.\n");
			printf("(%d,%d)\n", player->x, player->y);
			break;
		}

		player->y -= (G_BOARD_INTERVAL_ROW + 1);
		printf("(%d,%d)\n", player->x, player->y);
		break;

	case DOWN:
		if (player->y + (G_BOARD_INTERVAL_ROW + 1) < G_ROW_START)
		{
			printAlert("����� ������ ���� �� �����ϴ�.\n");
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

// �÷��̾��� �Է��� �޴� �Լ�
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

// ����� ǥ���ϴ� �Լ�
void printAlert(char alertText[])
{
	printf("%s", alertText);
}